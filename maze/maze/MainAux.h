#ifndef MAINAUX_H
#define MAINAUX_H

#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Maze.h"

enum IOErrorType {
	NoError = 0, MissingInput, BadInputAddress, MissingOutput, BadOutputAddress
};

inline IOErrorType operator|(IOErrorType a, IOErrorType b) {
	return static_cast<IOErrorType>(static_cast<int>(a) | static_cast<int>(b));
}

enum ParsingErrorType {
	NoError = 0, MaxStepsError = 1, RowsError = 2, ColsError = 4, MissingPlayerChar = 8,
	MissingEndChar = 16, MoreThanOnePlayerChar = 32, MoreThanOneEndChar = 64, WrongChar = 128
};

inline ParsingErrorType operator|(ParsingErrorType a, ParsingErrorType b) {
	return static_cast<ParsingErrorType>(static_cast<int>(a) | static_cast<int>(b));
}

class MainAux {
	inline void printWinMessage() { cout << "Succeeded in " << numOfSteps << " steps" << endl; };
	inline void printLostMessage() { cout << "Failed to solve maze in " << numOfSteps << " steps" << endl; };
	
};

#endif