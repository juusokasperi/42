#pragma once

#include <array>
#include <chrono>

static constexpr const char *NICKNAME = "Bot42";
static constexpr const char *USERNAME = "Bot";
static constexpr const char *REALNAME = "IRC Bot";

static constexpr int MAX_CHANNELS = 25;
static constexpr int MAX_IRC_MESSAGE_LENGTH = 512;
static constexpr int POLL_INTERVAL = 1;
static constexpr int DISCONNECT_TIMEOUT = 5;
static constexpr auto GAME_CLEANUP_INTERVAL = std::chrono::minutes(1);

static constexpr std::array<const char*, 2> DEFAULT_CHANNELS = {
	"#TestChannel",
	"#TestChannel2",
};
