#include "MainMenuState.h"
#include "Layer.h"

MainMenuState::MainMenuState(GameApp* app) : GameState(app)
{
	esLogMessage(__FUNCTION__);
	int cc = 0;

	esLogMessage("Init... %d", cc++);
	// Create new sprite batch group. This must be deleted at deinit.
	batch = new SpriteBatchGroup();

	esLogMessage("Init... %d", cc++);
	// Load texture to be used as texture for sprite.
	backgroundTexture = new Texture("splash.png");

	esLogMessage("Init... %d", cc++);
	// Create new sprite, with default parameters.
	backgroundSprite = new Sprite(0);

	//esLogMessage("Init... %d", cc++);
	//// Load texture to be used as texture for sprite.
	//startTexture = new Texture("start.png");

	//esLogMessage("Init... %d", cc++);
	//// Create new sprite, with default parameters.
	//startSprite = new Sprite(0);

	//m_map = new Map(1280, 768);

	//Layer* backgroundLayer = new Layer(m_map, "Background", 1.0f, true, false);
	//m_map->addLayer(Map::BACKGROUND0, backgroundLayer);

	esLogMessage("Init... Done");
}

MainMenuState::~MainMenuState()
{
}

bool MainMenuState::update(ESContext* ctx, float deltaTime)
{
	// Clear sprite before add new dynamic sprites.
	batch->clear();

	// Add sprite. Rotate it according to total time.
	batch->addSprite(backgroundTexture, backgroundSprite, vec2(0, 0), 0, vec2(800));
	return true;
}

void MainMenuState::draw(ESContext* ctx)
{
	// Draw batched objects to screen.
	batch->render();
}