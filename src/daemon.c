#include "tcp_server.h"

void copy_binary(const char* source_path, const char* dest_path) 
{
    FILE *source_file = fopen(source_path, "rb");
    if (source_file == NULL) {
        perror("Failed to open source file");
        exit(EXIT_FAILURE);
    }

    FILE *dest_file = fopen(dest_path, "wb");
    if (dest_file == NULL) {
        perror("Failed to open destination file");
        fclose(source_file);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFSIZ];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        fwrite(buffer, 1, bytes, dest_file);
    }

    fclose(source_file);
    fclose(dest_file);
}

void create_systemd_service(const char* service_name, const char* binary_path) 
{
    char service_file_path[256];
    snprintf(service_file_path, sizeof(service_file_path), "/etc/systemd/system/%s", service_name);

    FILE* file = fopen(service_file_path, "w");
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

