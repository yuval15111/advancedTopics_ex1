#include "FileHandler.h"

/*FileHandler::~FileHandler()
{
	delete(&m_fin);
	delete(&m_fout);
	delete(&m_errors.fmap);
	delete(&m_errors.list);
	delete(&m_errors);
}*/

FileHandler::FileHandler(int argc, char * argv[]) : m_fin(argv[1]), m_fout(argv[2]) {
	if (argc == 1) {
		pushError(ErrorType::MissingInput, argv[1]);
	}
	else if (argc == 2) {
		pushError(ErrorType::MissingOutput, argv[2]);
	}
	else { // argc >= 3
		if (!m_fin.good()) {
			pushError(ErrorType::BadInputAddress, nullptr);
		}
		if (!m_fout.good()) {
			pushError(ErrorType::BadOutputAddress, nullptr);
		}
	}
	checkErrors(m_errors);
}

Maze * FileHandler::parseInput() {
	MazeBoard board;
	string name;
	size_t maxSteps;
	size_t rowsNum, colsNum;
	size_t playerLocation[2] = { 0, 0 };

	name = getName();

	maxSteps = getIntValue(MAXSTEPS, ErrorType::MaxStepsError);
	rowsNum = getIntValue(ROWS, ErrorType::RowsError);
	colsNum = getIntValue(COLS, ErrorType::ColsError);

	board = getBoard(rowsNum, colsNum, playerLocation);
	Maze* maze = new Maze(name, maxSteps, rowsNum, colsNum, board, playerLocation);
	checkErrors(m_errors);
	return maze;
}

string FileHandler::getName() {
	string line;
	if (getline(m_fin, line)) {
		return line;
	}
	return nullptr;
}
size_t FileHandler::getIntValue(const char * input, const ErrorType error) {
	string line;
	if (getline(m_fin, line)) {
		vector<string> splitted = split(line, SPACE_CHAR);
		if (splitted.size() != 3 || splitted[0].compare(input) != 0 || splitted[1].compare("=") != 0) {
			return -1;
		}
		size_t result = (size_t)atoi(splitted[2].c_str()); // TODO: MAYBE THERE IS A BETTER SOLUTION
		if (result == 0) {
			pushError(ErrorType::MissingOutput, line);
			return -1;
		}
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

MazeBoard FileHandler::getBoard(size_t rows, size_t cols, size_t playerLocation[2]) {
	MazeBoard board;
	
	string line;
	bool seenPlayerChar = false, seenEndChar = false;
	
	for (size_t i = 0; i < rows; i++) {
		MazeRow row;
		if (getline(m_fin, line)) {
			for (int j = 0; j < line.length(); j++) {
				
				if (line[j] == PLAYER_CHAR) {
					if (!seenPlayerChar) {
						playerLocation[0] = i;
						playerLocation[1] = j;
						seenPlayerChar = true;
					}
					else { // only one player char allowed
						pushError(ErrorType::MoreThanOnePlayerChar, nullptr);
					}
				}
				else if (line[j] == END_CHAR) {
					if (!seenEndChar) {
						seenEndChar = true;
					}
					else { // only one end char allowed
						pushError(ErrorType::MoreThanOneEndChar, nullptr);
					}
				}
				else if (line[j] != SPACE_CHAR && line[j] != WALL_CHAR) { // other chars are invalid
					string str;
					pushError(ErrorType::WrongChar, to_string(line[j]) + to_string(i) + to_string(j));
				}
				row.push_back(line[j]);
			}
			for (size_t j = line.length(); j < cols; j++) {
				row.push_back(SPACE_CHAR);
			}
		}
		else {
			for (size_t j = 0; j < cols; j++) {
				row.push_back(SPACE_CHAR);
			}
		}
		board.push_back(row);
	}
	if (!seenPlayerChar) {
		pushError(ErrorType::MissingPlayerChar, nullptr);
	}
	if (!seenEndChar) {
		pushError(ErrorType::MissingEndChar, nullptr);
	}
	return board;
}