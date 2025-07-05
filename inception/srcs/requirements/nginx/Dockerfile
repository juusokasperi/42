FROM alpine:3.21.3

RUN apk update && apk add --no-cache nginx openssl gettext

RUN mkdir -p /run/nginx /etc/ssl/private /etc/ssl/certs

COPY ./conf/nginx.conf.template /etc/nginx/nginx.conf.template
COPY ./entrypoint.sh /entrypoint.sh

RUN chmod +x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]
