// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// http://code.google.com/p/yam2d/
//
// Copyright (c) 2013 Mikko Romppainen
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
// FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
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

