#include "FileHandler.h"

FileHandler::~FileHandler()
{
	delete(&m_fin);
	delete(&m_fout);
}

FileHandler::FileHandler(int argc, char * argv[]) : m_fin(argv[1]), m_fout(argv[2]) {
	m_errors = ErrorType::NoErrors;
	if (argc >= 3) {
		if (!m_fin.good()) {
			m_errors = m_errors | ErrorType::BadInputAddress;
		}
		if (!m_fout.good()) {
			m_errors = m_errors | ErrorType::BadOutputAddress;
		}
		checkIOErrors(argv[1], argv[2]);
	}
	else {
		if (argc == 1) {
			m_errors = m_errors | ErrorType::MissingInput;
		}
		else { // argc == 2
			m_errors = m_errors | ErrorType::MissingOutput;
		}
		checkIOErrors(nullptr, nullptr);
	}
}

Maze * FileHandler::parseInput() {
	MazeBoard board;
	string name;
	size_t maxSteps;
	size_t rowsNum, colsNum;
	size_t playerLocation[2] = { 0, 0 };

	name = getName();

	maxSteps = getIntValue("MaxSteps", ErrorType::MaxStepsError);
	rowsNum = getIntValue("Rows", ErrorType::RowsError);
	colsNum = getIntValue("Cols", ErrorType::ColsError);

	board = getBoard(rowsNum, colsNum, playerLocation);
	Maze* maze = new Maze(name, maxSteps, rowsNum, colsNum, board, playerLocation);
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
		vector<string> splitted = split(line, ' ');
		if (splitted.size() != 3 || splitted[0].compare(input) != 0 || splitted[1].compare("=") != 0) {
			return -1;
		}
		size_t result = (size_t)atoi(splitted[2].c_str()); // TODO: MAYBE THERE IS A BETTER SOLUTION
		if (result == 0) {
			m_errors = m_errors | error;
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
				row.push_back(line[j]);
				if (line[j] == '@') {
					if (!seenEndChar) {
						playerLocation[0] = i;
						playerLocation[1] = j;
						seenEndChar = true;
					}
					else { // only one player char allowed
						m_errors = m_errors | ErrorType::MoreThanOnePlayerChar;
					}
				}
				if (line[j] == '$') {
					if (!seenPlayerChar) {
						seenPlayerChar = true;
					}
					else { // only one end char allowed
						m_errors = m_errors | ErrorType::MoreThanOneEndChar;
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
		m_errors = m_errors | ErrorType::MissingPlayerChar;
	}
	if (!seenEndChar) {
		m_errors = m_errors | ErrorType::MissingEndChar;
	}
	return board;
}

void FileHandler::checkIOErrors(const string & input, const string & output) {
	if (m_errors & ErrorType::MissingInput) {
		cout << "Missing maze file argument in command line" << endl;
		
	}
	if (m_errors & ErrorType::MissingOutput) {
		cout << "Missing output file argument in command line" << endl;
	}
	if (m_errors & ErrorType::BadInputAddress) {
		cout << "Command line argument for maze: " << input << " doesn't lead to a maze file or leads to a file that cannot be opened" << endl;
	}
	if (m_errors & ErrorType::BadOutputAddress) {
		cout << "Command line argument for output file: " << output << " points to a bad path or to a file that already exists" << endl;
	}
}

void FileHandler::checkParsingErrors() {
	return;
}
