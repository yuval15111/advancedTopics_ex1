#ifndef MAINAUX_H
#define MAINAUX_H

#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <fstream>

#define MAX_INT 2147483647

#define MAXSTEPS "MaxSteps"
#define ROWS "Rows"
#define COLS "Cols"
#define SPACE_CHAR ' '
#define PLAYER_CHAR '@'
#define END_CHAR '$'
#define WALL_CHAR '#'

#define LEGALSTEP 0
#define HITWALL 1
#define HITBOOKMARK 2

enum class ErrorType {
	MissingInput, MissingOutput, BadInputAddress, BadOutputAddress,
	MaxStepsError, RowsError, ColsError,
	MissingPlayerChar, MissingEndChar,
	MoreThanOnePlayerChar, MoreThanOneEndChar,
	WrongChar
};

enum class Action {
	UP, DOWN, RIGHT, LEFT, BOOKMARK
};

using namespace std;
using MazeRow = vector<char>;
using MazeBoard = vector<MazeRow>;
using Coordinate = pair<size_t, size_t>;
using Pair = pair<ErrorType, string>;
using ErrorList = vector<Pair>;
typedef void(*Func) (const string * str);

Action operator!(const Action& a);
Coordinate operator+(Coordinate a, const Action & b);

void printWinMessage(const size_t numOfSteps);
void printLostMessage(const size_t numOfSteps);
void printMissingInputError(const string * str);
void printMissingOutputError(const string * str);
void printBadInputAddressError(const string * str);
void printBadOutputAddressError(const string * str);
void printMaxStepsError(const string * str);
void printRowsError(const string * str);
void printColsError(const string * str);
void printMissingPlayerCharError(const string * str);
void printMissingEndCharError(const string * str);
void printMoreThanOnePlayerCharError(const string * str);
void printMoreThanOneEndCharError(const string * str);
void printWrongCharError(const string * str);

struct Errors {
	map<ErrorType, Func> fmap = {
		{ErrorType::MissingInput, &printMissingInputError},
		{ErrorType::MissingOutput, &printMissingOutputError},
		{ErrorType::BadInputAddress, &printBadInputAddressError},
		{ErrorType::BadOutputAddress, &printBadOutputAddressError},
		{ErrorType::MaxStepsError, &printMaxStepsError},
		{ErrorType::RowsError, &printRowsError},
		{ErrorType::ColsError, &printColsError},
		{ErrorType::MissingPlayerChar, &printMissingPlayerCharError},
		{ErrorType::MissingEndChar, &printMissingEndCharError},
		{ErrorType::MoreThanOnePlayerChar, &printMoreThanOnePlayerCharError},
		{ErrorType::MoreThanOneEndChar, &printMoreThanOneEndCharError},
		{ErrorType::WrongChar, &printWrongCharError}
	};
	vector<pair<ErrorType, string>> list;
};

bool doesExist(char * path);
const char * setAbsolute(char * args[], int arg);
vector<string> split(string str, char delimiter);
void updateCoordinate(Coordinate & c, const size_t i, const size_t j);

#endif