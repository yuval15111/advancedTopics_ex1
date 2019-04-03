#ifndef PLAYER_H
#define PLAYER_H

#include "MainAux.h"

#define STEPS_NUM_TO_BOOKMARK 25
#define MAX_SAME_ACTION_NUM 30

class Player {
	
private:
	int					m_rowsNum = MAX_INT;
	int					m_colsNum = MAX_INT;
	Coordinate				m_bookmark;
	vector <Action>			m_actionVector;
	Coordinate				m_location;
	map <Coordinate,char>	m_mazeMapping;
	Action					m_action;
	int						m_currActionCounter = 0;

	void					updateLocation(const bool undo = false);
	void					updateMapping(const Coordinate loc, char c);
	void					generateAction(vector<Action> exclusions);
	bool					inVector(vector<Action> exclusions);
	vector<Action>			findExclusions();
	void					arrangeMapping(bool rows);
	char					getCharByDirection(Action a);
	inline int				numOfSteps() { return (int)m_actionVector.size(); }
	Coordinate				getCoordinateByAction(Coordinate loc, const Action & a);

public:
	Player();
	Action					move();
	void					hitWall();
	void					hitBookmark();
	inline const Coordinate	getLocation() { return m_location; }
	
};

#endif