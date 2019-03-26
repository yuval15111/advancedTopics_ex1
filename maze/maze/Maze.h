#include <string>
#include <vector>
#include <iostream>
#include "MainAux.h"

using namespace std;
using MazeRow = std::vector<char>;
using MazeBoard = std::vector<MazeRow>;

class Maze {
private:
	string m_name;
	size_t m_maxSteps;
	size_t m_rowsNum, m_colsNum;
	MazeBoard m_board;
	size_t m_playerLocation[2];

public:
	ParsingErrorType m_error;
	Maze(string name, size_t maxSteps, size_t rowsNum, size_t colsNum, MazeBoard board, size_t playerLocation[2], ParsingErrorType error);
	void printBoard();
	inline ParsingErrorType getErrors() { return m_error; }
};