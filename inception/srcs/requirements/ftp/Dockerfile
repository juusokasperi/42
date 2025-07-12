FROM alpine:3.21.3

RUN apk update && apk add --no-cache openssl vsftpd

COPY ./vsftpd.conf /etc/vsftpd/vsftpd.conf
COPY ./entrypoint.sh /entrypoint.sh

RUN chmod +x entrypoint.sh

ENTRYPOINT [ "/entrypoint.sh" ]

