#include "GameRunningState2.h"
#include "GameApp.h"
#include "MainMenuState.h"
#include <iostream>

GameRunningState2::GameRunningState2(GameApp* app) : GameState(app), amoutOfPegs(0), victoryState(false)
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

	amoutOfPegs = m_map->getLayer("Objects")->getGameObjects().size() - 1;

	esLogMessage("Init... %d", cc++);
	// Move camera to middle of map.
	m_map->getCamera()->setPosition(vec2(m_map->getWidth() / 2.0f - 1.0f, m_map->getHeight() / 2.0f - 0.5f));

	esLogMessage("Init... %d", cc++);
	// Load font texture. Made with font creation tool like bitmap font builder.

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
			GameObject* tryPickEmpty = m_map->getLayer("Objects")->pick(mouseInMapCoordinates);
			if (tryPickEmpty && tryPickEmpty->getName() == "Empty")
			{
				slm::vec2 m_slope = slope(pickedObject->getPosition(), tryPickEmpty->getPosition());

				if (m_slope.x < 0.001f || m_slope.y < 0.001f)
				{
					if (abs(lenght(m_slope) - 2) < 0.05f)
					{
						slm::vec2 norm = slm::normalize(m_slope);

						GameObject* tryPickBetween = m_map->getLayer("Objects")->pick(pickedObject->getPosition() + norm);
						if (tryPickBetween->getName() == "studd")
						{
							addEmpty(tryPickBetween->getPosition()); // add empty to removed studd position
							m_map->deleteGameObject(tryPickBetween); // remove studd between
							
							addEmpty(pickedObject->getPosition()); // add empty to removed studd old position
							pickedObject->setPosition(tryPickEmpty->getPosition()); // set picked studd to new position
							m_map->deleteGameObject(tryPickEmpty); // remove empty where pickedObject went

							amoutOfPegs--;
						}
					}
				}
			}
			else
			{
				pickedObject->setRotation(0.0f);
			}						
		}
		
		GameObject* tryPick = m_map->getLayer("Objects")->pick(mouseInMapCoordinates);
		if (tryPick && tryPick->getName() == "studd")
		{
			pickedObject = tryPick;
			pickedObject->setRotation(0.20f);
		}
	}

	if (isKeyReleased(KEY_ESCAPE))
	{
		getApp()->setState(new MainMenuState(getApp()));
		return true;
	}

	if (victoryState == false && amoutOfPegs == 1)
	{
		addVoitit(slm::vec2((ctx->width / m_map->getTileHeight()) / 2.0f, (ctx->height / m_map->getTileHeight()) / 2.0f));
		victoryState = true;
	}

	std::cout << amoutOfPegs << std::endl;

	return true;
}

void GameRunningState2::draw(ESContext* ctx)
{
	// Set screen size to camera.
	m_map->getCamera()->setScreenSize(ctx->width, ctx->height, 720, 1280.0f / 720.0f);

	// Render map and all of its layers containing GameObjects to screen.
	m_map->render();
}