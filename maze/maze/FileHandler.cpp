#include "FileHandler.h"

FileHandler::~FileHandler()
{
	if (m_manager != nullptr) delete m_manager;
	m_fin.close();
	m_fout.close();
}

/*	In the constructor we initialize ifstream m_fin and ofstream m_fout.
	We also check here validity of the program arguments. */
FileHandler::FileHandler(int argc, char * argv[]) {

	// Checking if the parsing allow for local issues
	bool parseAllow = true;
	switch (argc) {
	case 1:
		pushError(ErrorType::MissingInput, string());								// No arguments at all - shouldn't parse
		break;
	case 2:
		m_errors.no_IO_Errors = false;
		pushError(ErrorType::MissingOutput, string());								// No output path argument: may parse maze anyway
	default:
		if (!fileExists(argv[1])) {

			// For a new printing order - first input and then output
			if (m_errors.list.size() > 0 && m_errors.list[0].first == ErrorType::MissingOutput) {
				m_errors.list.pop_back();
				pushError(ErrorType::BadInputAddress, argv[1]);
				pushError(ErrorType::MissingOutput, string());
				
			}

			// There are no errors for output
			else {
				pushError(ErrorType::BadInputAddress, argv[1]);							// Bad maze path or file does not exist
			}

			// doesnt allow parsing - include locally-> parse allow 
			parseAllow = false;
			allowParsing(false);
		}
		if (argc >= 3) {
			if (fileExists(argv[2])) {
				pushError(ErrorType::BadOutputAddress, argv[2]);					// Bad output path argument: may parse maze anyway
					
				// If parsing is allow meaning the input file is ok
				if (parseAllow) {
					allowParsing(true);
					m_fin.open(argv[1]);
				}
				m_errors.no_IO_Errors = false;
			}
			else {
				m_fout.open(argv[2]);

				if (parseAllow) {
					m_fin.open(argv[1]);

					// If reaches here, valid output path argument
					allowParsing(true);
				}
			}	
		}

		// only if input is valid we will allow parsing
		else if (parseAllow) {
			allowParsing(true);
			m_fin.open(argv[1]);
		}
	}
	checkErrors(nullptr);
}

/*	This function checks if there are errors. If so: updates m_errors.noErrors field to false and prints the errors */
void FileHandler::checkErrors(void*(titleFunc)) {
	if (m_errors.list.size() == 0) return;
	if (titleFunc != nullptr) { // parsing errors
		FuncNoArgs f = (FuncNoArgs)titleFunc;
		f();

		m_errors.no_parsing_Errors = false;
	}
	for (ErrorList::iterator it = m_errors.list.begin(); it != m_errors.list.end(); ++it) {
		Func f = m_errors.fmap[it->first];
		string str = it->second;
		f(str);
	}
	m_errors.list.clear();
}

/* This function parses the input file and creates the manager object. */
void FileHandler::parseInput() {
	string line;

	string name = getName(line);															// Collects maze parameters
	int maxSteps = getIntValue(MAXSTEPS, ErrorType::MaxStepsError, line);
	int rowsNum = getIntValue(ROWS, ErrorType::RowsError, line);
	int colsNum = getIntValue(COLS, ErrorType::ColsError, line);
	checkErrors((void*)printHeaderErrorTitle);
	if (m_errors.no_parsing_Errors) {																// No errors, lines 2-4 are valid.
		Coordinate playerLocation, endLocation;
		MazeBoard board = getBoard(rowsNum, colsNum, playerLocation, endLocation, line);
		checkErrors((void*)printMazeErrorTitle);
		if (m_errors.no_parsing_Errors && m_errors.no_IO_Errors)									// No errors, maze file is valid - creates a Manager object
			m_manager = new Manager(name, maxSteps, rowsNum, colsNum,
									board, playerLocation, endLocation);
	}
}

string FileHandler::getName(string & line) {
	if (getline(m_fin, line)) {
		return line;
	}
	return nullptr;
}

