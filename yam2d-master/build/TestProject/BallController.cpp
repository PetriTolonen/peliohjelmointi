#include "BallController.h" // Include Player class header

#include "Input.h"

using namespace yam2d; // Use namespace yam3d implicitily.



BallController::BallController(GameObject* owner)
	: Component(owner, Component::getDefaultProperties()) // Initalize base class by giving parameres to it
{
	release = false;
}


BallController::~BallController(void)
{
}

void BallController::update(float deltaTime)
{
	float moveSpeed = 3.5f; // tiles / second

	if (isKeyReleased(KEY_SPACE))
	{
		release = true;
		esLogMessage("Space pressed: Ball released");
	}

	if (release == false)
	{
		
	}
}

