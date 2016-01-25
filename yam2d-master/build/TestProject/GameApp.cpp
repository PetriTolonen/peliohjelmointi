#include "GameApp.h"

// Update game
bool GameApp::update(ESContext* ctx, float deltaTime)
{
	m_currentState->update(ctx, deltaTime);
	return true;
}


// Draw game
void GameApp::draw(ESContext *ctx)
{
	m_currentState->draw(ctx);
}

