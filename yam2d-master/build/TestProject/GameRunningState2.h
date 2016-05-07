#pragma once

#include "GameState.h"
#include "MyComponentFactory2.h"
#include "Tileset.h"
#include "TileComponent.h"
#include "SpriteComponent.h"
#include <AnimatedSpriteComponent.h>
#include "GameApp.h"

#include "GameRunningState3.h"

#include <TextComponent.h>

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
		m_map->getLayer("UpperLayer")->addGameObject(gameObject);
	}

	GameObject* selection = 0;
	Ref<Texture> texture = 0;
	Ref<SpriteSheet> spriteSheet = 0;
	void addSelectionAnimation(slm::vec2 pos)
	{
		assert(selection == 0); // Only one explosion is allowed
		selection = new GameObject(0, 0);
		AnimatedSpriteComponent* animatedSprite = new AnimatedSpriteComponent(selection, spriteSheet);
		selection->addComponent(animatedSprite);
		selection->setSize(128, 128);
		std::vector<int> indices;
		indices.resize(spriteSheet->getClipCount());
		for (size_t i = 0; i<indices.size(); ++i)
		{
			indices[i] = i;
		}
		selection->setName("Selection");
		animatedSprite->addAnimation(0, SpriteAnimation::SpriteAnimationClip(indices, 2.0f, 1.0f, true));
		animatedSprite->setActiveAnimation(0);
		selection->setPosition(pos);
		m_map->getLayer("UpperLayer")->addGameObject(selection);
	}

	void toNextMap()
	{
		getApp()->setState(new GameRunningState3(getApp()));
	}

	int amoutOfPegs;

	bool victoryState;

	GameObject* createTextGameObject(const std::string& t)
	{
		// Load font texture. Made with font creation tool like bitmap font builder.
		Texture* fontTexture = new Texture("assets/Fixedsys_24_Bold.png");

		// Create font clip areas (sprite sheet), from dat file and texture. Dat-file is made with bitmap font builder.
		SpriteSheet* font = SpriteSheet::autoFindFontFromTexture(fontTexture, "assets/Fixedsys_24_Bold.dat");

		GameObject* gameObject = new GameObject(0, 0);
		TextComponent* textComponent = new TextComponent(gameObject, font);
		gameObject->addComponent(textComponent);
		textComponent->getText()->setText(t);
		textComponent->getText()->setColor(1.0f, 0.7f, 0.2f);

		return gameObject;
	}
};