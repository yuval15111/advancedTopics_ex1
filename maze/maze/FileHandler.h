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

enum ParsingErrorType {
	NoError = 0, MaxStepsError = 1, RowsError = 2, ColsError = 4, MissingPlayerChar = 8,
	MissingEndChar = 16, MoreThanOnePlayerChar = 32, MoreThanOneEndChar = 64, WrongChar = 128
};

inline ParsingErrorType operator|(ParsingErrorType a, ParsingErrorType b) {
	return static_cast<ParsingErrorType>(static_cast<int>(a) | static_cast<int>(b));
}


class FileHandler {
private:
	ifstream& m_fin;
	ofstream& m_fout;

public:
	FileHandler(ifstream& fin, ofstream& fout) : m_fin(fin), m_fout(fout) {};
	Maze * parseInput(ParsingErrorType & errors);
	~FileHandler();

	string getName(ifstream & fin);

	size_t getIntValue(ifstream & fin, const char * input);

	vector<string> split(string str, char delimiter);

	MazeBoard getBoard(ifstream & fin, size_t rows, size_t cols, size_t playerLocation[2], ParsingErrorType & error);
};

#endif