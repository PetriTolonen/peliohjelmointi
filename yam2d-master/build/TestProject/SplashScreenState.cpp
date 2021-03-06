#include "SplashScreenState.h"

#include "MainMenuState.h"
#include "GameApp.h"

SplashScreenState::SplashScreenState(GameApp* app) : GameState(app)
{
	esLogMessage(__FUNCTION__);
	int cc = 0;

	esLogMessage("Init... %d", cc++);
	// Create new sprite batch group. This must be deleted at deinit.
	batch = new SpriteBatchGroup();

	esLogMessage("Init... %d", cc++);
	// Load texture to be used as texture for sprite.
	splashTexture = new Texture("assets/splash.png");

	esLogMessage("Init... %d", cc++);
	// Create new sprite, with default parameters.
	m_sprite = new Sprite(0);

	esLogMessage("Init... %d", cc++);
	// Load font texture. Made with font creation tool like bitmap font builder.
	fontTexture = new Texture("assets/Fixedsys_24_Bold.png");

	esLogMessage("Init... %d", cc++);
	// Create font clip areas (sprite sheet), from dat file and texture. Dat-file is made with bitmap font builder.
	font = SpriteSheet::autoFindFontFromTexture(fontTexture, "assets/Fixedsys_24_Bold.dat");

	esLogMessage("Init... %d", cc++);
	// Create new text-object
	text = new Text(0, font);

	esLogMessage("Init... %d", cc++);
	// Text color
	text->setColor(0.0f, 1.0f, 0.5f);
	text->setDepth(1.0f);

	esLogMessage("Init... Done");
}

SplashScreenState::~SplashScreenState()
{
}

bool SplashScreenState::update(ESContext* ctx, float deltaTime)
{
	//esLogMessage(__FUNCTION__);
	// Update total time counter.
	m_timer += deltaTime;

	// Set text.
	text->setText("Splash screen");

	// Clear sprite before add new dynamic sprites.
	batch->clear();

	// Add sprite. Rotate it according to total time.
	batch->addSprite(splashTexture, m_sprite, vec2(0, 0), 0, vec2(720));

	// Add text to position -400,300
	batch->addText(fontTexture, text, vec2(-ctx->width / 2.5f, ctx->height / 2.5f), 0);

	if (m_timer > 5.0f)
	{
		getApp()->setState(new MainMenuState(getApp()));
	}

	return true;
}

void SplashScreenState::draw(ESContext* ctx)
{
	// Draw batched objects to screen.
	batch->render();
}