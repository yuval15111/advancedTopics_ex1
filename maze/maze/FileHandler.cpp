#include "FileHandler.h"

FileHandler::~FileHandler()
{
	delete(&m_fin);
	delete(&m_fout);
}

Maze FileHandler::parseInput() {
	MazeBoard board;
	string name;
	int maxSteps;
	int rowsNum, colsNum;
	string line;
	name = getName(m_fin, line);
	maxSteps = getMaxSteps(m_fin, line);
	rowsNum = getRowsNum(m_fin, line);
	colsNum = getColsNum(m_fin, line);
	board = getBoard(m_fin, line);
	Maze* maze = new Maze(name, maxSteps, rowsNum, colsNum, board);
}

string FileHandler::getName(ifstream& fin, string line) {
	if (getline(fin, line)) {
		return line;
	}
	return nullptr;
}
int FileHandler::getMaxSteps(ifstream& fin, string line) {
	if (getline(fin, line)) {
		vector<string> splitted = split(line, ' ');
	}
	return -1;
}
int FileHandler::getRowsNum(ifstream& fin, string line) {
	if (getline(fin, line)) {
		return line;
	}
	return -1;
}
int FileHandler::getColsNum(ifstream& fin, string line) {
	if (getline(fin, line)) {
		return line;
	}
	return -1;
}
MazeBoard FileHandler::getBoard(ifstream& fin, string line) {

}