#include "GameRunningState.h"
#include "GameApp.h"
#include "MainMenuState.h"
#include <iostream>

GameRunningState::GameRunningState(GameApp* app) : GameState(app)
{
	esLogMessage(__FUNCTION__);
	int cc = 0;

	esLogMessage("Init... %d", cc++);
	m_map = new TmxMap();

	esLogMessage("Init... %d", cc++);
	componentFactory = new MyComponentFactory();

	esLogMessage("Init... %d", cc++);
	componentFactory->setCurrentMap(m_map);

	esLogMessage("Init... %d", cc++);
	m_map->loadMapFile("assets/level.tmx", componentFactory);

	m_map->findGameObjectByName("Ball")->getComponent<BallController>()->setPlayerPad(m_map->findGameObjectByName("Player")->getComponent<PlayerPaddleController>());

	esLogMessage("Init... %d", cc++);
	// Move camera to middle of map.
	m_map->getCamera()->setPosition(vec2(m_map->getWidth() / 2.0f - 1.0f, m_map->getHeight() / 2.0f - 0.5f));

	esLogMessage("Init... Done");
}

GameRunningState::~GameRunningState()
{
	//std::cout << "GameRunnig state destructor" << std::endl;
	delete componentFactory;
}

bool GameRunningState::update(ESContext* ctx, float deltaTime)
{
	m_map->update(deltaTime);

	slm::vec2 collisionNormal;

	// Static collisions
	for (int i = 0; i < sizeof(m_map->getLayer("StaticColliders")); i++)
	{
		if (m_map->findGameObjectByName("Ball")->collidesTo(m_map->getLayer("StaticColliders")->getGameObjects()[i], &collisionNormal))
		{
			m_map->findGameObjectByName("Ball")->getComponent<BallController>()->HandleCollision(m_map->getLayer("StaticColliders")->getGameObjects()[i], collisionNormal);
		}
	}

	// Object collisions
	for (int i = 0; i < sizeof(m_map->getLayer("Bricks")); i++)
	{
		if (m_map->findGameObjectByName("Ball")->collidesTo(m_map->getLayer("Bricks")->getGameObjects()[i], &collisionNormal))
		{
			m_map->findGameObjectByName("Ball")->getComponent<BallController>()->HandleCollision(m_map->getLayer("Bricks")->getGameObjects()[i], collisionNormal);
			m_map->getLayer("Bricks")->getGameObjects()[i]->setPosition(-1000.0f, 0.0f);
		}
	}

	// Ball colliding player paddle
	if (m_map->findGameObjectByName("Ball")->collidesTo(m_map->findGameObjectByName("Player"), &collisionNormal))
	{
		m_map->findGameObjectByName("Ball")->getComponent<BallController>()->HandleCollision(m_map->findGameObjectByName("Player"), collisionNormal);
	}
		
	if (isKeyReleased(KEY_ESCAPE))
	{
		getApp()->setState(new MainMenuState(getApp()));
		return true;
	}
	return true;
}

void GameRunningState::draw(ESContext* ctx)
{
	// Set screen size to camera.
	m_map->getCamera()->setScreenSize(ctx->width, ctx->height, 720, 1280.0f / 720.0f);

	// Render map and all of its layers containing GameObjects to screen.
	m_map->render();
}