#include "Maze.h"

Maze::Maze(string name, size_t maxSteps, size_t rowsNum, size_t colsNum, MazeBoard board, size_t playerLocation[2]) :
	m_name(name), m_maxSteps(maxSteps), m_rowsNum(rowsNum), m_colsNum(colsNum), m_board(board)
{
	m_playerLocation[0] = playerLocation[0];
	m_playerLocation[1] = playerLocation[1];
}

void Maze::printBoard()
{
	for (size_t i = 0; i < m_rowsNum; i++) {
		for (size_t j = 0; j < m_colsNum; j++)
			cout << m_board[i][j];
		cout << endl;
	}
}
