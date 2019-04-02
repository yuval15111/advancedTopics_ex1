#include "Manager.h"

/*Manager::~Manager()
{
	for (size_t i = 0; i < m_rowsNum; i++) {
		delete(&m_board[i]);
	}
	delete(&m_board);
	delete(&m_playerLocation);
}*/

void Manager::printBoard()
{
	for (size_t i = 0; i < m_rowsNum; i++) {
		for (size_t j = 0; j < m_colsNum; j++) {
			if (m_playerLocation.first != i || m_playerLocation.second != j) {
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
}

void Manager::execute(Action a, const bool undo)
{
	a = undo ? !a : a;
	switch (a) {
	case Action::UP:
		m_playerLocation.first += m_rowsNum - 1;
		m_playerLocation.first %= m_rowsNum;
		break;
	case Action::DOWN:
		m_playerLocation.first++;
		m_playerLocation.first %= m_rowsNum;
		break;
	case Action::LEFT:
		m_playerLocation.second += m_colsNum - 1;
		m_playerLocation.second %= m_colsNum;
		break;
	case Action::RIGHT:
		m_playerLocation.second++;
		m_playerLocation.second %= m_colsNum;
		break;
	default:
		break;
	}
}

