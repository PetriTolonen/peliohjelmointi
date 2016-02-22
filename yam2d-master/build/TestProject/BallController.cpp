#include "BallController.h" // Include Player class header

#include "Input.h"

using namespace yam2d; // Use namespace yam3d implicitily.



BallController::BallController(GameObject* owner)
	: Component(owner, Component::getDefaultProperties()) // Initalize base class by giving parameres to it
{
	moveSpeed = 3.5f; // tiles / second
	moving = false;
	gameOver = false;
	BeginningDirection = slm::vec2(moveSpeed, -moveSpeed);
	direction = BeginningDirection;
	lives = 3;
}


BallController::~BallController(void)
{
}

void BallController::update(float deltaTime)
{
	if (gameOver)
	{
		// TODO 
	}
	
	if (isKeyPressed(KEY_SPACE))
	{
		moving = true;
		esLogMessage("Space pressed: Ball moving");
	}

	if (moving)
	{
		getGameObject()->setPosition(getGameObject()->getPosition() + deltaTime*direction);
	}
	else if (!gameOver)
	{
		getGameObject()->setPosition(slm::vec2(pad->getGameObject()->getPosition().x, pad->getGameObject()->getPosition().y - 1));
	}	
}

void BallController::HandleCollision(GameObject* otherObj)
{
	if (otherObj->getName() == "Right" && direction.y > 0)
	{
		direction = slm::vec2(-moveSpeed, moveSpeed);
	}
	else if (otherObj->getName() == "Right" && direction.y < 0)
	{
		direction = slm::vec2(-moveSpeed, -moveSpeed);
	}

	else if (otherObj->getName() == "Left" && direction.y > 0)
	{
		direction = slm::vec2(moveSpeed, moveSpeed);
	}
	else if (otherObj->getName() == "Left" && direction.y < 0)
	{
		direction = slm::vec2(-moveSpeed, -moveSpeed);
	}

	else if (otherObj->getName() == "Top" && direction.x > 0)
	{
		direction = slm::vec2(moveSpeed, moveSpeed);
	}
	else if (otherObj->getName() == "Top" && direction.x < 0)
	{
		direction = slm::vec2(-moveSpeed, moveSpeed);
	}
	
	else if (otherObj->getName() == "Bottom")
	{
		if (lives = 0)
		{
			gameOver = true;
		}
		else
		{
			lives--;
			moving = false;
			direction = BeginningDirection;
		}
	}
}

