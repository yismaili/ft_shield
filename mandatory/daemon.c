# include "ft_shield.h"

void create_daemon()
{
    pid_t pid;

    pid = fork();
    if (pid < 0){
        exit(EXIT_FAILURE);
    }
    if (pid > 0){
        exit(EXIT_SUCCESS);
    }
    if (setsid() < 0){
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0){
        exit(EXIT_FAILURE);
    }
    if (pid > 0){
        exit(EXIT_SUCCESS);
    }
    chdir("/");
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}
