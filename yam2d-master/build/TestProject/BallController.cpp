#include "BallController.h" // Include Player class header

#include "Input.h"

using namespace yam2d; // Use namespace yam3d implicitily.

BallController::BallController(GameObject* owner)
	: Component(owner, Component::getDefaultProperties()) // Initalize base class by giving parameres to it
{
	moveSpeedX = 3.5f; // tiles / second
	moveSpeedY = 3.5f; // tiles / second
	moving = false;
	gameOver = false;
	BeginningDirection = slm::vec2(moveSpeedX, -moveSpeedY);
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
	
	if (isKeyPressed(KEY_SPACE) && !moving)
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
		getGameObject()->setPosition(slm::vec2(pad->getGameObject()->getPosition().x, pad->getGameObject()->getPosition().y - 1.1f));
	}	
}

void BallController::HandleCollision(GameObject* otherObj, const slm::vec2& collisionNormal)
{
	if (otherObj->getName() == "Bottom")
	{
		if (lives == 0)
		{
			gameOver = true;
			moving = false;
			direction = BeginningDirection;
			return;
		}
		else
		{
			lives--;
			moving = false;
			direction = BeginningDirection;
			return;
		}
	}

	// TODO: how to?
	/*if (otherObj->getName() == "Player")
	{
		moveSpeedX += collisionNormal.x*3;
	}*/

	if (moving)
	{
		// First checking if hitting right or left side
		if ((1 - abs(collisionNormal.x)) < (1- abs(collisionNormal.y)))
		{
			// Ball going up hits object to the left side
			if (collisionNormal.x < 0 && direction.y < 0)
			{
				direction = slm::vec2(-moveSpeedX, -moveSpeedY);
			}
			// Ball going down hits object to the left side
			else if (collisionNormal.x < 0 && direction.y > 0)
			{
				direction = slm::vec2(-moveSpeedX, moveSpeedY);
			}

			// Ball going up hits object to the right side
			else if (collisionNormal.x > 0 && direction.y < 0)
			{
				direction = slm::vec2(moveSpeedX, -moveSpeedY);
			}
			// Ball going down hits object to the right side
			else if (collisionNormal.x > 0 && direction.y > 0)
			{
				direction = slm::vec2(moveSpeedX, moveSpeedY);
			}
		}
		// Else hitting top or bottom side
		else
		{
			// Ball going left hits object to the bottom side
			if (collisionNormal.y > 0 && direction.x < 0)
			{
				direction = slm::vec2(-moveSpeedX, moveSpeedY);
			}
			// Ball going right hits object to the bottom side
			else if (collisionNormal.y > 0 && direction.x > 0)
			{
				direction = slm::vec2(moveSpeedX, moveSpeedY);
			}

			// Ball going left hits object to the top side
			else if (collisionNormal.y < 0 && direction.x < 0)
			{
				direction = slm::vec2(-moveSpeedX, -moveSpeedY);
			}
			// Ball going right hits object to the top side
			else if (collisionNormal.y < 0 && direction.x > 0)
			{
				direction = slm::vec2(moveSpeedX, -moveSpeedY);
			}
		}		
	}	
}

