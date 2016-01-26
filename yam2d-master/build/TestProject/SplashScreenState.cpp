#include "SplashScreenState.h"
#include <iostream>
#include <SpriteComponent.h>

SplashScreenState::SplashScreenState()
{
	esLogMessage(__FUNCTION__);
	int cc = 0;

	esLogMessage("Init... %d", cc++);
	// Create new sprite batch group. This must be deleted at deinit.
	batch = new SpriteBatchGroup();

	esLogMessage("Init... %d", cc++);
	// Load texture to be used as texture for sprite.
	texture = new Texture("splash.png");

	esLogMessage("Init... %d", cc++);
	// Create new sprite, with default parameters.
	m_sprite = new Sprite(0);

	esLogMessage("Init... %d", cc++);
	// Load font texture. Made with font creation tool like bitmap font builder.
	fontTexture = new Texture("Fixedsys_24_Bold.png");

	esLogMessage("Init... %d", cc++);
	// Create font clip areas (sprite sheet), from dat file and texture. Dat-file is made with bitmap font builder.
	SpriteSheet* font = SpriteSheet::autoFindFontFromTexture(fontTexture, "Fixedsys_24_Bold.dat");

	esLogMessage("Init... %d", cc++);
	// Create new text-object
	text = new Text(0, font);

	esLogMessage("Init... Done");
}

SplashScreenState::~SplashScreenState()
{
	esLogMessage(__FUNCTION__);
	// Delete sprite batch group.
	delete m_sprite;
	delete text;
	delete batch;
}

bool SplashScreenState::update(ESContext* ctx, float deltaTime)
{
	//esLogMessage(__FUNCTION__);
	// Update total time counter.
	count += deltaTime;

	// Set text.
	text->setText("Splash!!");

	// Clear sprite before add new dynamic sprites.
	batch->clear();

	// Add sprite. Rotate it according to total time. We need also scale font a bit (100 times, so the sprite is 100x100 pixels).
	batch->addSprite(texture, m_sprite, vec2(0, 0), count, vec2(1));

	// Add text to position -400,300
	//batch->addText(fontTexture, text, vec2(-ctx->width / 3, ctx->height / 3), 0);

	return true;
}

void SplashScreenState::draw(ESContext* ctx)
{
	// Set OpenGL clear color
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set the viewport to be full window area.
	glViewport(0, 0, ctx->width, ctx->height);

	// Draw batched objects to screen.
	batch->render();
}