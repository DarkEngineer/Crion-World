#include "Player.h"

Player::Player()
{
	player_camera = new Camera();
	state = STANDING;
	statistics.experience = 0;
	statistics.health = 100;
	statistics.level = 1;
	statistics.speed = 350;
	statistics.weight = 60;

}

Camera * Player::getCamera()
{
	return player_camera;
}

Player::~Player()
{
	delete player_camera;
}