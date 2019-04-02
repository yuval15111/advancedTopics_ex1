#include "FileHandler.h"

FileHandler::~FileHandler()
{
	m_fin.close();
	m_fout.close();
}

FileHandler::FileHandler(int argc, char * argv[]) {
	//const char * in = setAbsolute(argv, 1);
	//const char * out = setAbsolute(argv, 2);
	cout << "Before openning fin" << endl;
	m_fin.open(argv[1]);
	cout << "After openning fin, before opening fout" << endl;
	m_fout.open(argv[2]);
	cout << "After openning fout" << endl;
	if (argc == 1) {
		pushError(ErrorType::MissingInput, string());
		cout << "end1" << endl;
	}
	else if (argc == 2) {
		pushError(ErrorType::MissingOutput, string());
		cout << "end2" << endl;
	}
	else if (!m_fin.good()) {
		pushError(ErrorType::BadInputAddress, argv[1]);
		cout << "end3" << endl;
	}
	else if (!m_fout.good()) {
		pushError(ErrorType::BadOutputAddress, argv[2]);
		cout << "end4" << endl;
	}
	cout << "end5" << endl;
	checkErrors();
}

bool FileHandler::checkErrors() {
	if (m_errors.list.size() == 0) return true;
	m_errors.noErrors = false;
	for (ErrorList::iterator it = m_errors.list.begin(); it != m_errors.list.end(); ++it) {
		Func f = m_errors.fmap[it->first];
		string str = it->second;
		f(str);
	}
	m_errors.list.clear();
	return false;
}

Manager * FileHandler::parseInput() {
	string line;
	// Manager future fields
	MazeBoard board;
	string name;
	size_t maxSteps, rowsNum, colsNum;
	Coordinate playerLocation = make_pair(0, 0), endLocation = make_pair(0, 0);

	// Parsing begins here
	name = getName(line);
	maxSteps = getIntValue(MAXSTEPS, ErrorType::MaxStepsError, line);
	rowsNum = getIntValue(ROWS, ErrorType::RowsError, line);
	colsNum = getIntValue(COLS, ErrorType::ColsError, line);
	if (checkErrors()) { // no errors, lines 2-4 are valid
		board = getBoard(rowsNum, colsNum, playerLocation, endLocation, line);
		if (checkErrors()) // no errors, maze file is valid
			return new Manager(name, maxSteps, rowsNum, colsNum, board, playerLocation, endLocation);
		cout << "Bad maze in maze file:" << endl;
	}
	cout << "Bad maze in file header:" << endl;
	return nullptr; // maze file is not valid
}

string FileHandler::getName(string & line) {
	if (getline(m_fin, line)) {
		return line;
	}
	return nullptr;
}

size_t FileHandler::getIntValue(const string & input, const ErrorType error, string & line) {
	const regex reg("\\s*" + input + "\\s*=\\s*[1-9][0-9]*\\s*");
	const regex numReg("[1-9][0-9]*");
	smatch match;
	if (getline(m_fin, line)) {
		if (!regex_match(line, reg)) {
			pushError(error, line);
			return -1;
		}
		regex_search(line, match, numReg);
		return stoi(match[0]);
	}
	pushError(error, line);
	return -1;
}

MazeBoard FileHandler::getBoard(const size_t rows, const size_t cols, Coordinate & playerLocation, Coordinate & endLocation, string & line) {
	MazeBoard board;
	bool seenPlayerChar = false, seenEndChar = false;
	for (size_t i = 0; i < rows; i++) {
		MazeRow row;
		if (getline(m_fin, line)) {
			for (size_t j = 0; j < line.length(); j++) {
				if (line[j] == PLAYER_CHAR)
					handleSpecialChar(PLAYER_CHAR, playerLocation, i, j, seenPlayerChar, line, ErrorType::MoreThanOnePlayerChar);
				else if (line[j] == END_CHAR)
					handleSpecialChar(END_CHAR, endLocation, i, j, seenEndChar, line, ErrorType::MoreThanOneEndChar);
				else if (line[j] != SPACE_CHAR && line[j] != WALL_CHAR) // other chars are invalid
					handleInvalidChar(line[j], i, j);
				row.push_back(line[j]);
			}
			for (size_t j = line.length(); j < cols; j++)
				row.push_back(SPACE_CHAR);
		}
		else
			for (size_t j = 0; j < cols; j++)
				row.push_back(SPACE_CHAR);
		board.push_back(row);
	}
	if (!seenPlayerChar) pushError(ErrorType::MissingPlayerChar, string());
	if (!seenEndChar) pushError(ErrorType::MissingEndChar, string());
	return board;
}

void FileHandler::handleSpecialChar(const char c, Coordinate & location, const size_t i, const size_t j, bool & seenChar, string & line, const ErrorType e) {
	if (!seenChar) {
		updateCoordinate(location, i, j);
		seenChar = true;
		if (c == PLAYER_CHAR) line[j] = SPACE_CHAR; // not necessary as '@' character
	}
	else { // only one player char allowed!
		pushError(e, string());
	}
}

void FileHandler::handleInvalidChar(const char c, const size_t i, const size_t j) {
	string str = "000";
	str[0] = c;
	str[1] = (char)i;
	str[2] = (char)j;
	pushError(ErrorType::WrongChar, str);
}

void FileHandler::pushActionToOutputFile(char c) {
	m_fout << c << endl;
}


