#ifndef MANAGER_H
#define MANAGER_H

#include "Player.h"

class Manager {
public:
	
private:
	string 					m_name;
	size_t 					m_maxSteps, m_rowsNum, m_colsNum;
	MazeBoard 				m_board;
	Coordinate 				m_playerLocation;
	Coordinate				m_endLocation;
	Coordinate				m_bookmark;
	Player *				m_player = nullptr;

public:
	Manager(string name, size_t maxSteps, size_t rowsNum, size_t colsNum,
			MazeBoard board, Coordinate playerLocation, Coordinate endLocation) :
			m_name(name), m_maxSteps(maxSteps), m_rowsNum(rowsNum),
			m_colsNum(colsNum),	m_board(board), m_playerLocation(playerLocation),
			m_endLocation(endLocation),	m_bookmark(0, 0) {};
	~Manager();

	inline void				bookmark() { m_bookmark = m_playerLocation; }
	void					execute(Action a, const bool undo = false);
	inline char				getCoordValue() { return m_board[m_playerLocation.first][m_playerLocation.second]; }
	inline bool				playerHitsEndChar() { return getCoordValue() == END_CHAR; }
	inline bool				playerHitsWallChar() { return getCoordValue() == WALL_CHAR; }
	inline bool				playerHitsBookmark() { return m_playerLocation == m_bookmark; }
	inline size_t			getMaxSteps() { return m_maxSteps; }
	void					printBoard();
	vector<char>			play();
};

#endif