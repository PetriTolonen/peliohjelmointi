#include "MainMenuState.h"

#include "GameRunningState.h"
#include "GameApp.h"

void MainMenuState::toRunningState()
{
	getApp()->setState(new GameRunningState(getApp()));
}

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
	GameObject* backgroundGameObject = createSpriteGameObject("assets/abstractbackground.png", 1280.0f, 720.0f);

	backgroundLayer->addGameObject(backgroundGameObject);

	//Adding menu buttons
	Layer* objectLayer = new Layer(m_map, "Objects", 1.0f, true, false);

	// Add created layer to be at MAPLAYER0-layer (depth/drawing order of the layer)
	m_map->addLayer(Map::MAPLAYER0, objectLayer);

	// Create new start game object
	GameObject* start = createSpriteGameObject("assets/StartExit2.png", tileSize.x, tileSize.y,0,0,128,128);

	start->setName("start");
	// Add start to level
	objectLayer->addGameObject(start);
	// Set position
	start->setPosition(vec2(1.4f, -0.7f));

	// Create new start game object
	GameObject* exit = createSpriteGameObject("assets/StartExit2.png", tileSize.x, tileSize.y,0,128,128,128);

	exit->setName("exit");
	// Add exit to level
	objectLayer->addGameObject(exit);
	// Set position
	exit->setPosition(vec2(1.4f, 0.7f));

	currentSelection = 0;
	m_map->getLayer("Objects")->getGameObjects()[currentSelection]->getComponent<SpriteComponent>()->getSprite()->setColor(0.0f, 1.0f, 0.4f);


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

	// Mouse picks start or exit.
	vec2 mouseInMapCoordinates = m_map->screenToMapCoordinates(mouseX, mouseY);
	pickedObject = m_map->getLayer("Objects")->pick(mouseInMapCoordinates);

	// Changing currentSelection from mouse.
	if (pickedObject && pickedObject->getName() == "start")
	{
		currentSelection = 0;
	}
	else if (pickedObject && pickedObject->getName() == "exit")
	{
		currentSelection = 1;
	}

	// Keyboard changes currentSelection up and down.
	if (isKeyReleased(KEY_UP) || isKeyReleased(KEY_W))
	{
		if (currentSelection > 0)
		{
			currentSelection--;
		}

		return true;
	}

	if (isKeyReleased(KEY_DOWN)|| isKeyReleased(KEY_S))
	{

		if (currentSelection < 1)
		{
			currentSelection++;
		}

		return true;
	}

	// Clearing color from all selections.
	for (int i = 0; i < m_map->getLayer("Objects")->getGameObjects().size(); i++)
	{
		m_map->getLayer("Objects")->getGameObjects()[i]->getComponent<SpriteComponent>()->getSprite()->setColor(1.0f, 1.0f, 1.0f);
	}

	// Color current selection.
	m_map->getLayer("Objects")->getGameObjects()[currentSelection]->getComponent<SpriteComponent>()->getSprite()->setColor(0.0f, 1.0f, 0.4f);

	// Mouse selection by pressing left mouse button.
	if (isMouseButtonReleased(MOUSE_LEFT))
	{
		if (pickedObject && pickedObject->getName() == "start")
		{
			esLogMessage("Object %s picked at position %2.2f,%2.2f!",
				pickedObject->getName().c_str(),
				pickedObject->getPosition().x,
				pickedObject->getPosition().y, " (start selected with mouse)");

			toRunningState();
			return true;
		}
		if (pickedObject && pickedObject->getName() == "exit")
		{
			esLogMessage("Object %s picked at position %2.2f,%2.2f!",
				pickedObject->getName().c_str(),
				pickedObject->getPosition().x,
				pickedObject->getPosition().y, " (exit selected with mouse)");
			return false;
		}
		else
		{
			esLogMessage("Object not picked!");
		}
	}

	// Keyboard return selectes currentSelection.
	if (isKeyReleased(KEY_RETURN))
	{
		switch (currentSelection)
		{
		case 0:
		{
			toRunningState();
			break;
		}
		case 1:
		{
			return false;
		}		

		default:
			break;
		}
		return true;
	}

	m_map->update(deltaTime);
	return true;
}

void MainMenuState::draw(ESContext* ctx)
{
	// Set screen size to camera.
	m_map->getCamera()->setScreenSize(ctx->width, ctx->height, 720, 1280.0f / 720.0f);

	// Render map and all of its layers containing GameObjects to screen.
	m_map->render();
}