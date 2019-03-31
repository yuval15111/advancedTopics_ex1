#ifndef PLAYER_H
#define PLAYER_H

#include "MainAux.h"

class Player {
	
private:
	size_t					m_numOfSteps = 0;
	size_t					m_rowsNum = INT_MAX;
	size_t					m_colsNum = INT_MAX;
	Coordinate				m_bookmark;
	vector <Coordinate>		m_path;
	Coordinate				m_location;
	map <Coordinate,char>	m_mazeMapping;
	Action					m_action;

	void					updateLocation(const bool undo = false);
	void					updatePath(const bool undo = false); // we will call from move
	void					updateMapping(const Coordinate loc, char c);
	void					generateAction(vector<Action> exclusions);
	bool					inVector(vector<Action> exclusions);
	vector<Action>			findExclusions();

public:
	Player();
	//~Player();
	Action					move();
	void					hitWall();
	void					hitBookmark();
	inline const Coordinate	getLocation() { return m_location; }
	
};

#endif