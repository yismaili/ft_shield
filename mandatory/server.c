#include <stdio.h>
#include <stdlib.h>
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

void accept_socket(int server_fd, struct sockaddr_in* address, int addrlen) {
    int new_socket;

    if((new_socket = accept(server_fd, (struct sockaddr*)address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
    return new_socket;
}

void read_write() {

}