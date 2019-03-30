#ifndef PLAYER_H
#define PLAYER_H

#include "Maze.h"

class Player {
	
private:
	size_t m_numOfSteps = 0;
	size_t m_rowsNum = INT_MAX;
	size_t m_colsNum = INT_MAX;
	Coord m_bookmark;
	vector <Coord> m_path;
	Coord m_currentLocation;
	map <Coordinate, char> m_mazeMapping;

public:
	Player();
	Action move();
	void hitWall(Action a);
	void hitBookmark();

private:
	void bookmark();
	void updatePath(bool undo = false); // we will call from move
	void updateMapping(Coord loc, char c);
	Action getLastRelativePoision();
	Action shuffle(vector<Action> exclusions);
	bool inVector(Action action, vector<Action> exclusions);
	void findExclusions(vector<Action> & exclusions);
	void updateLocation(Action a, bool undo = false);
};

#endif