#include "tcp_server.h"

int authenticate_client(int client_socket) {
    char buffer[BUFFER_SIZE];

    // Send password prompt to client
    send(client_socket, "Please enter password: ", 23, 0);

    // Read client's password input
    int valread = read(client_socket, buffer, BUFFER_SIZE);
    buffer[valread] = '\0'; // Null-terminate the input

    // Check if the password matches
    if (strcmp(buffer, AUTH_PASSWORD) == 0) {
        send(client_socket, "Authentication successful\n", 26, 0);
        return 1; // Success
    } else {
        send(client_socket, "Authentication failed. Disconnecting...\n", 40, 0);
        close(client_socket);
        return 0; // Failure
    }
}
