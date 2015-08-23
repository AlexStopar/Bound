#include "highscore.h"
#include "common.h"
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <functional>

void HighScore::ReadScores()
{
	std::string line;
	std::ifstream highScoreFile("highscores.txt");
	for (int i = 0; i < 4; i++)
	{
		std::getline(highScoreFile, line);
		for (int j = 0; j < 5; j++)
		{
			std::getline(highScoreFile, line);
			switch (i){
			case 0:
				easyScores.push_back(std::make_pair(line.substr(0, line.find(",")), 
					atoi(line.substr(line.find(",") + 1, line.size() - 1).c_str())));
				break;
			case 1:
				mediumScores.push_back(std::make_pair(line.substr(0, line.find(",")),
					atoi(line.substr(line.find(",") + 1, line.size() - 1).c_str())));
				break;
			case 2:
				hardScores.push_back(std::make_pair(line.substr(0, line.find(",")),
					atoi(line.substr(line.find(",") + 1, line.size() - 1).c_str())));
				break;
			default:
				whoaScores.push_back(std::make_pair(line.substr(0, line.find(",")),
					atoi(line.substr(line.find(",") + 1, line.size() - 1).c_str())));
				break;
			}
			
		}
	}
	highScoreFile.close();
}

void HighScore::WriteScores()
{
	std::ofstream highScoreFile("highscores.txt");
	for (int i = 0; i < 4; i++)
	{
		switch (i){
		case 0:
			highScoreFile << "EASY";
			break;
		case 1:
			highScoreFile << "MEDIUM";
			break;
		case 2:
			highScoreFile << "HARD";
			break;
		default:
			highScoreFile << "WHOA";
			break;
		}
		highScoreFile << "\n";
		for (int j = 0; j < 5; j++)
		{
			switch (i){
			case 0:
				highScoreFile << easyScores[j].first << "," << easyScores[j].second;
				break;
			case 1:
				highScoreFile << mediumScores[j].first << "," << mediumScores[j].second;
				break;
			case 2:
				highScoreFile << hardScores[j].first << "," << hardScores[j].second;
				break;
			default:
				highScoreFile << whoaScores[j].first << "," << whoaScores[j].second;
				break;
			}
			highScoreFile << "\n";
		}
	}
	highScoreFile.close();
}

bool HighScore::checkAndAddNewScore(int newScore, Difficulty gameDifficulty)
{
	bool isNewScore = false;
	switch (gameDifficulty)
	{
	case Difficulty::EASY:
		isNewScore = addScore(newScore, easyScores);
		break;
	case Difficulty::MEDIUM:
		isNewScore = addScore(newScore, mediumScores);
		break;
	case Difficulty::HARD:
		isNewScore = addScore(newScore, hardScores);
		break;
	case Difficulty::WHOA:
		isNewScore = addScore(newScore, whoaScores);
		break;
	}
	return isNewScore;
}

bool HighScore::addScore(int score, std::vector<std::pair<std::string, int>>& scores)
{
	for (std::vector<std::pair<std::string, int>>::iterator it = scores.begin(); it != scores.end(); ++it) {
		if (score == it->second) return false;
	}
	bool isNewScore = false;
	scores.push_back(std::make_pair("AAA",score));
	std::sort(scores.begin(), scores.end(), [](const std::pair<std::string, int> &p1, const std::pair<std::string, int> &p2)
	{
		return p1.second > p2.second;
	});
	if (scores[5].second != score) isNewScore = true;
	scores.pop_back();
	return isNewScore;
}

void HighScore::addInitials(std::string inputText)
{
	switch (gameDifficulty)
	{
	case Difficulty::EASY:
		for (std::vector<std::pair<std::string, int>>::iterator it = easyScores.begin(); it != easyScores.end(); ++it) {
			if (it->second == score) it->first = inputText;
		}
		break;
	case Difficulty::MEDIUM:
		for (std::vector<std::pair<std::string, int>>::iterator it = mediumScores.begin(); it != mediumScores.end(); ++it) {
			if (it->second == score) it->first = inputText;
		}
		break;
	case Difficulty::HARD:
		for (std::vector<std::pair<std::string, int>>::iterator it = hardScores.begin(); it != hardScores.end(); ++it) {
			if (it->second == score) it->first = inputText;
		}
		break;
	case Difficulty::WHOA:
		for (std::vector<std::pair<std::string, int>>::iterator it = whoaScores.begin(); it != whoaScores.end(); ++it) {
			if (it->second == score) it->first = inputText;
		}
		break;
	}
	
}

std::vector<std::pair<std::string, int>> HighScore::getEasyScores()
{
	return easyScores;
}

std::vector<std::pair<std::string, int>> HighScore::getMediumScores()
{
	return mediumScores;
}

std::vector<std::pair<std::string, int>> HighScore::getHardScores()
{
	return hardScores;
}

std::vector<std::pair<std::string, int>> HighScore::getWhoaScores()
{
	return whoaScores;
}