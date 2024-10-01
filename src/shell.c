#include "tcp_server.h"

void log_user_action(const char *command) {
    FILE *log_file = fopen(LOGS, "a");
    if (log_file == NULL) {
        perror("Error opening log file");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", t);

    fprintf(log_file, "[%s] %s\n", time_str, command);
    
    fclose(log_file);
}


void execute_command(const char* command, int client_socket) 
{
    char buffer[BUFFER_SIZE];
    FILE* fp;
    int status;
    log_user_action(command);
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