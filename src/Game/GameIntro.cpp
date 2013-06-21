#include "GameIntro.h"
#include "../Pipeline/Pipeline.h"

GameIntro::GameIntro()
{
	
}

void GameIntro::setWindow(int width, int height )
{
}

bool GameIntro::init()
{
}
Game * GameIntro::nextGameState()
{
	return this;
}


void GameIntro::render()
{
	}

void GameIntro::Update()
{
}

GameIntro::~GameIntro()
{
	delete m_pEffect;
	delete m_pGameCamera;
	delete m_pTexture;
	delete m_pMesh;
}