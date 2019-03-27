#include "FileHandler.h"

FileHandler::~FileHandler()
{
	delete(&m_fin);
	delete(&m_fout);
}

Maze * FileHandler::parseInput(ParsingErrorType & errors) {
	MazeBoard board;
	string name;
	size_t maxSteps;
	size_t rowsNum, colsNum;
	size_t playerLocation[2] = { 0, 0 };

	name = getName(m_fin);
	if ((maxSteps = getIntValue(m_fin, "MaxSteps")) == -1) {
		errors = errors | ParsingErrorType::MaxStepsError;
	}
	if ((rowsNum = getIntValue(m_fin, "Rows")) == -1) {
		errors = errors | ParsingErrorType::RowsError;
	}
	if ((colsNum = getIntValue(m_fin, "Cols")) == -1) {
		errors = errors | ParsingErrorType::ColsError;
	}
	board = getBoard(m_fin, rowsNum, colsNum, playerLocation, errors);
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
			return -1;
		size_t result = (size_t)atoi(splitted[2].c_str()); // TODO: MAYBE THERE IS A BETTER SOLUTION
		if (result == 0) return -1;
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

MazeBoard FileHandler::getBoard(ifstream& fin, size_t rows, size_t cols, size_t playerLocation[2], ParsingErrorType & errors) {
	MazeBoard board;
	
	string line;
	bool seenPlayerChar = false, seenEndChar = false;
	
	for (size_t i = 0; i < rows; i++) {
		MazeRow row;
		if (getline(fin, line)) {
			for (int j = 0; j < line.length(); j++) {
				row.push_back(line[j]);
				if (line[j] == '@') {
					if (!seenEndChar) {
						playerLocation[0] = i;
						playerLocation[1] = j;
						seenEndChar = true;
					}
					else { // only one player char allowed
						errors = errors | ParsingErrorType::MoreThanOnePlayerChar;
					}
				}
				if (line[j] == '$') {
					if (!seenPlayerChar) {
						seenPlayerChar = true;
					}
					else { // only one end char allowed
						errors = errors | ParsingErrorType::MoreThanOneEndChar;
					}
				}
			}
			for (size_t j = line.length(); j < cols; j++) {
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
	if (!seenPlayerChar) {
		errors = errors | ParsingErrorType::MissingPlayerChar;
	}
	if (!seenEndChar) {
		errors = errors | ParsingErrorType::MissingEndChar;
	}
	return board;
}