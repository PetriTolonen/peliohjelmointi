#include "MainMenuState.h"

#include <SpriteComponent.h>
#include <Input.h>

GameObject* createSpriteGameObject(const std::string& bitmapFileName, float sizeX, float sizeY, bool isWhiteTransparentColor = false)
{
	// Load texture to be used as texture for sprite.
	Texture* texture = new Texture(bitmapFileName.c_str());

	// If user wants to create texture which white coros is treated as atransparent color.
	if (isWhiteTransparentColor)
	{
		// Set white to transparent. Here color values are from 0 to 255 (RGB)
		texture->setTransparentColor(255, 255, 255);
	}

	// Create new sprite GameObject from texture.
	GameObject* gameObject = new GameObject(0, 0);
	SpriteComponent* sprite = new SpriteComponent(gameObject, texture);

	// Resize the sprite to be correct size
	gameObject->setSize(sizeX, sizeY);

	// Add sprite component to game object
	gameObject->addComponent(sprite);
	return gameObject;
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
	GameObject* backgroundGameObject = createSpriteGameObject("splash.png", 1280.0f, 720.0f);

	backgroundLayer->addGameObject(backgroundGameObject);

	//Adding menu buttons
	Layer* objectLayer = new Layer(m_map, "Objects", 1.0f, true, false);

	// Add created layer to be at MAPLAYER0-layer (depth/drawing order of the layer)
	m_map->addLayer(Map::MAPLAYER0, objectLayer);

	// Create new start game object
	GameObject* start = createSpriteGameObject("start.png", tileSize.x, tileSize.y);
	// Add start to level
	objectLayer->addGameObject(start);
	// Set position
	start->setPosition(vec2(0, 0));

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

	if (isMouseButtonPressed(MOUSE_LEFT))
	{
		vec2 mouseInMapCoordinates = m_map->screenToMapCoordinates(mouseX, mouseY);
		
		if (isMouseButtonReleased(MOUSE_LEFT))
		{
			GameObject* pickedObject = m_map->getLayer("Objects")->pick(mouseInMapCoordinates);

			if (pickedObject)
			{
				esLogMessage("Object %s picked at position %2.2f,%2.2f!",
					pickedObject->getName().c_str(),
					pickedObject->getPosition().x,
					pickedObject->getPosition().y);
			}
			else
			{
				esLogMessage("Object not picked!");
			}
		}		
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