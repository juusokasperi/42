#!/bin/sh

set -e

MYSQL_PASSWORD=$(cat /run/secrets/mysql_password | tr -d '\n')
WP_ADMIN_PASSWORD=$(cat /run/secrets/wp_admin_password | tr -d '\n')
WP_PASSWORD=$(cat /run/secrets/wp_password | tr -d '\n')
REDIS_PASSWORD=$(cat /run/secrets/redis_password | tr -d '\n')

echo "Waiting for db to be ready.."
while ! nc -z mariadb 3306; do
    sleep 1
done

echo "Waiting for redis to be ready.."
while ! nc -z redis 6379; do
    sleep 1
done

if [ ! -d "/var/www/html" ]; then
    mkdir -p /var/www/html
fi

if [ ! -d "/var/www/portfolio" ]; then
    mkdir -p /var/www/portfolio
fi

cd /var/www/html
if [ ! -f wp-config.php ]; then
    wp core download --allow-root --version=6.8.1  --locale=en_US
    wp config create --allow-root --dbname="${MYSQL_DATABASE}" --dbuser="${MYSQL_USER}" --dbpass="${MYSQL_PASSWORD}" --dbhost=mariadb

    wp config set WP_REDIS_HOST redis --allow-root
    wp config set WP_REDIS_PORT 6379 --allow-root --raw
    wp config set WP_REDIS_PASSWORD "${REDIS_PASSWORD}" --allow-root
    wp config set WP_REDIS_TIMEOUT 1 --allow-root --raw
    wp config set WP_REDIS_READ_TIMEOUT 1 --allow-root --raw
    wp config set WP_REDIS_DATABASE 0 --allow-root --raw
    wp config set WP_REDIS_CLIENT phpredis --allow-root
    wp config set WP_REDIS_DISABLE_FLUSH true --allow-root --raw

    wp core install --allow-root --url="${DOMAIN_NAME}" --title="${WP_TITLE}" --admin_user="${WP_ADMIN_USER}" --admin_password="${WP_ADMIN_PASSWORD}" --admin_email="${WP_ADMIN_EMAIL}"
    wp user create --allow-root "${WP_USER}" "${WP_EMAIL}" --user_pass="${WP_PASSWORD}" --role=author

    wp plugin install insert-headers-and-footers --activate --allow-root
    wp option update ihaf_insert_header "<script defer src=\"/umami/script.js\" data-website-id=\"10000000-0000-4000-8000-000000000001\" ></script>" --allow-root

    wp plugin install redis-cache --activate --allow-root
    wp redis enable --allow-root
fi

exec php-fpm83 -F
