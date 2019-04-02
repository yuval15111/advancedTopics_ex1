#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Manager.h"
#include <regex>

class FileHandler {
private:
	ifstream				m_fin;
	ofstream				m_fout;
	Errors					m_errors;
	bool					checkErrors();
	inline void				pushError(ErrorType type, const string & str) { m_errors.list.push_back(Pair(type, str)); }
	string					getName(string & line);
	size_t					getIntValue(const string & input, const ErrorType error, string & line);
	MazeBoard				getBoard(const size_t rows, const size_t cols, Coordinate & playerLocation, Coordinate & endLocation, string & line);
	void					handleSpecialChar(const char c, Coordinate & location, const size_t i, const size_t j, bool & seenChar, string & line, const ErrorType e);
	void					handleInvalidChar(const char c, const size_t i, const size_t j);

public:
	FileHandler(int argc, char* argv[]);
	~FileHandler();
	Manager *				parseInput();
	inline bool				noErrors() { return m_errors.list.size() == 0; }
	void					pushActionToOutputFile(char c);
};

#endif