#include "BallController.h" // Include Player class header

#include "Input.h"
#include <iostream>

using namespace yam2d; // Use namespace yam3d implicitily.

BallController::BallController(GameObject* owner)
	: Component(owner, Component::getDefaultProperties()) // Initalize base class by giving parameres to it
{
	moveSpeedX = 3.5f; // tiles / second
	moveSpeedY = 3.5f; // tiles / second
	moving = false;
	gameOver = false;
	beginningVelocity = slm::vec2(moveSpeedX, -moveSpeedY);
	velocity = beginningVelocity;
	lives = 3;
	removeFromInside = slm::vec2(0.0f);
	overlapOffset = 0.05f;
	dampingSpeed = 8.0f;
	paddleVelocityFactor = 10.0f;
	count = 0;
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
		velocity.x = pad->getComponent<PlayerPaddleController>()->getVelocity().x;
	}

	if (moving)
	{
		//std::cout << removeFromInside.x << " " << removeFromInside.y <<std::endl;
		getGameObject()->setPosition(getGameObject()->getPosition() + deltaTime*(velocity +removeFromInside));
	}

	else if (!gameOver)
	{
		getGameObject()->setPosition(slm::vec2(pad->getPosition().x, pad->getPosition().y - 1.1f));
	}	
}

void BallController::HandleCollision(GameObject* otherObj, const slm::vec2& collisionNormal, float deltaTime)
{
	if (otherObj->getName() == "Bottom")
	{
		if (lives == 0)
		{
			gameOver = true;
			moving = false;
			velocity = beginningVelocity;
			return;
		}
		else
		{
			lives--;
			moving = false;
			velocity = beginningVelocity;
			return;
		}
	}

	// for debugging
	/*count++;
	std::cout << "colliding " << count << std::endl;*/

	if (moving)
	{
		slm::vec2 tempNormal = collisionNormal;
		removeFromInside = slm::vec2(0.0f);
		
		// First checking if hitting right or left side
		if ((1 - abs(collisionNormal.x)) < (1- abs(collisionNormal.y)))
		{
			if (velocity.x > 0)
			{
				removeFromInside.x = -(1 - abs(tempNormal.x)) - overlapOffset;
			}
			else
			{
				removeFromInside.x = (1 - abs(tempNormal.x)) + overlapOffset;
			}
			tempNormal.y = 0.0f;			
		}
		// Else hitting top or bottom side
		else
		{
			if (velocity.y > 0)
			{
				removeFromInside.y = -(1 - abs(tempNormal.y)) - overlapOffset;
			}
			else
			{
				removeFromInside.y = (1 - abs(tempNormal.y)) + overlapOffset;
			}
			tempNormal.x = 0.0f;
		}
		
		slm::vec3 temp = slm::vec3(velocity, 0.0f);
		slm::vec3 temp2 = normalize(slm::vec3(tempNormal, 0.0f));

		slm::vec3 newvelocity = slm::reflect(temp, temp2);
		velocity = slm::vec2(newvelocity.x, newvelocity.y);

		if (otherObj->getName() == "Player")
		{			
			velocity.x += deltaTime*paddleVelocityFactor*otherObj->getComponent<PlayerPaddleController>()->getVelocity().x;
		}

		if (velocity.x > 4.0f )
		{
			velocity.x -= deltaTime*dampingSpeed;
		}
		if (velocity.x < -4.0f)
		{
			velocity.x += deltaTime*dampingSpeed;
		}
	}	
}

