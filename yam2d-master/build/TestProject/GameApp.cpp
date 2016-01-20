#include "GameApp.h"

// Update game
bool GameApp::update(ESContext* ctx, float deltaTime)
{

}


// Draw game
void GameApp::draw(ESContext *esContext)
{
	// Set OpenGL clear color (dark gray)
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

}

