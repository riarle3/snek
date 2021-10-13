#pragma once

#include "Graphics.h"
#include "Location.h"
#include <random>
#include "Settings.h"

class Board
{
public:
	enum class CellContents
	{
		Empty,
		Obstacle,
		Food,
		Poison
	};
public:
	Board( Graphics& gfx, Settings& stn );
	~Board();
	void DrawCell( const Location& loc,Color c );
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard( const Location& loc ) const;
	CellContents GetContents( const Location& loc ) const;
	void ConsumeContents( const Location& loc );
	void SpawnContents( std::mt19937& rng,const class Snake& snake,CellContents contents );
	void DrawBorder();
	void DrawCells();
private:
	Graphics& gfx;
	static constexpr Color borderColor = Colors::Blue;
	static constexpr Color obstacleColor = Colors::Gray;
	static constexpr Color poisonColor = { 64,8,64 };
	static constexpr Color foodColor = Colors::Red;
	static constexpr int cellPadding = 1;
	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;
	int dimension;
	int width;
	int height;
	int x;
	int y;
	CellContents* contents;
};