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
	// Set OpenGL clear color
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set the viewport to be full window area.
	glViewport(0, 0, ctx->width, ctx->height);

	// Enable back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Enable alpha blending (transparency)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set projection to identity
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Calculate half screen size
	float left = -0.5f*ctx->width;
	float right = 0.5f*ctx->width;
	float bottom = -0.5f*ctx->height;
	float top = 0.5f*ctx->height;

	// Set OpenGL orthogonal projection for screen size <esContext->width,esContext->height>
	glOrthof(float(int(left)), float(int(right)), float(int(bottom)), float(int(top)), -1.0, 1.0f);
	m_currentState->draw(ctx);
}

