#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <vector>
#include <utility>
#include "common.h"

class HighScore
{
public:
	static HighScore& getInstance()
	{
		static HighScore instance;
		return instance;
	}
	void ReadScores();
	void WriteScores();
	bool checkAndAddNewScore(int newScore, Difficulty gameDifficulty);
	bool addScore(int score, std::vector<std::pair<std::string, int>>& scores);
	void addInitials(std::string inputText);
	std::vector<std::pair<std::string, int>> getEasyScores();
	std::vector<std::pair<std::string, int>> getMediumScores();
	std::vector<std::pair<std::string, int>> getHardScores();
	std::vector<std::pair<std::string, int>> getWhoaScores();
private:
	HighScore() {};
	HighScore(HighScore const&);
	void operator=(HighScore const&);
	std::vector<std::pair<std::string, int>> easyScores;
	std::vector<std::pair<std::string, int>> mediumScores;
	std::vector<std::pair<std::string, int>> hardScores;
	std::vector<std::pair<std::string, int>> whoaScores;
};

#endif 
