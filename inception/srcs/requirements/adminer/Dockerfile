FROM alpine:3.21.3

RUN apk update && \
	apk add --no-cache php php-cgi php-session php-mysqli php-pdo_mysql curl

WORKDIR /var/www/html/

RUN curl -L -o adminer.php https://github.com/vrana/adminer/releases/download/v5.3.0/adminer-5.3.0-mysql-en.php

CMD ["php", "-S", "0.0.0.0:8080", "adminer.php"]
