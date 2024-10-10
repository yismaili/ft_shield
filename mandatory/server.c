#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>
#include <fcntl.h>

int create_socket() {
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        perror("failed to create socket");
        exit(EXIT_FAILURE);
    }
    return socketfd;
}

void bind_socket(int socketfd, struct sockaddr_in* address) {
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(4242);

    if(bind(socketfd, (struct sockaddr*)address, sizeof(*address)) < 0) {
        perror("bind failed");
        close(socketfd);
        exit(EXIT_FAILURE);
    }
}

void listen_socket(int socketfd) {
    if(listen(socketfd, 3) < 0) {
        perror("listen failed");
        close(socketfd);
        exit(EXIT_FAILURE);
    }
}

int accept_socket(int server_fd, struct sockaddr_in* address, int addrlen, int *client_socket) {
    int new_socket;
    int i;

    i = 0;
    if((new_socket = accept(server_fd, (struct sockaddr*)address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
    while (i < 3)
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

void read_write(int *client_socket, int server_fd, char* buffer) {
    int valread;
    int i;

    i = 0;
    if ((valread = read(server_fd, buffer, 1024)) == 0) {
        close(server_fd);
        while (i < 3)
        {
            if (client_socket[i] == server_fd)
            {
                client_socket[i] = 0;
                break;
            }
            i++;
        }
    }
    else {
        printf("Received: %s\n", buffer); 
        // write(server_fd, buffer, strlen(buffer));
    }
}

int main(void)
{
    int i;
    int server_fd;
    int socket_id;
    int max_sd;
    int activity;
    int new_socket;
    int client_socket[3];
    char buffer[1024] = {0};
    fd_set readfds;
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);

    i = 0;
    while (i < 3)
    {
        client_socket[i] = 0;
        i++;
    }

    server_fd = create_socket();
    bind_socket(server_fd, &addr);
    listen_socket(server_fd);

    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        max_sd = server_fd;

        i = 0;
        while (i < 3)
        {
            socket_id = client_socket[i];
            if (socket_id > 0){
                FD_SET(socket_id, &readfds);
            }
            if (socket_id > max_sd){
                max_sd = socket_id;
            }
            i++;
        }
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if ((activity < 0) && (errno != EINTR)) { 
            perror("select error"); 
        }
        if (FD_ISSET(server_fd, &readfds)) {
            new_socket = accept_socket(server_fd, &addr, addrlen, client_socket);
            // hna khassu ithauthentifya
        }
        i = 0;
        while (i < 3)
        {
            socket_id = client_socket[i];
            if (FD_ISSET(socket_id, &readfds)) {
                read_write(client_socket, socket_id, buffer);
            }
            i++;
        }
    }
    close(server_fd);
    return (0);
}