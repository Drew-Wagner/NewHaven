#include "Player.h"

Player::Player(Board* playingBoard)
{
	board = playingBoard;
}

void Player::placeTile(int x, int y, HarvestTile* tile, ResourcePool* pool)
{
	Node* startingNode = board->getNodeAtPosition(x, y);
	startingNode->setTile(tile);

	*pool = *tile->getResourcePool();

	bool matchMeadow = tile->hasResource(MEADOW);
	bool matchForest = tile->hasResource(FOREST);
	bool matchQuarry = tile->hasResource(QUARRY);
	bool matchWheat = tile->hasResource(WHEAT);

	board->resetNodesBeforeTraversal();
	depthFirstSearch(startingNode, pool, matchMeadow, matchForest, matchQuarry, matchWheat);
}
