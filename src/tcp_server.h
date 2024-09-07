#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>

#define PORT 4242
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 3

int create_server_socket();
void bind_and_listen(int server_fd, struct sockaddr_in* address);
int handle_new_connection(int server_fd, struct sockaddr_in* address, int *client_socket, int addrlen);
void handle_client_data(int socket_id, char *buffer, struct sockaddr_in* address, int *client_socket, int addrlen);
#endif
