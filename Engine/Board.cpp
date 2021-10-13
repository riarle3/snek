#include "Board.h"
#include "Snake.h"
#include <assert.h>

Board::Board( Graphics& gfx, Settings& stn )
	:
	gfx( gfx ),
	dimension(stn.TileSize()),
	width(stn.BoardSize().x),
	height(stn.BoardSize().y),
	x((gfx.ScreenWidth - width * dimension) / 2),
	y((gfx.ScreenHeight - height * dimension) / 2),
	contents(new CellContents[width * height])
{
	for (int i = 0; i < width * height; i++)
	{
		contents[i] = CellContents::Empty;
	}
}

Board::~Board()
{
	delete[] contents;
	contents = nullptr;
}

void Board::DrawCell( const Location & loc,Color c )
{
	assert( loc.x >= 0 );
	assert( loc.x < width );
	assert( loc.y >= 0 );
	assert( loc.y < height );

	const int off_x = x + borderWidth + borderPadding;
	const int off_y = y + borderWidth + borderPadding;

	gfx.DrawRectDim( loc.x * dimension + off_x + cellPadding,loc.y * dimension + off_y + cellPadding,dimension - cellPadding * 2,dimension - cellPadding * 2,c );
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::IsInsideBoard( const Location & loc ) const
{
	return loc.x >= 0 && loc.x < width &&
		loc.y >= 0 && loc.y < height;
}

Board::CellContents Board::GetContents( const Location& loc ) const
{
	return contents[loc.y * width + loc.x];
}

void Board::ConsumeContents( const Location& loc )
{
	assert( GetContents( loc ) == CellContents::Food 
			|| GetContents( loc ) == CellContents::Poison );
	contents[loc.y * width + loc.x] = CellContents::Empty;
}

void Board::SpawnContents( std::mt19937 & rng,const Snake & snake,CellContents contentsType )
{
	std::uniform_int_distribution<int> xDist( 0,GetGridWidth() - 1 );
	std::uniform_int_distribution<int> yDist( 0,GetGridHeight() - 1 );

	Location newLoc;
	do
	{
		newLoc.x = xDist( rng );
		newLoc.y = yDist( rng );
	}
	while( snake.IsInTile( newLoc ) || GetContents( newLoc ) != CellContents::Empty );

	contents[newLoc.y * width + newLoc.x] = contentsType;
}

void Board::DrawBorder()
{
	const int top = y;
	const int left = x;
	const int bottom = top + (borderWidth + borderPadding) * 2 + height * dimension;
	const int right = left + (borderWidth + borderPadding) * 2 + width * dimension;

	// top
	gfx.DrawRect( left,top,right,top + borderWidth,borderColor );
	// left
	gfx.DrawRect( left,top + borderWidth,left + borderWidth,bottom - borderWidth,borderColor );
	// right
	gfx.DrawRect( right - borderWidth,top + borderWidth,right,bottom - borderWidth,borderColor );
	// bottom
	gfx.DrawRect( left,bottom - borderWidth,right,bottom,borderColor );
}

void Board::DrawCells()
{
	for( int y = 0; y < height; y++ )
	{
		for( int x = 0; x < width; x++ )
		{
			switch( GetContents( { x,y } ) )
			{
			case Board::CellContents::Obstacle:
				DrawCell( { x,y },obstacleColor );
				break;
			case Board::CellContents::Food:
				DrawCell( { x,y },foodColor );
				break;
			case Board::CellContents::Poison:
				DrawCell( { x,y },poisonColor );
				break;
			}
		}
	}
}
