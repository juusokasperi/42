#!/bin/sh

FTP_PASSWORD=$(cat /run/secrets/ftp_password | tr -d '\n')

if [ ! -f "/etc/ssl/certs/vsftpd.crt" ]; then
	echo "Generating SSL certificate for FTP server"
	openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
		-keyout /etc/ssl/private/vsftpd.key \
		-out /etc/ssl/certs/vsftpd.crt \
		-subj "/CN=${DOMAIN_NAME:-jrinta-.42.fr}"
fi

adduser -D -h /home/${FTP_USER} ${FTP_USER} && echo "${FTP_USER}:${FTP_PASSWORD}" | chpasswd

exec /usr/sbin/vsftpd /etc/vsftpd/vsftpd.conf
