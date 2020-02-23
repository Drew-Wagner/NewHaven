#pragma once

#include <string>
#include "Resources.h"

class Node;
class Connection;
class HarvestTile;
class Board;
	
class Node {
private:
	/*
	Stores the 4 possible connections to adjacent nodes:
		0 -> top
		1 -> right
		2 -> bottom
		3 -> left
	*/
	Connection** neighbours;

	// Pointer to the HarvestTile placed on this node.
	HarvestTile* tile;

	bool visited;

public:
	enum Position {
		TOP = 0,
		RIGHT,
		BOTTOM,
		LEFT
	}; 
	Node();
	~Node();

	bool isEmpty();
	HarvestTile* getTile();
	void setTile(HarvestTile* tile);
	Connection* addConnection(int position, Node* other, bool isVertical);
	Connection* getConnection(int position);

	// Has the Node already been visited in this traversal
	bool wasVisited() { return visited; }

	// Marks the Node as visited.
	void setVisited() { visited = true; }

	// Resets the Node
	void unsetVisited() { visited = false; }
};

/*
Represents the edge between two adjacent nodes. Contains functions for
checking if the nodes resources line up.
*/
class Connection {
private:
	// Specifies the connections orientation, horizontal or vertical.
	bool isVertical;

	/*
	The left-most node if the connection is horizontal, or the top-most
	if the connection is vertical.
	*/
	Node* firstNode;

	/*
	The right-most node if the connection is horizontal, or the bottom-most
	if the connection is vertical.
	*/
	Node* secondNode;

public:
	// Creates a new connection, between left node (or top) and right node (or bottom), and specifies orientation.
	Connection() {}
	Connection(Node* first, Node* second, bool isVertical);

	// Returns the node on the other side of the connection.
	Node* getConnectedNode();

	ResourceType* matches();
};

/*
Represents a harvest tile, which can exist either on the board, within a node,
or in the player's inventory.
*/
class HarvestTile {
private:
	/*
	Specifies the resources of the harvest tile:
		0 -> top-left
		1 -> top-right
		2 -> bottom-right
		3 -> bottom-left
	This representation allows for easy rotations of the configuration.
	*/
	ResourceType* configuration;
	
	// Counts the number of each resource on the tile.
	ResourcePool* resourcePool;
public:
	HarvestTile(ResourceType topLeft, ResourceType topRight, ResourceType bottomRight, ResourceType bottomLeft);
	~HarvestTile();

	// Rotates the tile 90 degrees to the right.
	void rotateRight();

	// Rotates the tile 90 degrees to the left.
	void rotateLeft();

	// Returns type of top left resource.
	ResourceType getTopLeft() { return configuration[0]; }
	// Returns type of top right resource.

	ResourceType getTopRight() { return configuration[1]; }
	// Returns type of bottom right resource.

	ResourceType getBottomRight() { return configuration[2]; }
	// Returns type of bottom left resource.

	ResourceType getBottomLeft() { return configuration[3]; }

	// Gets a pointer to the resource pool associated with this harvest tile.
	ResourcePool* getResourcePool();

	bool hasResource(ResourceType type);

	std::string toString();
};

class Board {
private:
	// Represents the maximum number of tiles horizontally (Used to calculate the index to a node)
	int width;
	// Represents the maximum number of tiles vertically (Used to calculate the index to a node)
	int height;

	// Stores pointers to each Node making up the board. Used to get the node at a given position.
	Node** nodes;


public:
	Board(int width, int height);
	~Board();

	// Gets the index based on x and y coordinates.
	int getIndex(int x, int y) {
		return y * width + x;
	}

	// Returns a pointer to the node at the specified position.
	Node* getNodeAtPosition(int x, int y);

	// Sets the node at the specified position.
	void setNodeAtPosition(int x, int y, Node* node);

	bool setTileAtPosition(int x, int y, HarvestTile* tile);

	void resetNodesBeforeTraversal();

	std::string toString();
};
