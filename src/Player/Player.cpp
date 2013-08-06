#include "Player.h"

Player::Player()
	:
	state(STANDING),
	player_camera (new Camera()),
	bCreate(false)
{
	statistics.experience = 0;
	statistics.health = 100;
	statistics.level = 1;
	statistics.speed = 350;
	statistics.weight = 60;
}

bool Player::ifCreated(bool state)
{
	bCreate = state;
	return state;
}


bool Player::getCreateStatus()
{
	return bCreate;
}

Camera * Player::getCamera()
{
	return player_camera;
}

Player::~Player()
{
	delete player_camera;
}