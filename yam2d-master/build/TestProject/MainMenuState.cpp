#include "MainMenuState.h"

MainMenuState::MainMenuState()
{
	esLogMessage(__FUNCTION__);
	int cc = 0;

	esLogMessage("Init... %d", cc++);
	// Create new sprite batch group. This must be deleted at deinit.
	batch = new SpriteBatchGroup();

	esLogMessage("Init... %d", cc++);
	// Load texture to be used as texture for sprite.
	startTexture = new Texture("splash.png");

	esLogMessage("Init... %d", cc++);
	// Create new sprite, with default parameters.
	start = new Sprite(0);

	esLogMessage("Init... Done");
}

MainMenuState::~MainMenuState()
{
	esLogMessage(__FUNCTION__);
	delete start;
	delete batch;
}

bool MainMenuState::update(ESContext* ctx, float deltaTime)
{
	// Clear sprite before add new dynamic sprites.
	batch->clear();

	// Add sprite. Rotate it according to total time.
	batch->addSprite(startTexture, start, vec2(0, 0), 0, vec2(800));
	return true;
}

void MainMenuState::draw(ESContext* ctx)
{
	// Draw batched objects to screen.
	batch->render();
}