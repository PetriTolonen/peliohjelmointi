#pragma once
#include <Object.h>
#include <es_util.h>
#include <Sprite.h>
#include <SpriteBatch.h>
#include <SpriteSheet.h>
#include <Text.h>
#include <Texture.h>

class GameApp;

using namespace yam2d;

class GameState : public Object
{
public:
	virtual ~GameState(){}
	virtual bool update(ESContext* ctx, float deltaTime){ return true; }
	virtual void draw(ESContext *ctx){}
	
protected:
	GameState(){}
	GameApp* getApp(){ return m_gameApp; }
private:
	GameApp* m_gameApp;
};