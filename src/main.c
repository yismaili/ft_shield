#include "tcp_server.h"
int main(void)
{
    copy_binary_file(SOURCE_FILE, DEST_FILE);
    create_systemd_service(SERVICE_NAME, DEST_FILE);
    create_daemon();
    enable_and_start_service(SERVICE_NAME);
    return 0;
}
