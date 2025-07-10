#include "Bot/BotGame.hpp"

BotGame::BotGame(const std::string& word)
{
	reset(word);
}

BotGame::~BotGame() {}

void	BotGame::reset(const std::string& newWord)
{
	wordToGuess = newWord;
	maskedWord = std::string(newWord.length(), '_');
	guessedLetters.clear();
	wrongAttempts = 0;
	maxAttempts = 8;
	isGameOver = false;
	lastGameActivity = std::chrono::steady_clock::now();
}

bool	BotGame::getIsGameOver() const { return isGameOver; };

static std::string	addSpaces(std::string word)
{
	std::string spacedWord;
	for (char c : word)
	{
		spacedWord += '[';
		spacedWord += c;
		spacedWord += ']';
		spacedWord += ' ';
	}
	return spacedWord;
}

std::string	BotGame::getStartMessage() const
{
	return "New Hangman game started! The word has " + std::to_string(wordToGuess.length()) +
		" letters: " + addSpaces(maskedWord);
}

std::string	BotGame::getGameStatus()
{
	setLastGameActivity();
	std::string guessedLettersString;
	for (auto it = guessedLetters.begin(); it != guessedLetters.end(); ++it)
	{
		guessedLettersString += *it;
		if (std::next(it) != guessedLetters.end())
			guessedLettersString += ", ";
	}
	std::string	statusMsg = addSpaces(maskedWord) + " | Guessed: " + (guessedLetters.empty() ? "-" : guessedLettersString) +
							" | Attempts left: " + std::to_string(maxAttempts - wrongAttempts);
	return statusMsg;
}

std::chrono::steady_clock::time_point BotGame::getLastGameActivity() const { return lastGameActivity; }
void	BotGame::setLastGameActivity()
{
	lastGameActivity = std::chrono::steady_clock::now();
}

std::vector<std::string>	BotGame::guess(char letter)
{
	setLastGameActivity();
	if (isGameOver)
		return {"No active game. Start a new game first."};

	if (guessedLetters.find(letter) != guessedLetters.end())
		return {"You already guessed that letter. Try a different one."};
	
	guessedLetters.insert(letter);
	bool letterFound = false;

	for (size_t i = 0; i < wordToGuess.length(); ++i)
	{
		if (wordToGuess[i] == letter)
		{
			maskedWord[i] = wordToGuess[i];
			letterFound = true;
		}
	}
	if (letterFound)
	{
		if (maskedWord == wordToGuess)
		{
			isGameOver = true;
			return {"Congratulations! You guessed the word: " + addSpaces(wordToGuess)};
		}
		else
			return {"Letter found!", addSpaces(maskedWord), ""};
	}
	else
	{
		++wrongAttempts;
		if (wrongAttempts == 1)
		{
			return {
				"Letter not found. Attempts left: " + std::to_string(maxAttempts - wrongAttempts),
				addSpaces(maskedWord),
				"_______",
				"|/",
				"|",
				"|",
				"|",
				"|",
				"|",
				"|"
			};
		}
		else if (wrongAttempts == 2)
		{
			return {
				"Letter not found. Attempts left: " + std::to_string(maxAttempts - wrongAttempts),
				addSpaces(maskedWord),
				"_______",
				"|/    ",
				"|     O",
				"|",
				"|",
				"|",
				"|",
				"|"
			};
		}
		else if (wrongAttempts == 3)
		{
			return {
				"Letter not found. Attempts left: " + std::to_string(maxAttempts - wrongAttempts),
				addSpaces(maskedWord),
				"_______",
				"|/    ",
				"|     O",
				"|     |",
				"|     |",
				"|",
				"|",
				"|"
			};
		}
		else if (wrongAttempts == 4)
		{
			return {
				"Letter not found. Attempts left: " + std::to_string(maxAttempts - wrongAttempts),
				addSpaces(maskedWord),
				"_______",
				"|/    ",
				"|     O",
				"|    /|",
				"|     |",
				"|",
				"|",
				"|"
			};
		}
		else if (wrongAttempts == 5)
		{
			return {
				"Letter not found. Attempts left: " + std::to_string(maxAttempts - wrongAttempts),
				addSpaces(maskedWord),
				"_______",
				"|/    ",
				"|     O",
				"|    /|\\",
				"|     |",
				"|",
				"|"
			};
		}
		else if (wrongAttempts == 6)
		{
			return {
				"Letter not found. Attempts left: " + std::to_string(maxAttempts - wrongAttempts),
				addSpaces(maskedWord),
				"_______",
				"|/     ",
				"|     O",
				"|    /|\\",
				"|     |",
				"|    /",
				"|",
				"|"
			};
		}
		else if (wrongAttempts == 7)
		{
			return {
				"Letter not found. Attempts left: " + std::to_string(maxAttempts - wrongAttempts),
				addSpaces(maskedWord),
				"_______",
				"|/     ",
				"|     O",
				"|    /|\\",
				"|     |",
				"|    / \\",
				"|",
				"|"
			};
		}
		else
		{
			isGameOver = true;
			return {
				addSpaces(maskedWord),
				"_______",
				"|/    |",
				"|     O",
				"|    /|\\",
				"|     |",
				"|    / \\",
				"|",
				"|",
				"Game over! All attempts used. The word was: " + wordToGuess
			};
		}
	}
}

