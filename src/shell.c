#include "tcp_server.h"

void execute_command(const char* command, int client_socket) 
{
    char buffer[BUFFER_SIZE];
    FILE* fp;

    fp = popen(command, "r");
    if (fp == NULL) 
    {
        perror("Failed to run command");
        send(client_socket, "Error executing command\n", 25, 0);
        return;
    }
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
        send(client_socket, buffer, strlen(buffer), 0);
    pclose(fp);
}
