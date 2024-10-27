# include "ft_shield.h"

void add_client(Client* client_arr, int socket_fd)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_arr[i].socket_fd == 0) {
            client_arr[i].socket_fd = socket_fd;
            client_arr[i].isAuthenticated = false;
            return;
        }
    }
}

int is_autheticated(Client* client_arr, int socket_fd)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_arr[i].socket_fd == socket_fd) {
            if (client_arr[i].isAuthenticated == true){
                return (1);
            }else {
                return (0);
            }
        }
    }
    return (0);
}

void make_autheticated(Client* client_arr, int socket_fd)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_arr[i].socket_fd == socket_fd) {
            client_arr[i].isAuthenticated = true;
            break ;
        }
    }
}

void remove_client(Client* client_arr, int socket_fd)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_arr[i].socket_fd == socket_fd) {
            client_arr[i].socket_fd = 0;
            client_arr[i].isAuthenticated = 0;
            break;
        }
    }
}

int authenticate(int client_socket, Client* client_arr, int *numfds)
{
    int n;
    char password[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    n = 1;
    bzero(buffer, BUFFER_SIZE);
    n = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (n == 0) {
        close(client_socket);
        remove_client(client_arr, client_socket);
        (*numfds)--;
    }
    if (n < 0) {
        perror("ERROR READING FROM SOCKET");
        return (0);
    }

    buffer[n] = '\0';
    if (buffer[n - 1] == '\n') {
        buffer[n - 1] = '\0';
    }

    hash(buffer, password);
    if(strcmp(password, AUTH_PASSWORD_HASH) == 0)
    {
        return (1);
    }
    send(client_socket, "Keycode: ", 9, 0);
    return (0);
}