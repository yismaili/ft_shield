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


int main (void)
{
    int server_fd;
    int client_socket[MAX_CLIENTS];
    int max_sd;
    int socket_id;
    int  activity;
    struct sockaddr_in addr;
    int buffer[BUFFER_SIZE] = {0};
    fd_set readfds;
    int i;

    i = 0;
    while (i < MAX_CLIENTS;)
    {
        client_socket[i] = 0;
    }
    server_fd = create_server_socket();
    bind_and_listen(server_fd, &addr);
    

}

