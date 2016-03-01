#include "PlayerPaddleController.h" // Include Player class header

#include "Input.h"

using namespace yam2d; // Use namespace yam3d implicitily.



PlayerPaddleController::PlayerPaddleController(GameObject* owner)
	: Component(owner, Component::getDefaultProperties()) // Initalize base class by giving parameres to it
{
	maxSpeed = 10.0f;
	velocity = slm::vec2(0.0f);
	increment = 35.0f;
}


PlayerPaddleController::~PlayerPaddleController(void)
{
}

void PlayerPaddleController::update(float deltaTime)
{
	if (getKeyState(KEY_LEFT) && getGameObject()->getPosition().x > 1.0f)
	{
		if (velocity.x > -maxSpeed)
		{
			velocity.x -= deltaTime*increment;
		}		
	}
	if (getKeyState(KEY_RIGHT) && getGameObject()->getPosition().x < 17.0f)
	{
		if (velocity.x < maxSpeed)
		{
			velocity.x += deltaTime*increment;
		}		
	}

	// TODO: fix unwanted moving
	if (getKeyState(KEY_LEFT) || getKeyState(KEY_RIGHT))
	{
		// Let it move
	}	
	else
	{
		if (velocity.x > 0.0f)
			velocity.x -= deltaTime*9.0f;
		if (velocity.x < 0.0f)
			velocity.x += deltaTime*9.0f;
		if (abs(velocity.x) < 0.1f)
		{
			velocity.x = 0.0f;
		}
	}	

	getGameObject()->setPosition(getGameObject()->getPosition() + deltaTime*velocity);
	//getGameObject()->setPosition(ball->getPosition().x + deltaTime*velocity.x, 11.0f);
}

