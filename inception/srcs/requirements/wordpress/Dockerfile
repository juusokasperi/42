FROM alpine:3.21.3

RUN	apk update && apk add --no-cache \
	php83 php83-fpm php83-mysqli curl php83-phar \
	php83-mbstring php83-json php83-curl php83-dom php83-xml \
	php83-xmlreader php83-xmlwriter php83-simplexml php83-tokenizer \
	php83-ctype php83-fileinfo php83-zip php83-gd php83-iconv netcat-openbsd \
	php83-redis

COPY ./conf/www.conf /etc/php83/php-fpm.d/www.conf
COPY ./conf/php.ini /etc/php83/php.ini
COPY ./entrypoint.sh /entrypoint.sh

RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
	chmod +x wp-cli.phar && mv wp-cli.phar /usr/local/bin/wp

RUN chmod +x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]
