#include "tcp_server.h"

void execute_command(const char* command, int client_socket) 
{
    char buffer[BUFFER_SIZE];
    FILE* fp;
    int status;

    fp = popen(command, "r");
    if (fp == NULL) 
    {
        send(client_socket, "Error executing command\n", 25, 0);
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp))
    {
        send(client_socket, buffer, strlen(buffer), 0);
    }

    status = pclose(fp);
    if (status != 0) 
    {
        char error_message[BUFFER_SIZE];
        snprintf(error_message, sizeof(error_message), "sh: %s: command not found\n", command);
        send(client_socket, error_message, strlen(error_message), 0);
    }
}
