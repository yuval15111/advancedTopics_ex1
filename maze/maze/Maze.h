#ifndef MAZE_H
#define MAZE_H

#include "MainAux.h"

class Maze {
private:
	string m_name;
	size_t m_maxSteps;
	size_t m_rowsNum, m_colsNum;
	MazeBoard m_board;
	Coordinate m_playerLocation;

public:
	Maze(string name, size_t maxSteps, size_t rowsNum, size_t colsNum, MazeBoard board, Coordinate playerLocation);
	//~Maze();
	void printBoard();
};

#endif