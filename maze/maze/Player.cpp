#include "Player.h"

Player::Player() { 
	m_numOfSteps = 1; // first step in our implementation will be BOOKMARK, so to simplify the code we begin counting steps from 1
	m_bookmark = make_pair(0, 0); // first bookmark in starting point
	m_location = make_pair(INT_MAX, INT_MAX);
	updatePath();
	updateMapping(m_location, SPACE_CHAR);
	m_action = Action::NO_ACTION;
}

void Player::updateLocation(bool undo) {
	m_action = undo ? !m_action : m_action;
	switch (m_action) {
	case Action::UP:
		m_location.first--;
		break;
	case Action::DOWN:
		m_location.first++;
		break;
	case Action::LEFT:
		m_location.second--;
		break;
	case Action::RIGHT:
		m_location.second++;
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

void Player::updatePath(const bool undo) {
	if (!undo) {
		Coordinate copy = make_pair(m_location.first, m_location.second);
		m_path.push_back(copy);
	}
	else {
		m_path.pop_back();
	}
}

void Player::updateMapping(const Coordinate loc, char c) {
	m_mazeMapping[loc] = c;
}

Action Player::move() {
	m_numOfSteps++;
	generateAction(findExclusions());
	updateLocation();
	updateMapping(m_location, SPACE_CHAR);
	updatePath();
	return m_action;
}

// we update here the mapping with the wall we saw, the player location and undo the path
void Player::hitWall()
{
	updateMapping(m_location, WALL_CHAR);
	updateLocation(true); // undo
}

void Player::hitBookmark()
{
}

void Player::generateAction(vector<Action> exclusions) {
	// generates an action until it finds an action not in exclusions
	do {
		m_action = Action(rand() % 4);
	} while (inVector(exclusions));
}

bool Player::inVector(vector<Action> exclusions) {
	for (vector<Action>::iterator it = exclusions.begin(); it != exclusions.end(); ++it) {
		if (*it == m_action)
			return true;
	}
	return false;
}

vector<Action> Player::findExclusions()
{
	vector<Action> exclusions;
	char up = m_mazeMapping[m_location + Action::UP];
	char down = m_mazeMapping[m_location + Action::DOWN];
	char left = m_mazeMapping[m_location + Action::LEFT];
	char right = m_mazeMapping[m_location + Action::RIGHT];
	
	vector <char> directions = { up,down,right,left };
	vector <int> visit = { 0,0,0,0 };
	int space = 0;
	int wall = 0;

	for (int i = 0; i < 4; ++i) {
		if (directions[i] == WALL_CHAR) { 
			exclusions.push_back(static_cast<Action>(i));

			// In this location we hit a wall
			visit[i] = 2;
			wall++;
		}
		else if (directions[i] == SPACE_CHAR) {

			// we visited in this location
			visit[i] = 1;
			space++;
		}
	}

	// If we visited in all the directions
	if ((wall + space) == 4 || space == 4) return exclusions;

	// If we doesnt visited in all the directions we will push the locations that we visit
	else {
		for (int j = 0; j < 4; ++j) { if (visit[j] == 1) exclusions.push_back(static_cast<Action>(j)); };
	}

	return exclusions;
}

