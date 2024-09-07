#include "tcp_server.h"

int create_server_socket() // finction to create aserver socket 
{
    int server_fd;
    if ((server_fd = sockot(AF_INET, SOCK_STREAM, 0), 0) == 0)
    {
        perror("faild to create socket");
        exit (EXIT_FAILURE);
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
        exit (EXIT_FAILURE);
    }
}

int handle_new_connection(int server_fd, struct sockaddr_in* address, int *client_socket, int addrlen)
{
    int new_socket;
    int i;

    if ((new_socket = accept(server_fd, (struct sockaddr*)address, (socklen_t*)&addrlen)) < 0)
    {
        perror("Accept failed");
        exit (EXIT_FAILURE);
    }

    i = 0;
    while (i < MAX_CLIENTS)
    {
        if (client_socket[i] == 0)
        {
            client_socket[i] = new_socket;
            break;
        }
    }
    return new_socket;    
}

int main (void)
{
    int server_fd;
    int client_socket[MAX_CLIENTS];
    int max_sd;
    int socket_id;
    int  activity;
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);
    int buffer[BUFFER_SIZE] = {0};
    fd_set readfds;
    int i;

    i = 0;
    while (i < MAX_CLIENTS)
    {
        client_socket[i] = 0;
        i++;
    }

    server_fd = create_server_socket();
    bind_and_listen(server_fd, &addr);
    
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
        if ((activity < 0) && (errno != EIDRM))
            perror("select error");
        if (FD_ISSET(server_fd, &readfds))
            handle_new_connection(server_fd, &addr, client_socket, addrlen);
        i = 0;
        while (i < MAX_CLIENTS)
        {
            socket_id = client_socket[i];
            if (FD_ISSET(socket_id, &readfds))
                handle_client_data(server_fd, &addr, client_socket, addrlen);
            i++;
        }
    }

    return 0;
}

