#include "MainMenuState.h"

#include "GameRunningState.h"
#include "GameApp.h"

MainMenuState::MainMenuState(GameApp* app) : GameState(app)
{
	esLogMessage(__FUNCTION__);
	int cc = 0;

	//Map Tilesize
	vec2 tileSize(128, 128);

	m_map = new Map(tileSize.x, tileSize.y);

	Layer* backgroundLayer = new Layer(m_map, "Background", 1.0f, true, false);
	m_map->addLayer(Map::BACKGROUND0, backgroundLayer);

	// Create new sprite GameObject from texture (background sprite) size is same than screen size.
	GameObject* backgroundGameObject = createSpriteGameObject("splash.png", 1280.0f, 720.0f);

	backgroundLayer->addGameObject(backgroundGameObject);

	//Adding menu buttons
	Layer* objectLayer = new Layer(m_map, "Objects", 1.0f, true, false);

	// Add created layer to be at MAPLAYER0-layer (depth/drawing order of the layer)
	m_map->addLayer(Map::MAPLAYER0, objectLayer);

	// Create new start game object
	GameObject* start = createSpriteGameObject("StartExit.png", tileSize.x, tileSize.y,0,0,128,128);

	start->setName("start");
	// Add start to level
	objectLayer->addGameObject(start);
	// Set position
	start->setPosition(vec2(0, -0.51f));

	// Create new start game object
	GameObject* exit = createSpriteGameObject("StartExit.png", tileSize.x, tileSize.y,128,0,128,128);

	exit->setName("exit");
	// Add exit to level
	objectLayer->addGameObject(exit);
	// Set position
	exit->setPosition(vec2(0, 0.51f));

	esLogMessage("Init... Done");
}

MainMenuState::~MainMenuState()
{
}

bool MainMenuState::update(ESContext* ctx, float deltaTime)
{
	m_map->getCamera()->setPosition(0, 0);

	float mouseX = float(getMouseAxisX());
	float mouseY = float(getMouseAxisY());

	if (isMouseButtonReleased(MOUSE_LEFT))
	{
		mouseWasPressedAndReleased = true;
	}

	vec2 mouseInMapCoordinates = m_map->screenToMapCoordinates(mouseX, mouseY);
	
	if (mouseWasPressedAndReleased == true)
	{
		pickedObject = m_map->getLayer("Objects")->pick(mouseInMapCoordinates);

		if (pickedObject && pickedObject->getName() == "start")
		{
			esLogMessage("Object %s picked at position %2.2f,%2.2f!",
				pickedObject->getName().c_str(),
				pickedObject->getPosition().x,
				pickedObject->getPosition().y," (start selected)");

			getApp()->setState(new GameRunningState(getApp()));
			return true;
		}
		if (pickedObject && pickedObject->getName() == "exit")
		{
			esLogMessage("Object %s picked at position %2.2f,%2.2f!",
				pickedObject->getName().c_str(),
				pickedObject->getPosition().x,
				pickedObject->getPosition().y, " (exit selected)");
			return false;
		}
		else
		{
			esLogMessage("Object not picked!");
		}
	}

	m_map->update(deltaTime);
	mouseWasPressedAndReleased = false;
	return true;
}

void MainMenuState::draw(ESContext* ctx)
{
	// Set screen size to camera.
	m_map->getCamera()->setScreenSize(ctx->width, ctx->height, 720, 1280.0f / 720.0f);

	// Render map and all of its layers containing GameObjects to screen.
	m_map->render();
}