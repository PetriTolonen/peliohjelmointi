#include "SplashScreenState.h"
#include <iostream>

bool SplashScreenState::update(ESContext* ctx, float deltaTime)
{
	return true;
}

void SplashScreenState::draw(ESContext* ctx)
{
	std::cout << "testing splash" << std::endl;
}