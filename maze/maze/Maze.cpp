#include "Maze.h"

Maze::Maze(string name, size_t maxSteps, size_t rowsNum, size_t colsNum,
		   MazeBoard board, Coord playerLocation, Coord endLocation) :
	m_name(name), m_maxSteps(maxSteps), m_rowsNum(rowsNum), m_colsNum(colsNum), m_board(board)
{
	m_playerLocation.set(playerLocation.row, playerLocation.col);
	m_endLocation.set(endLocation.row, endLocation.col);
}

/*Maze::~Maze()
{
	for (size_t i = 0; i < m_rowsNum; i++) {
		delete(&m_board[i]);
	}
	delete(&m_board);
	delete(&m_playerLocation);
}*/

void Maze::printBoard()
{
	for (size_t i = 0; i < m_rowsNum; i++) {
		for (size_t j = 0; j < m_colsNum; j++) {
			if (m_playerLocation.row != i || m_playerLocation.col != j) {
				cout << m_board[i][j];
			}
			else {
				cout << "@";
			}
		}
			
		cout << endl;
	}
	cout << endl;
	cout << endl;
	cout << endl;
}

void Maze::execute(Action a, bool undo)
{
	a = undo ? !a : a;
	switch (a) {
	case Action::UP:
		m_playerLocation.row += m_rowsNum - 1;
		m_playerLocation.row %= m_rowsNum;
		break;
	case Action::DOWN:
		m_playerLocation.row++;
		m_playerLocation.row %= m_rowsNum;
		break;
	case Action::LEFT:
		m_playerLocation.col += m_colsNum - 1;
		m_playerLocation.col %= m_colsNum;
		break;
	case Action::RIGHT:
		m_playerLocation.col++;
		m_playerLocation.col %= m_colsNum;
		break;
	case Action::BOOKMARK:
		//handle
		break;
	}
}

bool Maze::hasReachedDestination()
{
	return m_playerLocation == m_endLocation;
}
