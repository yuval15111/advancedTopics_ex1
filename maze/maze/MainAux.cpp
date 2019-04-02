#include "MainAux.h"

Action operator!(const Action& a) {
	switch (a) {
	case Action::UP:
		return Action::DOWN;
	case Action::DOWN:
		return Action::UP;
	case Action::LEFT:
		return Action::RIGHT;
	case Action::RIGHT:
		return Action::LEFT;
	default:
		return a;
	}
}

Coordinate operator+(Coordinate a, const Action & b) {
	switch (b) {
	case Action::UP:
		a.first--;
		break;
	case Action::DOWN:
		a.first++;
		break;
	case Action::LEFT:
		a.second--;
		break;
	case Action::RIGHT:
		a.second++;
		break;
	default:
		break;
	}
	return a;
}

void printWinMessage(const size_t numOfSteps) {
	cout << "Succeeded in " << numOfSteps << " steps" << endl; 
}

void printLostMessage(const size_t numOfSteps) {
	cout << "Failed to solve maze in " << numOfSteps << " steps" << endl;
}

void printMissingInputError(const string & str) {
	(void)str;
	cout << "Missing maze file argument in command line" << endl;
}

void printMissingOutputError(const string & str) {
	(void)str;
	cout << "Missing output file argument in command line" << endl;
}

void printBadInputAddressError(const string & str)
{
	cout << "Command line argument for maze: " << str << " doesn't lead to a maze file or leads to a file that cannot be opened" << endl;
}

void printBadOutputAddressError(const string & str)
{
	cout << "Command line argument for output file: " << str << " points to a bad path or to a file that already exists" << endl;
}

void printMaxStepsError(const string & str)
{
	cout << "expected in line 2 - MaxSteps = <num>" << endl;
	cout << "got: " << str << endl;
}

void printRowsError(const string & str)
{
	cout << "expected in line 3 - Rows = <num>" << endl;
	cout << "got: " << str << endl;
}

void printColsError(const string & str)
{
	cout << "expected in line 4 - Cols = <num>" << endl;
	cout << "got: " << str << endl;
}

void printMissingPlayerCharError(const string & str)
{
	(void)str;
	cout << "Missing @ in maze" << endl;
}

void printMissingEndCharError(const string & str)
{
	(void)str;
	cout << "Missing $ in maze" << endl;
}

void printMoreThanOnePlayerCharError(const string & str)
{
	(void)str;
	cout << "More than one @ in maze" << endl;
}

void printMoreThanOneEndCharError(const string & str)
{
	(void)str;
	cout << "More than one $ in maze" << endl;
}

void printWrongCharError(const string & str)
{
	if (str[0] == 9)
		cout << "Wrong character in maze: TAB in row " << (int)str[1] << ", col " << (int)str[2] << endl;
	else
		cout << "Wrong character in maze: " << str[0] << " in row " << (int)str[1] << ", col " << (int)str[2] << endl;
}

char getActionChar(const Action& a) {
	switch (a) {
	case Action::UP:
		return 'U';
	case Action::DOWN:
		return 'D';
	case Action::LEFT:
		return 'L';
	case Action::RIGHT:
		return 'R';
	default:
		return 'B';
	}
}

void updateCoordinate(Coordinate & c, const size_t i, const size_t j) {
	c.first = i;
	c.second = j;
}