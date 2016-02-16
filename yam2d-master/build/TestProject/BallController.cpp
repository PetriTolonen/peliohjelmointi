#include "BallController.h" // Include Player class header

#include "Input.h"

using namespace yam2d; // Use namespace yam3d implicitily.



BallController::BallController(GameObject* owner)
	: Component(owner, Component::getDefaultProperties()) // Initalize base class by giving parameres to it
{
	float moveSpeed = 3.5f; // tiles / second
	moving = false;
	direction = slm::vec2(moveSpeed, -moveSpeed);
}


BallController::~BallController(void)
{
}

void BallController::update(float deltaTime)
{
	

	if (isKeyPressed(KEY_SPACE))
	{
		moving = true;
		esLogMessage("Space pressed: Ball moving");
	}

	if (moving)
	{
		getGameObject()->setPosition(getGameObject()->getPosition() + deltaTime*direction);
	}
	else
	{
		getGameObject()->setPosition(slm::vec2(pad->getGameObject()->getPosition().x, getGameObject()->getPosition().y));
	}

	
}

