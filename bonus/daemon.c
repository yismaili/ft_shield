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

void create_systemd_service(const char* service_name, const char* binary_path) 
{
    char service_file_path[256];
    FILE* file;

    snprintf(service_file_path, sizeof(service_file_path), "/etc/systemd/system/%s", service_name);

    file = fopen(service_file_path, "w");
    if (file == NULL) {
        perror("Failed to open service file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "[Unit]\n");
    fprintf(file, "Description=%s\n", service_name);
    fprintf(file, "After=network.target\n\n");

    fprintf(file, "[Service]\n");
    fprintf(file, "ExecStart=%s\n", binary_path);
    fprintf(file, "ExecStop=/bin/kill -s TERM $MAINPID\n");
    fprintf(file, "Restart=on-failure\n");
    fprintf(file, "User=root\n\n");

    fprintf(file, "[Install]\n");
    fprintf(file, "WantedBy=multi-user.target\n");

    fclose(file);

    printf("Service file created: %s\n", service_file_path);
}


void enable_and_start_service(const char* service_name) 
{
    char command[256];
    
    snprintf(command, sizeof(command), "systemctl daemon-reload");
    if (system(command) != 0) {
        perror("Failed to reload systemd daemon");
        exit(EXIT_FAILURE);
    }

    snprintf(command, sizeof(command), "systemctl enable %s", service_name);
    if (system(command) != 0) {
        perror("Failed to enable systemd service");
        exit(EXIT_FAILURE);
    }

    snprintf(command, sizeof(command), "systemctl start %s", service_name);
    if (system(command) != 0) {
        perror("Failed to start systemd service");
        exit(EXIT_FAILURE);
    }

    printf("Service enabled and started: %s\n", service_name);
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

