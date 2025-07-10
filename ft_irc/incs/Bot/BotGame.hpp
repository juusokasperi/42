#pragma once

#include <set>
#include <string>
#include <vector>
#include <chrono>

class BotGame
{
	private:
		std::string		wordToGuess;
		std::string		maskedWord;
		std::set<char>	guessedLetters;
		int				maxAttempts;
		int				wrongAttempts;
		bool			isGameOver;
		std::chrono::steady_clock::time_point	lastGameActivity;

	public:
		BotGame(const std::string& word);
		~BotGame();
		BotGame(const BotGame &src) = delete;
		BotGame& operator=(const BotGame &src) = delete;
		std::string					getStartMessage() const;
		std::vector<std::string>	guess(char letter);
		void						reset(const std::string& newWord);
		bool						getIsGameOver() const;
		std::string					getGameStatus();
		void						setLastGameActivity();
		std::chrono::steady_clock::time_point	getLastGameActivity() const;
};