#ifndef FILEHANDLER_H
#define FILEHANDLER_H

//#include "MainAux.h"
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Maze.h"

using namespace std;

enum ErrorType {
	NoErrors = 0, MaxStepsError = 1, RowsError = 2, ColsError = 4, MissingPlayerChar = 8,
	MissingEndChar = 16, MoreThanOnePlayerChar = 32, MoreThanOneEndChar = 64, WrongChar = 128,
	MissingInput = 256, BadInputAddress = 512, MissingOutput = 1024, BadOutputAddress = 2048
};

inline ErrorType operator|(ErrorType a, ErrorType b) {
	return static_cast<ErrorType>(static_cast<int>(a) | static_cast<int>(b));
}

inline bool operator&(ErrorType a, ErrorType b) {
	return ((static_cast<int>(a) & static_cast<int>(b)) == 0);
}


class FileHandler {
private:
	ifstream m_fin;
	ofstream m_fout;
	ErrorType m_errors;

public:
	FileHandler(int argc, char* argv[]);
	Maze * parseInput();
	~FileHandler();
	string getName();
	size_t getIntValue(const char * input, const ErrorType error);
	vector<string> split(string str, char delimiter);
	MazeBoard getBoard(size_t rows, size_t cols, size_t playerLocation[2]);
	inline ErrorType getErrors() const { return m_errors; }
	void checkIOErrors(const string & input, const string & output);
	void checkParsingErrors();
};

#endif