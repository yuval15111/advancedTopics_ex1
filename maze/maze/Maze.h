#ifndef MAZE_H
#define MAZE_H

#include "MainAux.h"

class Maze {
public:
	string m_name;
	size_t m_maxSteps;
private:
	size_t m_rowsNum, m_colsNum;
	MazeBoard m_board;
	Coord m_playerLocation;
	Coord m_endLocation;

public:
	Maze(string name, size_t maxSteps, size_t rowsNum, size_t colsNum, MazeBoard board, Coord playerLocation, Coord endLocation);
	//~Maze();
	void printBoard();
	bool hasReachedDestination();
	void execute(Action a, bool undo = false);
	inline const Coord getPlayerLocation() { return m_playerLocation; }
	inline const char getCoordValue(const Coord & c) { return m_board[c.row][c.col]; }
};

#endif