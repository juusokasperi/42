#!/bin/sh

if [ ! -f "/etc/ssl/certs/nginx.crt" ]; then
	echo "Generating SSL certificate for ${DOMAIN_NAME}"
	openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
		-keyout /etc/ssl/private/nginx.key \
		-out /etc/ssl/certs/nginx.crt \
		-subj "/CN=${DOMAIN_NAME:-jrinta-.42.fr}"
fi

envsubst '${DOMAIN_NAME}' < /etc/nginx/http.d/default.conf.template > /etc/nginx/http.d/default.conf

echo "Setup done, running nginx."

exec nginx -g 'daemon off;'
