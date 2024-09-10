#include "tcp_server.h"

void copy_binary_file(const char *sourcePath, const char *destinationPath) {
    int sourceFd;
    int destinationFd;
    unsigned char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    sourceFd = open(sourcePath, O_RDONLY);
    if (sourceFd < 0) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    destinationFd = open(destinationPath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH);
    if (destinationFd < 0) {
        perror("Error opening destination file");
        close(sourceFd);
        exit(EXIT_FAILURE);
    }

    while ((bytesRead = read(sourceFd, buffer, sizeof(buffer))) > 0) {
        if (write(destinationFd, buffer, bytesRead) != bytesRead) {
            perror("Error writing to destination file");
            close(sourceFd);
            close(destinationFd);
            exit(EXIT_FAILURE);
        }
    }

    if (bytesRead < 0) {
        perror("Error reading from source file");
    }
    close(sourceFd);
    close(destinationFd);
}

void create_daemon()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
        exit (EXIT_FAILURE);
    if (pid > 0)
        exit (EXIT_SUCCESS);
    if (setsid() < 0)
        exit (EXIT_FAILURE);
    
    pid = fork();
    if (pid < 0)
        exit (EXIT_FAILURE);
    if (pid > 0)
        exit (EXIT_SUCCESS);
    chdir("/");
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

