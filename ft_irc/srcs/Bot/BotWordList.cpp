#include "Bot/BotWordList.hpp"

const std::vector<std::string> wordList = {
	"electricity", "keyboard", "hardware", "foundation", "transistor", "computer", "desktop",
	"engineering", "greenhouse", "circuit", "imagination", "robot", "memory", "colleague",
	"submarine", "chess", "resistance", "matrix", "function", "laser", "mechanism",
	"bodyguard", "algorithm", "global", "ozone", "bridge", "technology", "spider", "universe",
	"pyramid", "sphere", "member", "warning", "ignorance", "screen", "language", "elevator",
	"system", "internet", "parameter", "traffic", "network", "filter", "nucleus", "result",
	"automatic", "microphone", "civilization", "operation", "country", "beautiful", "mission",
	"picture", "teacher", "superman", "dimension", "alarm", "process", "mathematics",
	"electron", "certificate", "grandfather", "landmark", "relativity", "eraser", "harmony",
	"design", "pointer", "superstition", "musician", "encryption", "elephant", "directory", "reception",
	"message", "debugger", "nationality", "overflow", "advertisement", "statement", "forest",
	"puzzle", "voltage", "current", "astronomy", "wisdom", "campaign", "supermarket",
	"database", "collection", "barrier", "project", "sunlight", "figure", "graph", "orange",
	"battle", "hundred", "signal", "thousand", "transformation", "daughter", "terminal",
	"communication", "microwave", "achievement", "peace", "wireless", "delete", "window",
	"brain", "control", "firewall", "freedom", "harbour", "confidence", "positive", "destination",
};

std::string	getRandomWord()
{
	if (wordList.empty())
		return "";

	int index = std::rand() % wordList.size();
	return wordList[index];
}