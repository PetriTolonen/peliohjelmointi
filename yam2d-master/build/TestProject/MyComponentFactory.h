#pragma once

#include <Map.h>
#include <es_util.h>

#include <Sprite.h>
#include <SpriteBatch.h>
#include <SpriteSheet.h>
#include <SpriteComponent.h>
#include <Text.h>
#include <Texture.h>

using namespace yam2d;

class MyComponentFactory : public DefaultComponentFactory
{
private:
	Map* m_map;

public:
	MyComponentFactory()
		:DefaultComponentFactory()
		, m_map(0)
	{
	}

	void setCurrentMap(Map* map)
	{
		m_map = map;
	}

	virtual ~MyComponentFactory()
	{
	}

	virtual Component* createNewComponent(const std::string& type, Entity* parent, const yam2d::PropertySet& properties)
	{
		// TODO: Implementation... Use now default implementation instead.
		return DefaultComponentFactory::createNewComponent(type, parent, properties);
	}


	virtual Entity* createNewEntity(ComponentFactory* componentFactory, const std::string& type, Entity* parent, const yam2d::PropertySet& properties)
	{
		esLogMessage("1");
		if ("StaticColliders" == type)
		{
			esLogMessage("2");
			GameObject* gameObject = new GameObject(parent, properties);
			return gameObject;
		}
		
		else if ("Ball" == type)
		{
			GameObject* gameObject = new GameObject(0, 0);
			gameObject->addComponent(componentFactory->createNewComponent("Tile", gameObject, properties));
			return gameObject;
		}
		
		else if ("Brick" == type)
		{
			esLogMessage("3");
			GameObject* gameObject = new GameObject(0, 0);
			gameObject->addComponent(componentFactory->createNewComponent("Tile", gameObject, properties));
			return gameObject;
		}
		
		else if ("PlayerPad" == type)
		{
			esLogMessage("4");
			// Create new player.
			GameObject* gameObject = new GameObject(0, 0);
			gameObject->addComponent(componentFactory->createNewComponent("Tile", gameObject, properties));
			return gameObject;
		}
	

		// Default functionality.
		Entity* res = DefaultComponentFactory::createNewEntity(componentFactory, type, parent, properties);
		assert(res != 0);
		return res;
	}
};