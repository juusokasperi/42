FROM alpine:3.21.3

RUN apk update && apk add --no-cache mariadb gettext mariadb-client

RUN	mkdir -p /var/lib/mysql /run/mysqld && \
	chown -R mysql:mysql /var/lib/mysql /run/mysqld

COPY conf/init.sql.template /etc/mysql/init.sql.template
COPY conf/mariadb-server.cnf /etc/my.cnf.d/mariadb-server.cnf
COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

ENTRYPOINT [ "/entrypoint.sh" ]
