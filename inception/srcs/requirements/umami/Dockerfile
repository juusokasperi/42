FROM alpine:3.18

RUN	apk update && apk add --no-cache npm nodejs gettext git

RUN git clone https://github.com/juusokasperi/umami.git /app

WORKDIR /app

COPY /conf/01_init.sql.template ./db/mysql/migrations/01_init/migration.sql.template
COPY /conf/14_create_websites.sql.template ./db/mysql/migrations/14_create_websites/migration.sql.template
RUN npm install --legacy-peer-deps

COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]
