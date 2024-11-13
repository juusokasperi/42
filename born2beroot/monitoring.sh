#! /bin/bash

arc=$(uname -a)
num_processors=$(lscpu | awk '$1 == "Socket(s):" {print $2}')
threads=$(lscpu | awk '$1 == "CPU(s):" {print $2}')
total_ram=$(free -m | awk '$1 == "Mem:" {print $2}')
used_ram=$(free -m | awk '$1 == "Mem:" {print $3}')
percentage_ram=$(free -m | awk '$1 == "Mem:" {printf("%.2f", $3/$2*100)}')
total_space=$(df -BG | grep '^/dev/' | grep -v '/boot$' | awk '{total += $2} END {print total}')
free_space=$(df -BM | grep '^/dev/' | grep -v '/boot$' | awk '{used += $3} END {print used}')
percentage_space=$(df -BM | grep '^/dev/' | grep -v '/boot$' | awk '{used += $3} {total += $2} END {printf("%d", used/total*100)}')
cpu_load=$(top -bn1 | grep '^%Cpu' | awk '{printf("%.2f", $2 + $4)}')
last_boot=$(who -b | awk '{print $3 " " $4}')
lvm_use=$(if [ $(lsblk | grep "lvm" | wc -l) -eq 0 ]; then echo no; else echo yes; fi)
tcp_conns=$(netstat -ant | grep "ESTABLISHED" | wc -l)
users_logged=$(w -h | wc -l)
ip=$(hostname -I)
mac=$(ip link show | grep "ether" | awk '{print $2}')
sudo_cmds=$(journalctl _COMM=sudo -q | grep "COMMAND" | wc -l)

wall "	#Architecture: $arc
	#CPU physical: $num_processors
	#vCPU: $threads
	#Memory usage: $used_ram/${total_ram}MB ($percentage_ram%)
	#Disk usage: $free_space/${total_space}Gb ($percentage_space%)
	#CPU load: $cpu_load%
	#Last boot: $last_boot
	#LVM use: $lvm_use
	#Connections TCP: $tcp_conns
	#User log: $users_logged	
	#Network: IP $ip ($mac)
	#Sudo: $sudo_cmds cmd
"