int FileHandler::getIntValue(const string & input, const ErrorType error, string & line) {
	const regex reg("\\s*" + input + "\\s*=\\s*[1-9][0-9]*\\s*$((.|\\r)*)");
	
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

/*	params: rows, col - parsed from maze file; references to playerLocation and endLocation that will be filled in this function;
			refernce to line string which we fill with lines from the input and parse the file with.
	return: A maze board object (two-dimensional character vector) */
MazeBoard FileHandler::getBoard(const int rows, const int cols, Coordinate & playerLocation, Coordinate & endLocation, string & line) {
	MazeBoard board;
	bool seenPlayerChar = false, seenEndChar = false;
	for (int i = 0; i < rows; i++) {
		MazeRow row;
		if (getline(m_fin, line)) {

			// The case when there are external chars in the line
			if (cols < (int)line.length()) {
				for (int j = 0; j < cols; j++) {
					if (line[j] == PLAYER_CHAR)
						handleSpecialChar(PLAYER_CHAR, playerLocation, i, j, seenPlayerChar, line, ErrorType::MoreThanOnePlayerChar);
					else if (line[j] == END_CHAR)
						handleSpecialChar(END_CHAR, endLocation, i, j, seenEndChar, line, ErrorType::MoreThanOneEndChar);
					else if (line[j] != SPACE_CHAR && line[j] != WALL_CHAR) // other chars are invalid
						handleInvalidChar(line[j], i, j);
					row.push_back(line[j]);
				}

				/* Check the rest of the line - other chars are invalid
				for (int k = cols; k < (int)line.length(); k++) {
					if (line[k] != SPACE_CHAR && line[k] != WALL_CHAR)
						handleInvalidChar(line[k], i, k);
				}	*/
			}
			else {
				for (int j = 0; j < (int)line.length(); j++) {
					if (line[j] == PLAYER_CHAR)
						handleSpecialChar(PLAYER_CHAR, playerLocation, i, j, seenPlayerChar, line, ErrorType::MoreThanOnePlayerChar);
					else if (line[j] == END_CHAR)
						handleSpecialChar(END_CHAR, endLocation, i, j, seenEndChar, line, ErrorType::MoreThanOneEndChar);
					else if (line[j] != SPACE_CHAR && line[j] != WALL_CHAR) // other chars are invalid
						handleInvalidChar(line[j], i, j);
					row.push_back(line[j]);
				}
			}
			
			// Refill with SPACE_CHAR when the cols > line.length()
			for (int j = (int)line.length(); j < cols; j++)
				row.push_back(SPACE_CHAR);
		}

		// Refill one row if missing
		else
			for (int j = 0; j < cols; j++)
				row.push_back(SPACE_CHAR);
		board.push_back(row);
	}
	if (!seenPlayerChar) pushError(ErrorType::MissingPlayerChar, string());
	if (!seenEndChar) pushError(ErrorType::MissingEndChar, string());
	return board;
}

/*	A helper function for getBoard().
	Params: char c, location reference, (i, j) new coordinate indices, other helping parameters.
	The function updates the location coordinate by (i, j) values or pushes errors to the Errors vector if needed. */
void FileHandler::handleSpecialChar(const char c, Coordinate & location, const int i, const int j, bool & seenChar, string & line, const ErrorType e) {
	if (!seenChar) {
		updateCoordinate(location, i, j);
		seenChar = true;
		if (c == PLAYER_CHAR) line[j] = SPACE_CHAR; // not necessary as '@' character
	}
	else { // only one player char allowed!
		pushError(e, string());
	}
}

/*	A helper function for getBoard().
	Params: invalid char c, (i, j) error indices.
	The function pushes invalid char error to Error vector. */
void FileHandler::handleInvalidChar(const char c, const int i, const int j) {
	string str = "000";
	str[0] = c;
	str[1] = (char)i;
	str[2] = (char)j;
	pushError(ErrorType::WrongChar, str);
}

/*	params: vector of game actions.
	This function pushes the actions vector into the output file. */
void FileHandler::pushActionsToOutputFile(vector<char> actions) {
	for(const char & c : actions)
		m_fout << c << endl;
}
