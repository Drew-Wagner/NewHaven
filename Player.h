#pragma once

#include "Resources.h"
#include "GraphUtils.h"
#include "GBMap.h"

class Player {
private:
	Board* board;
public:
	Player(Board* playingBoard);
	/*
	Places a tile, and returns the Resource Pool earned.
	*/
	void placeTile(int x, int y, HarvestTile* tile, ResourcePool* pool);
};