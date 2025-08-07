#!/bin/sh
set -e

ls -la /run/secrets/

export UMAMI_MYSQL_PASSWORD=$(cat /run/secrets/umami_mysql_password | tr -d '\n')
export UMAMI_ADMIN_PASSWORD=$(cat /run/secrets/umami_admin_password | tr -d '\n')
export DATABASE_URL=mysql://${UMAMI_USER}:${UMAMI_MYSQL_PASSWORD}@mariadb:3306/${UMAMI_DB}

echo "Admin password: '${UMAMI_ADMIN_PASSWORD}'"
echo "Attempting to hash password..."
export UMAMI_ADMIN_PASSWORD_HASH=$(node -e "
    const bcrypt = require('./node_modules/bcryptjs');
    console.log(bcrypt.hashSync('${UMAMI_ADMIN_PASSWORD}', 10));
    ")
echo "Hash result: '${UMAMI_ADMIN_PASSWORD_HASH}'"

export UMAMI_ADMIN_ID=${UMAMI_ADMIN_ID:-"41e2b680-648e-4b09-bcd7-3e2b10c06264"}

envsubst '${UMAMI_ADMIN_ID},${UMAMI_ADMIN_USERNAME},${UMAMI_ADMIN_PASSWORD_HASH}' < /app/db/mysql/migrations/01_init/migration.sql.template > /app/db/mysql/migrations/01_init/migration.sql
envsubst '${UMAMI_ADMIN_ID}' < /app/db/mysql/migrations/14_create_websites/migration.sql.template > /app/db/mysql/migrations/14_create_websites/migration.sql

echo "Waiting for db to be ready.."
while ! nc -z mariadb 3306; do
    sleep 1
done

cd /app && npm run build
exec npm run start
