#pragma once

#include <Object.h>

#include <Ref.h>

#include <Input.h>
#include <Layer.h>
#include <Map.h>
#include <Camera.h>

#include <es_util.h>
#include <Sprite.h>
#include <SpriteBatch.h>
#include <SpriteSheet.h>
#include <SpriteComponent.h>
#include <Text.h>
#include <Texture.h>

class GameApp;

using namespace yam2d;

class GameState : public Object
{
public:
	virtual bool update(ESContext* ctx, float deltaTime){ return true; }
	virtual void draw(ESContext *ctx){}
	virtual ~GameState(){}
	
protected:
	GameState(GameApp* app): m_gameApp(app){}	
	GameApp* getApp(){ return m_gameApp; }
private:
	GameApp* m_gameApp;
};