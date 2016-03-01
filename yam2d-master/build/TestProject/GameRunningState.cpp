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

	m_map->findGameObjectByName("Ball")->getComponent<BallController>()->setPlayerPad(m_map->findGameObjectByName("Player"));

	esLogMessage("Init... %d", cc++);
	// Move camera to middle of map.
	m_map->getCamera()->setPosition(vec2(m_map->getWidth() / 2.0f - 1.0f, m_map->getHeight() / 2.0f - 0.5f));

	m_map->findGameObjectByName("Player")->getComponent<PlayerPaddleController>()->setBall(m_map->findGameObjectByName("Ball"));

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

	if (m_map->getLayer("Bricks")->getGameObjects().size() == 0)
	{
		m_map->findGameObjectByName("Ball")->getComponent<BallController>()->stopBall();
	}

	slm::vec2 collisionNormal;

	// Static collisions
	for (int i = 0; i < m_map->getLayer("StaticColliders")->getGameObjects().size(); i++)
	{
		if (m_map->findGameObjectByName("Ball")->collidesTo(m_map->getLayer("StaticColliders")->getGameObjects()[i], &collisionNormal))
		{
			m_map->findGameObjectByName("Ball")->getComponent<BallController>()->HandleCollision(m_map->getLayer("StaticColliders")->getGameObjects()[i], collisionNormal, deltaTime);
		}
	}

	// Object collisions
	for (int i = 0; i < m_map->getLayer("Bricks")->getGameObjects().size(); i++)
	{
		if (m_map->findGameObjectByName("Ball")->collidesTo(m_map->getLayer("Bricks")->getGameObjects()[i], &collisionNormal))
		{
			m_map->findGameObjectByName("Ball")->getComponent<BallController>()->HandleCollision(m_map->getLayer("Bricks")->getGameObjects()[i], collisionNormal, deltaTime);
			m_map->deleteGameObject(m_map->getLayer("Bricks")->getGameObjects()[i]);
		}
	}

	// Ball colliding player paddle
	if (m_map->findGameObjectByName("Ball")->collidesTo(m_map->findGameObjectByName("Player"), &collisionNormal))
	{
		m_map->findGameObjectByName("Ball")->getComponent<BallController>()->HandleCollision(m_map->findGameObjectByName("Player"), collisionNormal, deltaTime);
	}
		
	if (isKeyReleased(KEY_ESCAPE))
	{
		getApp()->setState(new MainMenuState(getApp()));
		return true;
	}

	if (m_map->getLayer("Bricks")->getGameObjects().size() == 0)
	{
		getApp()->setState(new MainMenuState(getApp()));
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