#include "Snake.h"
#include <assert.h>

Snake::Snake( const Location& loc )
{
	segments.push_back(new Segment());
	segments[0]->InitHead( loc );
}

Snake::~Snake()
{
	for (auto& s : segments)
	{
		delete s;
		s = nullptr;
	}
	segments.clear();
}

void Snake::MoveBy( const Location& delta_loc )
{
	for( int i = segments.size() - 1; i > 0; --i )
	{
		segments[i]->Follow( *segments[i - 1] );
	}
	segments[0]->MoveBy( delta_loc );
}

Location Snake::GetNextHeadLocation( const Location& delta_loc ) const
{
	Location l( segments[0]->GetLocation() );
	l.Add( delta_loc );
	return l;
}

void Snake::GrowAndMoveBy( const Location& delta_loc )
{
	if( segments.size() < nSegmentsMax )
	{
		int segIndex = segments.size();
		segments.push_back(new Segment());
		segments[segIndex]->InitBody(bodyColors[segIndex % nBodyColors]);
	}
	MoveBy( delta_loc );
}

void Snake::Draw( Board & brd ) const
{
	for( int i = 0; i < segments.size(); ++i )
	{
		segments[i]->Draw( brd );
	}
}

bool Snake::IsInTileExceptEnd( const Location& target ) const
{
	for( int i = 0; i < segments.size() - 1; ++i )
	{
		if( segments[i]->GetLocation() == target )
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsInTile( const Location& target ) const
{
	for (int i = 0; i < segments.size(); ++i)
	{
		if (segments[i]->GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

void Snake::Segment::InitHead( const Location& in_loc )
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody( Color c_in )
{
	c = c_in;
}

void Snake::Segment::Follow( const Segment& next )
{
	loc = next.loc;
}

void Snake::Segment::MoveBy( const Location& delta_loc )
{
	assert( abs( delta_loc.x ) + abs( delta_loc.y ) == 1 );
	loc.Add( delta_loc );
}

void Snake::Segment::Draw( Board& brd ) const
{
	brd.DrawCell( loc,c );
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
