#pragma once
#include "Location.h"
#include <string>
#include <fstream>
#include <sstream>

class Settings
{
public:
	Settings(std::string filename)
	{
		ReadSettings(filename);
	}
	Settings& ReadSettings(std::string filename)
	{
		std::ifstream fin(filename);
		std::string settings;
		while (std::getline(fin, settings))
		{
			if (settings[0] != '#')
			{
				std::string key = settings.substr(0, settings.find('='));
				std::string value = settings.substr(settings.find('=') + 1);
				if (key == "tile-size")
				{
					tileSize = std::stoi(value);
				}
				else if (key == "board-size")
				{
					boardSize.x = std::stoi(value.substr(0, value.find(' ')));
					boardSize.y = std::stoi(value.substr(value.find(' ') + 1));
				}
				else if (key == "speedup-rate")
				{
					speedupRate = std::stof(value);
				}
				else if (key == "poison-amount")
				{
					poisonAmount = std::stoi(value);
				}
				else if (key == "food-amount")
				{
					foodAmount = std::stoi(value);
				}
			}
		}

		return *this;
	}
	const int TileSize() const
	{
		return tileSize;
	}
	const Location& BoardSize() const
	{
		return boardSize;
	}
	const float SpeedupRate() const
	{
		return speedupRate;
	}
	const int PoisonAmount() const
	{
		return poisonAmount;
	}
	const int FoodAmount() const
	{
		return foodAmount;
	}
private:
	int tileSize;
	Location boardSize;
	float speedupRate;
	int poisonAmount;
	int foodAmount;
};

