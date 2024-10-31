# include "ft_shield.h"

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
