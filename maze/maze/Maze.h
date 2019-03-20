#include <string>
#include <vector>
#include <iostream>

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
	Maze(string name, size_t maxSteps, size_t rowsNum, size_t colsNum, MazeBoard board, size_t playerLocation[2]);
	void printBoard();
};