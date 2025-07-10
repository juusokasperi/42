#pragma once

#include <array>

static constexpr std::array<const char*, 3> MOTD = {
	"Welcome to IRC server.",
	"Created by Heidi, Juuso & Matias.",
	"This server was created as a part of the Hive Helsinki curriculum.",
};

static constexpr const char* HOSTNAME = "irc.42";

static constexpr int MAX_IRC_MESSAGE_LENGTH = 512;
static constexpr int DISCONNECT_TIMEOUT = 30;

static constexpr int USER_MAX_CHANNELS = 20;
static constexpr int MAX_TARGETS = 4;
static constexpr int RESERVE_CHANNELS = 1024;
static constexpr int MAX_CLIENTS = 1024;
static constexpr int PING_INTERVAL = 120;
static constexpr int PONG_TIMEOUT = 30;
static constexpr int POLL_INTERVAL = 1000;

static constexpr int NICK_LENGTH = 9;
static constexpr int USERNAME_LENGTH = 9;
static constexpr int REALNAME_LENGTH = 50;
static constexpr int PASSWORD_LENGTH = 32;
static constexpr int CHANNEL_LENGTH = 50;
static constexpr int TOPIC_LENGTH = 307;
static constexpr int KICK_LENGTH = 255;
