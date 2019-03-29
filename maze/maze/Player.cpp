#include "Player.h"

Player::Player() : m_numOfSteps(0) {
	m_bookmark.set(0, 0);
	m_currentLocation.set(0, 0);
	updatePath();
	updateMapping(m_currentLocation, SPACE_CHAR);
}

void Player::updatePath() {
	Coord copy = m_currentLocation;
	m_path.push_back(copy);
}

void Player::updateMapping(Coord loc, char c) {
	m_mazeMapping[loc] = c;
}

Action Player::move() {

}