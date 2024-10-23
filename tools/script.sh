#!/bin/sh
sudo systemctl stop ft_shield
sudo systemctl disable ft_shield
sudo rm /etc/systemd/system/ft_shield.service
rm -rf /bin/ft_shield
sudo systemctl daemon-reload
sudo systemctl reset-failed ft_shield

