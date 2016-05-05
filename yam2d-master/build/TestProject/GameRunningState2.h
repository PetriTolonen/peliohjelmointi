#pragma once

#include "GameState.h"
#include "MyComponentFactory2.h"
#include "Tileset.h"
#include "TileComponent.h"
#include "SpriteComponent.h"

class GameRunningState2 : public GameState
{
public:
	GameRunningState2(GameApp* app);
	virtual ~GameRunningState2();
	virtual bool update(ESContext* ctx, float deltaTime);
	virtual void draw(ESContext* ctx);
private:
	Ref<TmxMap> m_map;
	MyComponentFactory2* componentFactory2;
	Ref<GameObject> pickedObject;

	slm::vec2 oldPos;
	slm::vec2 currentPos;

	slm::vec2 slope(slm::vec2 pos, slm::vec2 pos2)
	{
		return slm::vec2(pos2.x - pos.x, pos2.y - pos.y);
	}

	float lenght(slm::vec2 slope)
	{
		return sqrt(pow(slope.x, 2) + pow(slope.y, 2));
	}

	void addEmpty(slm::vec2 pos)
	{
		GameObject* gameObject = new GameObject(0, 0);

		// Resize the sprite to be correct size
		int tileSizeX = m_map->getTileWidth();
		int tileSizeY = m_map->getTileWidth();
		gameObject->setSize(tileSizeX, tileSizeY);
		gameObject->setPosition(pos);
		gameObject->setName("Empty");
		m_map->getLayer("Objects")->addGameObject(gameObject);
	}

	void addVoitit(slm::vec2 pos)
	{
		GameObject* gameObject = new GameObject(0, 0);

		// Resize the sprite to be correct size
		gameObject->setSize(256.0f, 256.0f);
		gameObject->setPosition(pos);
		gameObject->setName("Voitto");
		Texture* texture = new Texture("assets/Voitit.png");
		gameObject->addComponent(new SpriteComponent(gameObject, texture));
		m_map->getLayer("Objects")->addGameObject(gameObject);
	}

	int amoutOfPegs;

	bool victoryState;
};