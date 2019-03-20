#include "FileHandler.h"

FileHandler::~FileHandler()
{
	delete(&m_fin);
	delete(&m_fout);
}

Maze * FileHandler::parseInput() {
	MazeBoard board;
	string name;
	size_t maxSteps;
	size_t rowsNum, colsNum;
	size_t playerLocation[2] = { 0, 0 };

	name = getName(m_fin);
	maxSteps = getIntValue(m_fin, "MaxSteps");
	rowsNum = getIntValue(m_fin, "Rows");
	colsNum = getIntValue(m_fin, "Cols");
	board = getBoard(m_fin, rowsNum, colsNum, playerLocation);
	Maze* maze = new Maze(name, maxSteps, rowsNum, colsNum, board, playerLocation);
	return maze;
}

string FileHandler::getName(ifstream& fin) {
	string line;
	if (getline(fin, line)) {
		return line;
	}
	return nullptr;
}
size_t FileHandler::getIntValue(ifstream& fin, const char * input) {
	string line;
	if (getline(fin, line)) {
		vector<string> splitted = split(line, ' ');
		if (splitted.size() != 3 || splitted[0].compare(input) != 0 || splitted[1].compare("=") != 0)
			// handle errors
			return -1;
		size_t result = (size_t)atoi(splitted[2].c_str()); // MAYBE THERE IS A BETTER SOLUTION
		if (result == 0) return -1;
		// handle error of illegal number input
		return result;
	}
	return -1;
}

vector<string> FileHandler::split(string str, char delimiter) {
	vector<string> v = {};
	size_t currSpaceIndex = 0, lastSpaceIndex = - 1;
	while ((currSpaceIndex = str.find(delimiter, lastSpaceIndex + 1)) != std::string::npos) {
		if (currSpaceIndex != 0) {
			v.push_back(str.substr(lastSpaceIndex + 1, currSpaceIndex - lastSpaceIndex - 1));
			lastSpaceIndex = currSpaceIndex;
		}
	}
	v.push_back(str.substr(lastSpaceIndex + 1));
	return v;
}

MazeBoard FileHandler::getBoard(ifstream& fin, size_t rows, size_t cols, size_t playerLocation[2]) {
	MazeBoard board;
	
	string line;
	
	for (size_t i = 0; i < rows; i++) {
		MazeRow row;
		if (getline(fin, line)) {
			for (int j = 0; j < line.length(); j++) {
				row.push_back(line[j]);
				if (line[j] == '@') {
					playerLocation[0] = i;
					playerLocation[1] = j;
				}
			}
			for (int j = line.length(); j < cols; j++) {
				row.push_back(' ');
			}
		}
		else {
			for (size_t j = 0; j < cols; j++) {
				row.push_back(' ');
			}
		}
		board.push_back(row);
	}
	return board;
}