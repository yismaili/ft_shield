## Foreword
This project aims to develop a simple trojan horse program called ft_shield. It is designed as a hands-on exercise to learn about malware programming, focusing specifically on trojan horse mechanisms. The project does not intend to promote malicious activity but serves as an educational tool for understanding software security vulnerabilities.
## Usage Example
# Start the program
    $ ./ft_shield
# Verify daemon is running
    $ systemctl status ft_shield.service
# Connect to daemon
    $ nc addr_ip 4242
    Keycode: 42
    $> shell
    Spawning shell on port 4242
