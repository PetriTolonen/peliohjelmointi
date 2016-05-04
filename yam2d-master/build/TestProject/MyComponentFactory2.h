#pragma once

#include <Map.h>
#include <es_util.h>

#include <Sprite.h>
#include <SpriteBatch.h>
#include <SpriteSheet.h>
#include <SpriteComponent.h>
#include <Text.h>
#include <Texture.h>

#include "PlayerPaddleController.h"
#include "BallController.h"

using namespace yam2d;

class MyComponentFactory2 : public DefaultComponentFactory
{
private:
	Map* m_map;

public:
	MyComponentFactory2()
		:DefaultComponentFactory()
		, m_map(0)
	{
	}

	void setCurrentMap(Map* map)
	{
		m_map = map;
	}

	virtual ~MyComponentFactory2()
	{
	}

	virtual Component* createNewComponent(const std::string& type, Entity* parent, const yam2d::PropertySet& properties)
	{
		// TODO: Implementation... Use now default implementation instead.
		return DefaultComponentFactory::createNewComponent(type, parent, properties);
	}


	virtual Entity* createNewEntity(ComponentFactory* componentFactory, const std::string& type, Entity* parent, const yam2d::PropertySet& properties)
	{
		if ("Wall" == type)
		{
			esLogMessage("Wall created by MyComponentFactory2");
			GameObject* gameObject = new GameObject(parent, properties);
			gameObject->addComponent(componentFactory->createNewComponent("Tile", gameObject, properties));
			return gameObject;
		}
		
		else if ("studd" == type)
		{
			esLogMessage("studd created by MyComponentFactory2");
			GameObject* gameObject = new GameObject(parent, properties);
			gameObject->addComponent(componentFactory->createNewComponent("Tile", gameObject, properties));
			return gameObject;
		}

		else if ("Empty" == type)
		{
			esLogMessage("Empty created by MyComponentFactory2");
			GameObject* gameObject = new GameObject(parent, properties);
			gameObject->addComponent(componentFactory->createNewComponent("Tile", gameObject, properties));
			return gameObject;
		}

		// Default functionality.
		Entity* res = DefaultComponentFactory::createNewEntity(componentFactory, type, parent, properties);
		assert(res != 0);
		return res;
	}
};