#include "tcp_server.h"

void hash(const char *password, char *hash) {
    unsigned int hash_value;
    size_t i;

    i = 0;
    hash_value = i;
    while(i < strlen(password))
    {
        hash_value = (hash_value * SECRET_KEY) + (unsigned char)password[i];
        i++;
    }
    snprintf(hash, BUFFER_SIZE, "%08x", hash_value);
}

int authenticate_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    char hashed_password[BUFFER_SIZE];
    int valread;

    send(client_socket, "Please enter password: ", 23, 0);
    valread = read(client_socket, buffer, BUFFER_SIZE);

    if (valread <= 0) {
        send(client_socket, "Failed to read password. Disconnecting...\n", 42, 0);
        return 0;
    }

    buffer[valread] = '\0';

    if (buffer[valread - 1] == '\n') {
        buffer[valread - 1] = '\0';
    }

    hash(buffer, hashed_password);

    if (strcmp(hashed_password, AUTH_PASSWORD_HASH) == 0) {
        send(client_socket, "Authentication successful\n", 26, 0);
        return 1;
    } else {
        return 0;
    }
}

