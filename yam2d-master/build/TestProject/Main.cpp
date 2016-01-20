// Include OpenGL ES Engine utils
#include <es_util.h>
#include "GameApp.h"

using namespace yam2d;

namespace
{
	GameApp* game;
}

// Initialize the game
bool init(ESContext *esContext)
{
	GameApp* game = new GameApp();
	return true;
}

// Deinitialize the game
void deinit(ESContext *esContext)
{

}

int main(int argc, char *argv[])
{
	ESContext esContext;
	esInitContext(&esContext);
	esCreateWindow(&esContext, "Simple map example", 1280, 720, ES_WINDOW_DEFAULT);

	esRegisterInitFunc(&esContext, init);
	esRegisterDrawFunc(&esContext, game->draw);
	esRegisterUpdateFunc(&esContext, game->update);
	esRegisterDeinitFunc(&esContext, deinit);

	esMainLoop(&esContext);
	return 0;
}
