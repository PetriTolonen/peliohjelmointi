#ifndef PLAYER_H_
#define PLAYER_H_ 

// Include base class
#include <SpriteComponent.h>
#include <GameObject.h>
#include <vec2.h>

// Use yam2d::Component as base class for our player. Use also yam2d::Updatable -interface, for update-method.
class PlayerPaddleController : public yam2d::Component, public yam2d::Updatable
{
public:
	/** Constructor of player.
	*
	* @param gameObjectType Game specific game object type. Useful for for example detecting of "real game object type", like Player or Enemy.
	* @param texture Texture for our game object.
	*/
	PlayerPaddleController(yam2d::GameObject* parent);
	virtual ~PlayerPaddleController(void);

	// This virtual method is automatically called byt map/layer, when update is called from main.cpp
	virtual void update(float deltaTime);

	yam2d::GameObject* getGameObject() { return (yam2d::GameObject*)getOwner(); }
	const yam2d::GameObject* getGameObject() const { return (const yam2d::GameObject*)getOwner(); }
	const slm::vec2 getVelocity(){ return velocity; }
private:
	slm::vec2 velocity;
	float maxSpeed;
	float increment;
};


#endif