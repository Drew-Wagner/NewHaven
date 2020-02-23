#pragma once
#include "Resources.h"

class HarvestTile;
class Node;
class Connection;
class Board;

/*
Represents a harvest tile, which can either exist in the player's inventory,
or be placed on a Node.
*/
class HarvestTile {
private:
	/*
	Stores the tile configuration as an array:
		0 -> Top left
		1 -> Top right
		2 -> Bottom right
		3 -> Bottom left
	This allows for easy tile rotations.
	*/
	ResourceType* configuration;
	/*
	Allows one to query the number of resources on this tile, by ResourceType.
	*/
	ResourcePool* resourcePool;
public:
	HarvestTile(ResourceType* configuration);
	~HarvestTile();

	// Rotates the tile 90 degrees to the right
	void rotateRight();
	// Rotates the tile 90 degrees to the left.
	void rotateLeft();

	ResourcePool* getResourcePool();
};

/*
Represents a square on the board as a node in a connected graph. A node can store
a HarvestTile, or be empty.
*/
class Node {
private:
	/*
	Pointer to the 4 possible connections of the node:
		0 -> Top
		1 -> Right
		2 -> Bottom
		3 -> Left
	*/
	Connection* connections;

	HarvestTile* tile;
public:
	Node();
	bool isEmpty();
	HarvestTile* getTile();
	void setTile(HarvestTile* tile);
};

class Connection {
private:
	/*
	Indicates the orientation of the connection.
	*/
	bool isVertical;

	/*
	The node on the left, or the top if the connection is vertical.
	*/
	Node* firstNode;

	/*
	The node on the right, or the bottom if the connection is vertical.
	*/
	Node* secondNode;
public:
	ResourceType* matches();
};

class Board {
private:
	/*
	Stores pointers to nodes in order to be able to place access nodes by position.
	*/
	Node* nodes;
	int width;
	int height;

	int getIndex(int x, int y);
public:
	Node* getNodeAtPosition(int x, int y);
	Node* setNodeAtPosition(int x, int y, Node node);
};