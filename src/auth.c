#include "tcp_server.h"

void hash(const char *password, char *hash) {
    unsigned int hash_value;

    hash_value = 0;
    for (size_t i = 0; i < strlen(password); i++) {
        hash_value = (hash_value * SECRET_KEY) + (unsigned char)password[i];
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
        close(client_socket);
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
        send(client_socket, "Authentication failed. Disconnecting...\n", 40, 0);
        close(client_socket);
        return 0;
    }
}

