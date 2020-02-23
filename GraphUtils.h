#pragma once

#include "Resources.h"
#include "GBMap.h"

/*
Recursively performs a depth-first search through the board in
order to count the connected resources or the desired types.
*/
void depthFirstSearch(Node* node, ResourcePool* pool, bool matchMeadow, bool matchForest, bool matchQuarry, bool matchWheat);