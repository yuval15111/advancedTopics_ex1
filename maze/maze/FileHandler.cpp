#include "FileHandler.h"

/*FileHandler::~FileHandler()
{
	delete(&m_fin);
	delete(&m_fout);
	delete(&m_errors.fmap);
	delete(&m_errors.list);
	delete(&m_errors);
}*/

FileHandler::FileHandler(char * argv[]) : m_fin(argv[1]), m_fout(argv[2]) { // TODO: Check IO Erorrs
	if (!m_fin.good()) {
		pushError(ErrorType::BadInputAddress, argv[1]);
	}
	if (!m_fout.good()) {
		pushError(ErrorType::BadOutputAddress, argv[2]);
	}
}

Maze * FileHandler::parseInput() {
	if (!checkErrors(m_errors)) { // IO Errors - can't parse!
		return nullptr;
	}
	MazeBoard board;
	string name;
	size_t maxSteps;
	size_t rowsNum, colsNum;
	Coord playerLocation = { 0, 0 };
	Coord endLocation = { 0, 0 };

	name = getName();
	maxSteps = getIntValue(MAXSTEPS, ErrorType::MaxStepsError);
	rowsNum = getIntValue(ROWS, ErrorType::RowsError);
	colsNum = getIntValue(COLS, ErrorType::ColsError);
	if (checkErrors(m_errors)) { // lines 2-4 are valid
		board = getBoard(rowsNum, colsNum, playerLocation, endLocation);
		if (checkErrors(m_errors)) { // maze file is valid
			Maze * maze = new Maze(name, maxSteps, rowsNum, colsNum, board, playerLocation, endLocation);
			return maze;
		}
	}
	return nullptr; // maze file is not valid
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
			pushError(error, line);
			return -1;
		}
		size_t result = (size_t)atoi(splitted[2].c_str()); // TODO: MAYBE THERE IS A BETTER SOLUTION
		if (result == 0) {
			pushError(error, line);
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

MazeBoard FileHandler::getBoard(size_t rows, size_t cols, Coord & playerLocation, Coord & endLocation) {
	MazeBoard board;
	
	string line;
	bool seenPlayerChar = false, seenEndChar = false;
	
	for (size_t i = 0; i < rows; i++) {
		MazeRow row;
		if (getline(m_fin, line)) {
			for (size_t j = 0; j < line.length(); j++) {
				
				if (line[j] == PLAYER_CHAR) {
					if (!seenPlayerChar) {
						playerLocation.set(i, j);
						seenPlayerChar = true;
						line[j] = SPACE_CHAR; // not necessary as '@' character
					}
					else { // only one player char allowed
						pushError(ErrorType::MoreThanOnePlayerChar, nullptr);
					}
				}
				else if (line[j] == END_CHAR) {
					if (!seenEndChar) {
						endLocation.set(i, j);
						seenEndChar = true;
					}
					else { // only one end char allowed
						pushError(ErrorType::MoreThanOneEndChar, nullptr);
					}
				}
				else if (line[j] != SPACE_CHAR && line[j] != WALL_CHAR) { // other chars are invalid
					string str = "000";
					str[0] = line[j];
					str[1] = (char)i;
					str[2] = (char)j;
					pushError(ErrorType::WrongChar, str);
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