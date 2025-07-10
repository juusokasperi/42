FROM alpine:3.21.3

RUN apk update && apk add --no-cache nginx openssl gettext

RUN mkdir -p /run/nginx /etc/ssl/private /etc/ssl/certs /etc/ssl/nginx/
RUN openssl dhparam -out /etc/ssl/nginx/dh2048.pem 2048

COPY ./conf/nginx.conf /etc/nginx/nginx.conf
COPY ./conf/default.conf.template /etc/nginx/http.d/default.conf.template
COPY ./entrypoint.sh /entrypoint.sh

RUN chmod +x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]
