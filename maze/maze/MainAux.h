#ifndef MAINAUX_H
#define MAINAUX_H

#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
//#include "Maze.h"

#define MAXSTEPS "MaxSteps"
#define ROWS "Rows"
#define COLS "Cols"
#define SPACE_CHAR ' '
#define PLAYER_CHAR '@'
#define END_CHAR '$'
#define WALL_CHAR '#'

using namespace std;
using MazeRow = std::vector<char>;
using MazeBoard = std::vector<MazeRow>;
using Coordinate = size_t[2];

enum class ErrorType {
	MissingInput, MissingOutput, BadInputAddress, BadOutputAddress,
	MaxStepsError, RowsError, ColsError,
	MissingPlayerChar, MissingEndChar,
	MoreThanOnePlayerChar, MoreThanOneEndChar,
	WrongChar
};

typedef pair<ErrorType, std::string> Pair;
typedef void(*Func) (const string & str);
typedef std::vector<Pair> ErrorList;
typedef std::map<ErrorType, Func> FuncMap;

void printWinMessage(const int numOfSteps);
void printLostMessage(const int numOfSteps);
void handleMissingInputError(const string & str);
void handleMissingOutputError(const string & str);
void handleBadInputAddressError(const string & str);
void handleBadOutputAddressError(const string & str);
void handleMaxStepsError(const string & str);
void handleRowsError(const string & str);
void handleColsError(const string & str);
void handleMissingPlayerCharError(const string & str);
void handleMissingEndCharError(const string & str);
void handleMoreThanOnePlayerCharError(const string & str);
void handleMoreThanOneEndCharError(const string & str);
void handleWrongCharError(const string & str);

struct Errors {
	FuncMap fmap = {
		{ErrorType::MissingInput, &handleMissingInputError},
		{ErrorType::MissingOutput, &handleMissingOutputError},
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

void checkErrors(Errors & e);

#endif