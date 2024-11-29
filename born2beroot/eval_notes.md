uname -a
sudo systemctl status <service>
lsblk

hostnamectl (set-hostname <hostname>)
sudo vim /etc/hosts -> hostname

sudo adduser <name>
sudo groupadd <group>
sudo usermod -aG <group> <username>

sudo vim /etc/pam.d/common-password
sudo vim /etc/login.defs
sudo visudo (sudo nano /etc/sudoers)

sudo crontab -u root -e

php console system:check
php console database:check
