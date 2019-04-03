#include "Player.h"
#include <time.h>


Player::Player() { 
	m_bookmark = make_pair(0, 0); // first bookmark in starting point
	m_location = make_pair(0, 0);
	updateMapping(m_location, SPACE_CHAR);
	m_action = Action::BOOKMARK;
}

void Player::updateLocation(bool undo) {
	m_action = undo ? !m_action : m_action;
	switch (m_action) {
	case Action::UP:
		m_location.first++;
		break;
	case Action::DOWN:
		m_location.first--;
		break;
	case Action::LEFT:
		m_location.second--;
		break;
	case Action::RIGHT:
		m_location.second++;
		break;
	default:
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


void Player::updateMapping(const Coordinate loc, char c) {
	m_mazeMapping[loc] = c;
}

Action Player::move() {
	generateAction(findExclusions());
	m_actionVector.push_back(m_action);
	updateLocation();
	updateMapping(m_location, SPACE_CHAR);
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
	if (m_bookmark == m_location) return;
	else {
		if (m_bookmark.first == m_location.first) { // Defines col dimention
			m_colsNum = ABS(m_bookmark.second, m_location.second);
			arrangeMapping(false);
		} 
		else if (m_bookmark.second == m_location.second) {
			m_rowsNum = ABS(m_bookmark.first, m_location.first);
			arrangeMapping(true);
		}
	}
}

void Player::generateAction(vector<Action> exclusions) {
	if (m_actionVector.size() % STEPS_NUM_TO_BOOKMARK == 0) {
		m_action = Action::BOOKMARK;
		return;
	}

	srand((unsigned int)time(0));
	// generates an action until it finds an action not in exclusions
	do {
		m_action = Action(rand() % 4);
	} while (inVector(exclusions));
	
	if (numOfSteps() != 0 && m_action == m_actionVector[numOfSteps() - 1]) m_currActionCounter++;
	else m_currActionCounter = 1;
}

bool Player::inVector(vector<Action> exclusions) {
	for (vector<Action>::iterator it = exclusions.begin(); it != exclusions.end(); ++it) {
		if (*it == m_action)
			return true;
	}
	return false;
}

/*	return: vector of actions which none of them won't be chosen as the next action */
vector<Action> Player::findExclusions()
{
	vector<Action> exclusions;

	char up = getCharByDirection(Action::UP);
	char down = getCharByDirection(Action::DOWN);
	char left = getCharByDirection(Action::LEFT);
	char right = getCharByDirection(Action::RIGHT);
	
	vector <char> directions = { up,down,right,left };
	vector <int> visit = { 0,0,0,0 };
	int space = 0;
	int wall = 0;

	// We won't allow more than MAX_SAME_ACTION_NUM steps of the same action.
	if (m_currActionCounter == MAX_SAME_ACTION_NUM) {
		exclusions.push_back(m_action);
	}

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


void Player::arrangeMapping(bool rows)
{
	map <Coordinate, char> newMapping;
	if (rows) {
		for (map<Coordinate, char>::iterator it = m_mazeMapping.begin(); it != m_mazeMapping.end(); ++it) {
			char& c = m_mazeMapping[(*it).first];
			Coordinate newLocation = (*it).first;
			if (newLocation.first < 0) newLocation.first = m_rowsNum + newLocation.first % m_rowsNum;
			else newLocation.first %= m_rowsNum;
			newMapping[newLocation] = c;
		}
	}
	else {
		for (map<Coordinate, char>::iterator it = m_mazeMapping.begin(); it != m_mazeMapping.end(); ++it) {
			char& c = m_mazeMapping[(*it).first];
			Coordinate newLocation = (*it).first;
			if (newLocation.second < 0) newLocation.second = m_colsNum + newLocation.second % m_colsNum;
			else newLocation.second %= m_colsNum;
			newMapping[newLocation] = c;
		}
	}
	m_mazeMapping.clear();
	m_mazeMapping = newMapping;
}

char Player::getCharByDirection(Action a)
{
	Coordinate key = m_location + a;
	if (m_mazeMapping.find(key) != m_mazeMapping.end())
		return m_mazeMapping[key];
	return '0';
}

