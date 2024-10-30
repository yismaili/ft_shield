sudo systemctl stop ft_shield.service
sudo systemctl disable ft_shield.service
sudo rm /etc/systemd/system/ft_shield.service
sudo systemctl daemon-reload
sudo systemctl reset-failed
sudo rm /bin/ft_shield
sudo kill -9 $(lsof -t -i:4242 2>/dev/null) 2>/dev/null