#pragma once

#include "SearchNode.h"
#include <vector>

class SearhLevel
{
public:
	SearhLevel();
	~SearhLevel();

	float GetG(SearchNode* fromPos, SearchNode* toPos);
	float GetH(SearchNode* fromPos, SearchNode* toPos);

private:
	bool isWalkable(int x, int y);
	
};