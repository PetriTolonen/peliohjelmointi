// Include OpenGL ES Engine utils
#include <es_util.h>
#include "GameApp.h"
#include "SplashScreenState.h"
#include "MainMenuState.h"

using namespace yam2d;

namespace
{
	GameApp* game;
}

// Initialize the game
bool init(ESContext *esContext)
{
	game = new GameApp();
	SplashScreenState* splash = new SplashScreenState(game);
	game->setState(splash);
	return true;
}

// Deinitialize the game
void deinit(ESContext *esContext)
{
	delete game;
}

// Update game
void update(ESContext* ctx, float deltaTime)
{
	game->update(ctx, deltaTime);

	if (false)
	{
		esQuitApp(ctx);
	}
}


// Draw game
void draw(ESContext *esContext)
{
	game->draw(esContext);
}

int main(int argc, char *argv[])
{
	ESContext esContext;
	esInitContext(&esContext);
	esCreateWindow(&esContext, "Simple map example", 1280, 720, ES_WINDOW_DEFAULT);

	esRegisterInitFunc(&esContext, init);
	esRegisterDrawFunc(&esContext, draw);
	esRegisterUpdateFunc(&esContext, update);
	esRegisterDeinitFunc(&esContext, deinit);

	esMainLoop(&esContext);
	return 0;
}
