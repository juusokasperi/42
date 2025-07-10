FROM alpine:3.18

RUN	apk update && apk add --no-cache redis gettext

COPY conf/redis.conf.template /etc/redis/redis.conf.template

COPY entrypoint.sh /entrypoint.sh

RUN mkdir -p /data && \
	mkdir -p /etc/redis && \
	chown redis:redis /data && \
	chown redis:redis /etc/redis && \
	chown redis:redis /etc/redis/redis.conf.template && \
	chmod +x /entrypoint.sh

USER redis

ENTRYPOINT ["/entrypoint.sh"]
