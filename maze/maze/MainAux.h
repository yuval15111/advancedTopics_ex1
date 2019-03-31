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

using namespace std;
using MazeRow = vector<char>;
using MazeBoard = vector<MazeRow>;

enum class Action {
	UP, DOWN, RIGHT, LEFT, BOOKMARK, NO_ACTION
};

Action operator!(const Action& a);

enum class ErrorType {
	MissingInput, MissingOutput, BadInputAddress, BadOutputAddress,
	MaxStepsError, RowsError, ColsError,
	MissingPlayerChar, MissingEndChar,
	MoreThanOnePlayerChar, MoreThanOneEndChar,
	WrongChar
};

typedef pair<ErrorType, string> Pair;
typedef void(*Func) (const string * str);
typedef vector<Pair> ErrorList;
typedef map<ErrorType, Func> FuncMap;
typedef pair<size_t, size_t> Coordinate;

void printWinMessage(const size_t numOfSteps);
void printLostMessage(const size_t numOfSteps);

void handleMissingInputError(const string * str);
void handleMissingOutputError(const string * str);
void handleBadInputAddressError(const string * str);
void handleBadOutputAddressError(const string * str);
void handleMaxStepsError(const string * str);
void handleRowsError(const string * str);
void handleColsError(const string * str);
void handleMissingPlayerCharError(const string * str);
void handleMissingEndCharError(const string * str);
void handleMoreThanOnePlayerCharError(const string * str);
void handleMoreThanOneEndCharError(const string * str);
void handleWrongCharError(const string * str);

struct Errors {
	FuncMap fmap = {
		{ErrorType::BadInputAddress, &handleBadInputAddressError},
		{ErrorType::BadOutputAddress, &handleBadOutputAddressError},
		{ErrorType::MaxStepsError, &handleMaxStepsError},
		{ErrorType::RowsError, &handleRowsError},
		{ErrorType::ColsError, &handleColsError},
		{ErrorType::MissingPlayerChar, &handleMissingPlayerCharError},
		{ErrorType::MissingEndChar, &handleMissingEndCharError},
		{ErrorType::MoreThanOnePlayerChar, &handleMoreThanOnePlayerCharError},
		{ErrorType::MoreThanOneEndChar, &handleMoreThanOneEndCharError},
		{ErrorType::WrongChar, &handleWrongCharError}
	};
	ErrorList list;
};

vector<string> split(string str, char delimiter);
void updateCoordinate(Coordinate & c, const size_t i, const size_t j);

#endif