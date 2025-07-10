SRCS =	main.cpp Client.cpp Channel.cpp CommandParser.cpp		\
		Server/Server.cpp			Server/ServerAuth.cpp		\
		Server/ServerHandlers.cpp	Server/ServerJoin.cpp		\
		Server/ServerKick.cpp		Server/ServerMode.cpp 		\
		Server/ServerParse.cpp		Server/ServerPart.cpp		\
		Server/ServerPing.cpp		Server/ServerPrivmsg.cpp	\
		Server/ServerUser.cpp		Server/ServerUtils.cpp		\
		IrcErrors.cpp Logger.cpp
SRCS_DIR = srcs/

SRCS_BONUS = Bot/main.cpp	Bot/Bot.cpp	Bot/BotParse.cpp		\
		Bot/BotHandlers.cpp	CommandParser.cpp Logger.cpp		\
		Bot/BotWordList.cpp	Bot/BotGame.cpp

OBJS_BONUS = $(addprefix $(OBJS_DIR), $(SRCS_BONUS:.cpp=.o))
DEPS_BONUS = $(addprefix $(DEPS_DIR), $(SRCS_BONUS:.cpp=.d))

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))
OBJS_DIR = objs/

DEPS_DIR = deps/
DEPS = $(addprefix $(DEPS_DIR), $(SRCS:.cpp=.d))

CC = c++
CFLAGS += -Wall -Wextra -Werror -std=c++17 -MMD -MP $(INCS)
CFLAGS += -O2 -DNDEBUG -march=native -mtune=native -flto -fomit-frame-pointer

INCS = -I./incs/

NAME = ircserv
NAME_BONUS = ircbot

$(OBJS_DIR)bonus/%.o: $(SRCS_DIR)bonus/%.cpp
	@mkdir -p $(dir $@) $(dir $(DEPS_DIR)$*)
	@$(CC) $(CFLAGS) -c $< -o $@ -MF $(DEPS_DIR)$*.d

$(OBJS_DIR)%.o: $(SRCS_DIR)%.cpp
	@mkdir -p $(dir $@) $(dir $(DEPS_DIR)$*)
	@$(CC) $(CFLAGS) -c $< -o $@ -MF $(DEPS_DIR)$*.d

all: $(NAME)
bonus: $(NAME_BONUS)
bot: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)
	@echo "IRCBOT: Compilation OK, executable ./$(NAME_BONUS)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "FT_IRC: Compilation OK, executable ./$(NAME)"

-include $(DEPS) $(DEPS_BONUS)

clean:
	@rm -rf $(OBJS_DIR) $(DEPS_DIR) server_log bot_log
	@echo "FT_IRC: Clean OK."

fclean:
	@rm -rf $(OBJS_DIR) $(DEPS_DIR) $(NAME) $(NAME_BONUS) server_log bot_log
	@echo "FT_IRC: FClean OK."

re: fclean all

.PHONY: all clean fclean re bonus bot
