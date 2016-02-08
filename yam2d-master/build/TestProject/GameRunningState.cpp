#include "GameRunningState.h"
#include "GameApp.h"
#include "MainMenuState.h"
#include <iostream>

GameRunningState::GameRunningState(GameApp* app) : GameState(app)
{
	esLogMessage(__FUNCTION__);
	int cc = 0;

	//Map Tilesize
	vec2 tileSize(128, 128);

	m_map = new TmxMap();
	componentFactory = new DefaultComponentFactory();

	m_map->loadMapFile("assets/level.tmx", componentFactory);

	// Move camera to middle of map.
	m_map->getCamera()->setPosition(vec2(m_map->getWidth() / 2.0f - 0.5f, m_map->getHeight() / 2.0f - 0.5f));
}

GameRunningState::~GameRunningState()
{
	//std::cout << "Runnig state destructor" << std::endl;
}

bool GameRunningState::update(ESContext* ctx, float deltaTime)
{
	m_map->update(deltaTime);

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