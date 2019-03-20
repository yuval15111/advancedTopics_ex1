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
	name = getName(m_fin);
	maxSteps = getIntValue(m_fin, "MaxSteps");
	rowsNum = getIntValue(m_fin, "Cols");
	colsNum = getIntValue(m_fin, "Rows");
	board = getBoard(m_fin, rowsNum, colsNum);
	Maze* maze = new Maze(name, maxSteps, rowsNum, colsNum, board);
}

string FileHandler::getName(ifstream& fin) {
	string line;
	if (getline(fin, line)) {
		return line;
	}
	return nullptr;
}
int FileHandler::getIntValue(ifstream& fin, const char * input) {
	string line;
	if (getline(fin, line)) {
		vector<string> splitted = split(line, ' ');
		if (splitted.size() != 3 || splitted[0].compare(input) != 0 || splitted[1].compare("=") != 0)
			// handle errors
			return -1;
		int result = atoi(splitted[2].copy); // MAYBE THERE IS A BETTER SOLUTION
		if (result == 0) return -1;
		// handle error of illegal number input
		return result;
	}
	return -1;
}

vector<string> FileHandler::split(string str, char delimiter) {
	vector<string> v = {};
	int currSpaceIndex = 0, lastSpaceIndex = - 1;
	while ((currSpaceIndex = str.find(delimiter)) != std::string::npos) {
		if (currSpaceIndex != 0) {
			v.push_back(str.substr(lastSpaceIndex + 1, currSpaceIndex));
			lastSpaceIndex = currSpaceIndex;
		}
	}
	return v;
}

MazeBoard FileHandler::getBoard(ifstream& fin, int rows, int cols) {
	MazeBoard board;
	MazeRow row;
	string line;
	
	for (int i = 0; i < rows; i++) {
		if (getline(fin, line)) {

			for (int j = 0; j < cols; j++) {
				row[j] = line[j];

			}
			
		}
		else {
			// finish
		}
		board[i] = row;
	}
	return board;
}