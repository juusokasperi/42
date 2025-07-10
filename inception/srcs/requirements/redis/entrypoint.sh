#!/bin/sh

export REDIS_PASSWORD=$(cat /run/secrets/redis_password | tr -d '\n')

envsubst '${REDIS_PASSWORD}' < /etc/redis/redis.conf.template > /etc/redis/redis.conf

exec redis-server /etc/redis/redis.conf
