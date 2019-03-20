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
	maxSteps = getIntValue(m_fin, line, "MaxSteps");
	rowsNum = getIntValue(m_fin, line, "Cols");
	colsNum = getIntValue(m_fin, line, "Rows");
	board = getBoard(m_fin, line, rowsNum, colsNum);
	Maze* maze = new Maze(name, maxSteps, rowsNum, colsNum, board);
}

string FileHandler::getName(ifstream& fin, string line) {
	if (getline(fin, line)) {
		return line;
	}
	return nullptr;
}
int FileHandler::getIntValue(ifstream& fin, string line, const char * input) {
	if (getline(fin, line)) {
		vector<string> splitted = split(line, ' ');
		if (splitted.size() != 3 || !splitted[0].equals(input) || !splitted[1].equals("="))
			// handle errors
			return -1;
		int result = atoi(splitted[2]);
		if (result == 0) return -1;
		// handle error of illegal number input
		return result;
	}
	return -1;
}

vector<string> FileHandler::split(string str, char delimiter) {
	vector<string> v = {};
	while (str.find(delimiter) != std::string::npos) {

	}
}

MazeBoard FileHandler::getBoard(ifstream& fin, string line, int rows, int cols) {
	MazeBoard board;
	MazeRow row;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			getline(fin, line)
		}
	}
}