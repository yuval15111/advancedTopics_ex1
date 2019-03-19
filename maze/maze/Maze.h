#include <string>
#include <vector>

using namespace std;
using MazeRow = std::vector<char>;
using MazeBoard = std::vector<MazeRow>;

class Maze {
private:
	string m_name;
	int m_maxSteps;
	int m_rowsNum, m_colsNum;
	MazeBoard m_board;
public:
	Maze(string name, int maxSteps, int rowsNum, int colsNum, MazeBoard board) :
		m_name(name), m_maxSteps(maxSteps), m_rowsNum(rowsNum), m_colsNum(colsNum), m_board(board) {};
};