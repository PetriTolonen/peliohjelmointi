#include "GameRunningState2.h"
#include "GameApp.h"
#include "MainMenuState.h"
#include <iostream>

GameRunningState2::GameRunningState2(GameApp* app) : GameState(app)
{
	esLogMessage(__FUNCTION__);
	int cc = 0;

	esLogMessage("Init... %d", cc++);
	m_map = new TmxMap();

	esLogMessage("Init... %d", cc++);
	componentFactory2 = new MyComponentFactory2();

	esLogMessage("Init... %d", cc++);
	componentFactory2->setCurrentMap(m_map);

	esLogMessage("Init... %d", cc++);
	m_map->loadMapFile("assets/level2.tmx", componentFactory2);

	esLogMessage("Init... %d", cc++);
	// Move camera to middle of map.
	m_map->getCamera()->setPosition(vec2(m_map->getWidth() / 2.0f - 1.0f, m_map->getHeight() / 2.0f - 0.5f));

	esLogMessage("Init... Done");
}

GameRunningState2::~GameRunningState2()
{
	delete componentFactory2;
}

bool GameRunningState2::update(ESContext* ctx, float deltaTime)
{
	m_map->update(deltaTime);

	// Mouse picks
	float mouseX = float(getMouseAxisX());
	float mouseY = float(getMouseAxisY());

	vec2 mouseInMapCoordinates = m_map->screenToMapCoordinates(mouseX, mouseY);
	
	if (isMouseButtonReleased(MOUSE_LEFT))
	{
		if (pickedObject)
		{
			if (m_map->getLayer("Objects")->pick(mouseInMapCoordinates)->getName() == "Empty")
			{
				slm::vec2 m_slope = slope(pickedObject->getPosition(), m_map->getLayer("Objects")->pick(mouseInMapCoordinates)->getPosition());

				if (m_slope.x == 0.0f || m_slope.y == 0.0f)
				{
					if (abs(lenght(m_slope) - 2) < 0.05f)
					{
						slm::vec2 norm = slm::normalize(m_slope);

						if (m_map->getLayer("Objects")->pick(pickedObject->getPosition() + norm)->getName() == "studd")
						{
							m_map->deleteGameObject(m_map->getLayer("Objects")->pick(pickedObject->getPosition() + norm)); // remove studd between
							addEmpty(pickedObject->getPosition() + norm); // add empty to removed studd position
							m_map->deleteGameObject(m_map->getLayer("Objects")->pick(mouseInMapCoordinates)); //remove empty
							addEmpty(pickedObject->getPosition()); // add empty to removed studd position
							pickedObject->setPosition(m_map->getLayer("Objects")->pick(mouseInMapCoordinates)->getPosition()); // set picked studd to new position
						}
					}
				}
			}
			else
			{
				pickedObject->setRotation(0.0f);
			}						
		}
		
		if (m_map->getLayer("Objects")->pick(mouseInMapCoordinates)->getName() != "Empty")
		{
			pickedObject = m_map->getLayer("Objects")->pick(mouseInMapCoordinates);
		}

		if (pickedObject->getName() == "studd")
		{
			pickedObject->setRotation(0.20f);
		}
	}

	if (isKeyReleased(KEY_ESCAPE))
	{
		getApp()->setState(new MainMenuState(getApp()));
		return true;
	}

	return true;
}

void GameRunningState2::draw(ESContext* ctx)
{
	// Set screen size to camera.
	m_map->getCamera()->setScreenSize(ctx->width, ctx->height, 720, 1280.0f / 720.0f);

	// Render map and all of its layers containing GameObjects to screen.
	m_map->render();
}