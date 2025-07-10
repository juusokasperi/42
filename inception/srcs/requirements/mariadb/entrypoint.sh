#!/bin/sh
set -e

ls -la /run/secrets/

export MYSQL_PASSWORD=$(cat /run/secrets/mysql_password | tr -d '\n')
export MYSQL_ROOT_PASSWORD=$(cat /run/secrets/mysql_root_password | tr -d '\n')

envsubst '${MYSQL_DATABASE},${MYSQL_USER},${MYSQL_PASSWORD},${MYSQL_ROOT_PASSWORD}' < /etc/mysql/init.sql.template > /etc/mysql/init.sql

if [ ! -d "/var/lib/mysql/mysql" ]; then
	echo "Creating MariaDB database"
	mariadb-install-db --user=mysql --datadir=/var/lib/mysql --basedir=/usr
else
	echo "Database already initialized, skipping init."
fi

echo "Starting MariaDB.."
exec mariadbd-safe --user=mysql --datadir=/var/lib/mysql
