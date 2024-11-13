# Born2beroot

Install debían on virtualbox, giga muistia riittää ja vaikka 12gb hdd
Pistä kansioon sgoinfre/students/jrinta-/<VM name>
Mount debianin .iso VM asetuksista
Käynnistä VM, asenna
Hostname jrinta-42
Username jrinta-

Set up encrypted LVM
Separate /home, var... partitions
Erasing datan voi cancelata
Encryption key born2ber00t42 esim
Partition disks: jata tilaa /srv/ ja /var/log partitioneille
Proxy saa olla blank, no popularity contest
Deselect ssh server
Jos kysyy GRUB, Yes. (/dev/sda)

## Commands:
lsblk - show partition
dpgk -l | grep sudo - tai ufw, cron, openssh, libpw
hostnamectl host infot
hostnamectl set-hostname <hostname> - change that
sudo nano /etc/hosts - change to same hostname

## Install sudo:
su - 		login as root
apt update
apt upgrade
apt install sudo
usermod -aG sudo jrinta-
getent group sudo
sudo visudo
-> under User privilege specification: jrinta-	ALL=(ALL) ALL
								 user       Host=(which user can run) which commands are OK
## vim:
apt install vim

## ssh-server:
sudo apt install openssh-server
sudo systemctl status ssh
sudo vim /etc/ssh/sshd_config
#Port22 -> Port 4242
sudo grep Port /etc/ssh/sshd_config
sudo service ssh restart

## Ufw:
apt install ufw
sudo ufw enable
sudo ufw status numbered
sudo ufw allow ssh
sudo ufw allow 4242
sudo ufw status numbered
sudo ufw delete rule <number>

## Setup connecting to ssh:
Virtual box settings->network->adapter1->port forwarding->host & guest 4242

sudo systemctl restart ssh -< boot ssh
sudo service sshd status

Connect to ssh in terminal:
ssh jrinta-@127.0.0.1 -p 4242
(In case of error, rm ~/.ssh/known_hosts and redo)

## Set up password policy:
sudo apt install libpam-pwquality
sudo vim /etc/pam.d/common-password

password requisite pam_pwquality.so retry=3 minlen=10 ucredit=-1 lcredit=-1 dcredit=-1 maxrepeat=3 reject_username difok=7
password required pam_pwhistory.so remember=5 use_authtok

Sudo vim /etc/login.defs
PASS_MAX_DAYS 30, MIN 2, WARN 7

sudo reboot

## users & groups:
sudo groupadd user42
getent group <user42>
cut -d: -f1 /etc/passwd to check all users
sudo adduser <name>
sudo usermod -aG <group> <username>
groups to see where current user belongs to
chage -l username to see password rules

chage -M, chage -m, chage -W

## Create sudolog:
cd ~/../../
cd var/log/
mkdir sudo
cd sudo && touch sudo.log
cd ~/../

sudo nano /etc/sudoers

Defaults	env_reset
Defaults	mail_badpass
Defaults secure_path=“/usr/local/sbin:/usr/local/bin:/usr/bin:/sbin:/bin”
Defaults	badpass_message=“Incorrect password - please do try again.”
Defaults	passwd_tries=3
Defaults	logfile=“/var/log/sudo/sudo.log”
Defaults	log_input, log_output
Defaults	requiretty

## Cron:
apt install net-tools
cd /usr/local/bin
touch monitoring.sh
chmod 777 monitoring.sh

Put in through terminal ssh connection:
#!/bin/bash
arc=$(uname -a)
pcpu=$(grep "physical id" /proc/cpuinfo | sort | uniq | wc -l)
vcpu=$(grep "^processor" /proc/cpuinfo | wc -l)
fram=$(free -m | awk '$1 == "Mem:" {print $2}')
uram=$(free -m | awk '$1 == "Mem:" {print $3}')
pram=$(free | awk '$1 == "Mem:" {printf("%.2f"), $3/$2*100}')
fdisk=$(df -BG | grep '^/dev/' | grep -v '/boot$' | awk '{ft += $2} END {print ft}')
udisk=$(df -BM | grep '^/dev/' | grep -v '/boot$' | awk '{ut += $3} END {print ut}')
pdisk=$(df -BM | grep '^/dev/' | grep -v '/boot$' | awk '{ut += $3} {ft+= $2} END {printf("%d"), ut/ft*100}')
cpul=$(top -bn1 | grep '^%Cpu' | cut -c 9- | xargs | awk '{printf("%.1f%%"), $1 + $3}')
lb=$(who -b | awk '$1 == "system" {print $3 " " $4}')
lvmu=$(if [ $(lsblk | grep "lvm" | wc -l) -eq 0 ]; then echo no; else echo yes; fi)
ctcp=$(ss -Ht state established | wc -l)
ulog=$(users | wc -w)
ip=$(hostname -I)
mac=$(ip link show | grep "ether" | awk '{print $2}')
cmds=$(journalctl _COMM=sudo | grep COMMAND | wc -l)
wall "	#Architecture: $arc
	#CPU physical: $pcpu
	#vCPU: $vcpu
	#Memory Usage: $uram/${fram}MB ($pram%)
	#Disk Usage: $udisk/${fdisk}Gb ($pdisk%)
	#CPU load: $cpul
	#Last boot: $lb
	#LVM use: $lvmu
	#Connections TCP: $ctcp ESTABLISHED
	#User log: $ulog
	#Network: IP $ip ($mac)
	#Sudo: $cmds cmd"

sudo visudo
under %sudo ALL=(ALL:ALL) ALL
jrinta- ALL=(root) NOPASSWD: /usr/local/bin/monitoring.sh

reboot..

sudo /usr/local/bin/monitoring.sh to execute script
sudo crontab -u root -e
*/10 * * * * /usr/local/bin/monitoring.sh

## In terminal:
Go to Box folder
shasum <name>.vdi
Put that number in signature.txt	that will be submitted
