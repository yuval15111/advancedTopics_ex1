#include "Player.h"

Player::Player() : m_numOfSteps(0) {
	m_bookmark.set(INT_MAX, INT_MAX);
	m_currentLocation.set(0, 0);
	updatePath();
	updateMapping(m_currentLocation, SPACE_CHAR);
}

void Player::updateLocation(Action a, bool undo) {
	a = undo ? !a : a;
	switch (a) {
	case Action::UP:
		m_currentLocation.row--;
		break;
	case Action::DOWN:
		m_currentLocation.row++;
		break;
	case Action::LEFT:
		m_currentLocation.col--;
		break;
	case Action::RIGHT:
		m_currentLocation.col++;
		break;
	}
}
// TODO: previous implementation
/*{
	a = undo ? !a : a;
	switch (a) {
	case Action::UP:
		m_currentLocation.row += m_rowsNum - 1;
		m_currentLocation.row %= m_rowsNum;
		break;
	case Action::DOWN:
		m_currentLocation.row++;
		m_currentLocation.row %= m_rowsNum;
		break;
	case Action::LEFT:
		m_currentLocation.col += m_colsNum - 1;
		m_currentLocation.col %= m_colsNum;
		break;
	case Action::RIGHT:
		m_currentLocation.col++;
		m_currentLocation.col %= m_colsNum;
		break;
	}
}*/

void Player::updatePath(bool undo) {
	if (undo == false) {
		Coord copy = m_currentLocation;
		m_path.push_back(copy);
	}
	else {
		m_path.pop_back();
	}
}

void Player::updateMapping(Coord loc, char c) {
	Coordinate l = make_pair(loc.row, loc.col);
	m_mazeMapping[l] = c;
}

Action Player::move() {
	Action action;
	vector<Action> exclusions;
	m_numOfSteps++;
	if (m_path.size() == 1) { // didn't move yet
		if (m_bookmark.row == INT_MAX) { // first step - bookmark
			m_bookmark.set(0, 0);
			return Action::BOOKMARK;
		}
	}
	else { // size > 0, after first two steps
		// handle more exclusions
		// understand what is the best path to come back after all four ways were visited
		findExclusions(exclusions);
	}
	action = shuffle(exclusions);
	updateLocation(action);
	updateMapping(m_currentLocation, SPACE_CHAR);
	updatePath();
	return action;
}

// we update here the mapping with the wall we saw, the player location and undo the path
void Player::hitWall(Action a)
{
	updateMapping(m_currentLocation, WALL_CHAR);
	updateLocation(a, true); // undo
}

void Player::hitBookmark()
{
}

Action Player::shuffle(vector<Action> exclusions) {
	Action action;
	do {
		action = Action(rand() % 4);
	} while (inVector(action, exclusions));
	return action;
}

bool Player::inVector(Action action, vector<Action> exclusions) {
	for (vector<Action>::iterator it = exclusions.begin(); it != exclusions.end(); ++it) {
		if (*it == action)
			return true;
	}
	return false;
}

void Player::findExclusions(vector<Action>& exclusions)
{
	// exclusions.push_back(getLastRelativePoision());
}

// assumption: m_path.size() > 0
Action Player::getLastRelativePoision()
{
	Coord lastCoord = m_path.back();
	if (lastCoord.row < m_currentLocation.row) {
		return Action::LEFT;
	}
	else if (lastCoord.row > m_currentLocation.row) {
		return Action::RIGHT;
	}
	else if (lastCoord.col < m_currentLocation.col) {
		return Action::DOWN;
	}
	else { // (lastCoord.col > m_currentLocation.col)
		return Action::UP;
	}
}
