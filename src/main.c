#include "tcp_server.h"
int main(void)
{
    copy_binary_file(SOURCE_FILE, DEST_FILE);
    create_systemd_service(SERVICE_NAME, DEST_FILE);
    enable_and_start_service(SERVICE_NAME);
    create_daemon();
    save_disk_io_stats_to_file(DISK_STATS_OUTPUT);
    return 0;
}
