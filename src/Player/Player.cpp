#include "Player.h"

Player::Player()
{
	body = new Object();
	player_camera = new Camera();
	state = STANDING;
	statistics.experience = 0;
	statistics.health = 100;
	statistics.level = 1;
	statistics.speed = 350;
	statistics.weight = 60;

}

void Player::create(const char* sourceMesh, const char * fileStructure)
{
	body->create(sourceMesh, fileStructure);
}

void Player::create(glm::vec3 position, const char * sourceMesh, const char * fileStructure)
{
	body->create(position, sourceMesh, fileStructure);
}

Player::~Player()
{
	delete body;
	delete player_camera;
	delete & state;
	delete & statistics;
}