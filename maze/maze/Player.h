#ifndef PLAYER_H
#define PLAYER_H

#include "Maze.h"

class Player {
	
private:
	size_t m_numOfSteps = 0;
	Coord m_bookmark;
	vector <Coord> m_path;
	Coord m_currentLocation;
	map <Coord, char> m_mazeMapping;

public:
	Player();

private:
	Action move();
	void hitWall();
	void bookmark();
	void hitBookmark();
	void updatePath(); // we will call from move
	void updateMapping(Coord loc, char c);
};

#endif