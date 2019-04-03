#ifndef PLAYER_H
#define PLAYER_H

#include "MainAux.h"

class Player {
	
private:
	size_t					m_numOfSteps = 0;
	size_t					m_rowsNum = MAX_INT;
	size_t					m_colsNum = MAX_INT;
	Coordinate				m_bookmark;
	vector <Coordinate>		m_path;
	Coordinate				m_location;
	map <Coordinate,char>	m_mazeMapping;
	Action					m_action;

	void					updateLocation(const bool undo = false);
	void					updatePath(const bool undo = false);
	void					updateMapping(const Coordinate loc, char c);
	void					generateAction(vector<Action> exclusions);
	bool					inVector(vector<Action> exclusions);
	vector<Action>			findExclusions();

public:
	Player();
	Action					move();
	void					hitWall();
	void					hitBookmark();
	inline const Coordinate	getLocation() { return m_location; }
	
};

#endif