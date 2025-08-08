DOMAIN_NAME := $(shell grep '^DOMAIN_NAME=' srcs/.env 2>/dev/null | cut -d'=' -f2)
ifeq ($(DOMAIN_NAME),)
	DOMAIN_NAME := jrinta-.42.fr
endif

HOSTS_ENTRY = ::1 $(DOMAIN_NAME)
HOSTS_FILE = /etc/hosts

WP_DATA_DIR = srcs/wp_data/
MARIA_DATA_DIR = srcs/maria_data/
REDIS_DATA_DIR = srcs/redis_data
PORTFOLIO_DATA_DIR = srcs/portfolio_data
PORTFOLIO_DIR = srcs/requirements/portfolio

DOCKER_COMPOSE = srcs/docker-compose.yml

all: up

create_dirs:
	@mkdir -p $(WP_DATA_DIR)
	@mkdir -p $(MARIA_DATA_DIR)
	@mkdir -p $(REDIS_DATA_DIR)
	@mkdir -p $(PORTFOLIO_DATA_DIR)

add_hosts_entry:
	@if ! grep -q "$(HOSTS_ENTRY)" $(HOSTS_FILE); then \
		echo "Adding domain $(DOMAIN_NAME) to hosts.."; \
		echo "$(HOSTS_ENTRY)" | sudo tee -a $(HOSTS_FILE) > /dev/null; \
	fi

remove_hosts_entry:
	@if grep -q "$(HOSTS_ENTRY)" $(HOSTS_FILE); then \
		echo "Removing $(HOSTS_ENTRY) from hosts file.."; \
		sudo sed -i '' '/$(HOSTS_ENTRY)/d' $(HOSTS_FILE); \
	fi

up: add_hosts_entry create_dirs
	@docker compose -f $(DOCKER_COMPOSE) up -d

build: add_hosts_entry create_dirs
	@docker compose -f $(DOCKER_COMPOSE) up --build -d
	@timeout=40; elapsed=0; \
	spinner="⠋⠙⠹⠸⠼⠴⠦⠧"; \
	while [ $$elapsed -lt $$timeout ]; do \
		if docker exec wordpress test -f /var/www/html/wp-config.php 2>/dev/null; then \
			printf "\r \033[1;32m✔\033[0m WordPress is ready!\033[K\n"; \
			break; \
		fi; \
		char=$$(echo "$$spinner" | cut -c$$(( (elapsed % 8) + 1))); \
		printf "\r \033[0;33m%s\033[0m WordPress setting up. [%02d/%02ds]" "$$char" "$$elapsed" "$$timeout"; \
		sleep 1; \
		elapsed=$$((elapsed + 1)); \
	done; \
	if [ $$elapsed -ge $$timeout ]; then \
		printf "\r \033[0;35m✘\033[0m WordPress installation timed out (%02ds). Cleaning up..\033[K\n" "$$timeout"; \
		$(MAKE) fclean; \
		exit 1; \
	fi

down:
	@docker compose -f $(DOCKER_COMPOSE) down

fclean:
	@docker compose -f $(DOCKER_COMPOSE) down -v --rmi all --remove-orphans
	@rm -rf $(MARIA_DATA_DIR) $(WP_DATA_DIR) $(REDIS_DATA_DIR) $(PORTFOLIO_DATA_DIR)
	@$(MAKE) remove_hosts_entry

re: fclean build

.PHONY: add_hosts_entry remove_hosts_entry build up fclean down create_dirs build_portfolio re
