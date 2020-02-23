#include "GraphUtils.h"

void depthFirstSearch(Node* node, ResourcePool* pool, bool matchMeadow, bool matchForest, bool matchQuarry, bool matchWheat)
{
	// Mark the node as visited.
	node->setVisited();
	for (int i = 0; i < 4; i++) {
		Connection* connection = node->getConnection(i);
		if (connection) {
			Node* nextNode = connection->getConnectedNode();
			if (nextNode->wasVisited()) continue;

			HarvestTile* nextTile = nextNode->getTile();
			if (!nextTile) continue;

			ResourcePool nextPool = *nextTile->getResourcePool();

			ResourceType* matches = connection->matches();
			bool gotoNext = false;

			// Check if there is a match for each desired resource type
			if (matchMeadow && (matches[0] == MEADOW || matches[1] == MEADOW)) {
				pool->add(MEADOW, nextPool.get(MEADOW));
				gotoNext = true;
			}
			else {
				matchMeadow = false;
			}

			if (matchForest && (matches[0] == FOREST || matches[1] == FOREST)) {
				pool->add(FOREST, nextPool.get(FOREST));
				gotoNext = true;
			}
			else {
				matchForest = false;
			}

			if (matchQuarry && (matches[0] == QUARRY || matches[1] == QUARRY)) {
				pool->add(QUARRY, nextPool.get(QUARRY));
				gotoNext = true;
			}
			else {
				matchQuarry = false;
			}

			if (matchWheat && (matches[0] == WHEAT || matches[1] == WHEAT)) {
				pool->add(WHEAT, nextPool.get(WHEAT));
				gotoNext = true;
			}
			else {
				matchWheat = false;
			}
			// If a match was found go to next node, and continue the search
			if (gotoNext) {
				depthFirstSearch(nextNode, pool, matchMeadow, matchForest, matchQuarry, matchWheat);
			}
		}
	}
}