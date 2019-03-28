#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Maze.h"

class FileHandler {
private:
	ifstream m_fin;
	ofstream m_fout;
	Errors m_errors;

public:
	FileHandler(int argc, char* argv[]);
	Maze * parseInput();
	//~FileHandler();
	string getName();
	size_t getIntValue(const char * input, const ErrorType error);
	vector<string> split(string str, char delimiter);
	MazeBoard getBoard(size_t rows, size_t cols, Coordinate playerLocation);
	inline void pushError(ErrorType type, const string & str) {	m_errors.list.push_back(Pair(type, str)); }
};

#endif