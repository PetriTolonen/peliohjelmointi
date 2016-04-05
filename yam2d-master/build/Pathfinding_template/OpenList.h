#pragma once
#include "SearchNode.h"

class OpenList
{
public:
	OpenList(){}
	~OpenList(){}

	SearchNode* findFromOpenList(const Position& pos);
	void insertToOpenList(SearchNode* n);
	void sortOpenList();
	SearchNode* removeSmallestFFromOpenList();

	bool isEmpty();
	void clear();
private:

};