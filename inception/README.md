# Inception

A dockerized environment that sets up Nginx, WordPress, MariaDB, Redis, Adminer, FTP, Static Portfolio site built with TypeScripted React and Umami, each in their own containers.

## Setup

1. Add a `.env` file to `srcs/` folder.

- Needed variables for `.env` (also present in `.env.example`):
```sh
DOMAIN_NAME=
MYSQL_DATABASE=
MYSQL_USER=

WP_TITLE=

WP_ADMIN_USER=
WP_ADMIN_EMAIL=

WP_USER=
WP_EMAIL=

FTP_USER=

UMAMI_USER=
UMAMI_DB=

UMAMI_ADMIN_USERNAME=
```

2. Add the following service passwords into `srcs/secrets`;
```sh
ftp_password.txt			mysql_password.txt
mysql_root_password.txt		redis_password.txt
umami_admin_password.txt	umami_mysql_password.txt
wp_admin_password.txt		wp_password.txt
```

3. Run `make build` in the project root.

4. The services are available via your specified domain name and at `https://localhost:443`. Subservices include `https://localhost:443/adminer`, `https://localhost:443/umami`, `https://localhost:443/portfolio`. The FTP service is accessible with a FTP client at port 21.

---

Other make commands include `up` `down` `fclean` `re`
