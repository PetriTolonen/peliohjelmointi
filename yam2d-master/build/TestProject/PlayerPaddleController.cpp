#include "PlayerPaddleController.h" // Include Player class header

#include "Input.h"

using namespace yam2d; // Use namespace yam3d implicitily.



PlayerPaddleController::PlayerPaddleController(GameObject* owner)
	: Component(owner, Component::getDefaultProperties()) // Initalize base class by giving parameres to it
{
}


PlayerPaddleController::~PlayerPaddleController(void)
{
}

void PlayerPaddleController::update(float deltaTime)
{
	float moveSpeed = 4.0f; // tiles / second

	if (getKeyState(KEY_LEFT))
	{
		getGameObject()->setPosition(getGameObject()->getPosition() + deltaTime*moveSpeed*vec2(-1.0f,0.0f));
	}
	if (getKeyState(KEY_RIGHT))
	{
		getGameObject()->setPosition(getGameObject()->getPosition() + deltaTime*moveSpeed*vec2(1.0f, 0.0f));
	}
}

