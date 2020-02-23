#include "GBMap.h"
#include <iostream>

using namespace std;

Board::Board(int width, int height)
{
	this->width = width;
	this->height = height;
	this->nodes = new Node * [width * height]{ 0 };
}

Board::~Board()
{
	delete[] nodes;
	nodes = nullptr;
}

Node* Board::getNodeAtPosition(int x, int y)
{
	return nodes[getIndex(x,y)];
}

// TODO Add connections to existing nodes.
void Board::setNodeAtPosition(int x, int y, Node* node)
{
	nodes[getIndex(x, y)] = node;
	// Add connection to left tile
	if (x > 0) {
		Node* leftNode = nodes[getIndex(x - 1, y)];
		if (leftNode) {
			leftNode->addConnection(Node::RIGHT, node, false);
			node->addConnection(Node::LEFT, leftNode, false);
		}
	}
	// Add connection to bottom tile
	if (y > 0) {
		Node* topNode = nodes[getIndex(x, y - 1)];
		if (topNode) {
			topNode->addConnection(Node::BOTTOM, node, true);
			node->addConnection(Node::TOP, topNode, false);
		}
	}
}

bool Board::setTileAtPosition(int x, int y, HarvestTile* tile)
{
	Node* node = getNodeAtPosition(x, y);
	if (node) {
		node->setTile(tile);
	}
	return false;
}

void Board::resetNodesBeforeTraversal()
{
	for (int i = 0; i < width * height; i++) {
		Node* node = nodes[i];
		if (node) {
			node->unsetVisited();
		}
	}
}

std::string Board::toString()
{
	string str = "Board(";
	for (int y = 0; y < height * 2; y++) {
		if (y % 2 == 0) {
			str += "\n";
		}
		str += "\t";
		for (int x = 0; x < width * 2; x++) {
			Node* node = getNodeAtPosition(x / 2, y / 2);
			if (node) {
				HarvestTile* tile = node->getTile();
				if (!tile) {
					if (x % 2 == 0) {
						str += ".";
					}
					else {
						str += ". ";
					}
					continue;
				}
				if (y % 2 == 0) {
					if (x % 2 == 0) {
						ResourceType type = tile->getTopLeft();
						str += ResourceTypeToChar(type);
					}
					else {
						ResourceType type = tile->getTopRight();
						str += ResourceTypeToChar(type);
						str += " ";
					}
				}
				else {
					if (x % 2 == 0) {
						ResourceType type = tile->getBottomLeft();
						str += ResourceTypeToChar(type);
					}
					else {
						ResourceType type = tile->getBottomRight();
						str += ResourceTypeToChar(type);
						str += " ";
					}
				}
			}
			else {
				if (x % 2 == 0) {
					str += " ";
				}
				else {
					str += "  ";
				}
			}
		}
		str += "\n";
	}
	str += ")";
	return str;
}

HarvestTile::HarvestTile(ResourceType topLeft, ResourceType topRight, ResourceType bottomRight, ResourceType bottomLeft)
{
	configuration = new ResourceType[4]{
		topLeft, topRight, bottomRight, bottomLeft
	};
	resourcePool = new ResourcePool();
	for (int i = 0; i < 4; i++) {
		resourcePool->add(configuration[i], 1);
	}
}

HarvestTile::~HarvestTile()
{
	delete resourcePool;
	delete[] configuration;
	resourcePool = nullptr;
	configuration = nullptr;
}

void HarvestTile::rotateRight()
{
	ResourceType* newConfig = new ResourceType[4]{ NONE };
	for (int i = 0; i < 4; i++) {
		newConfig[i] = configuration[(4 + ((i-1) % 4)) % 4];
	}
	delete[] configuration;
	configuration = newConfig;
}

void HarvestTile::rotateLeft()
{
	ResourceType* newConfig = new ResourceType[4]{ NONE };
	for (int i = 0; i < 4; i++) {
		newConfig[i] = configuration[(4 + ((i + 1) % 4)) % 4];
	}
	delete[] configuration;
	configuration = newConfig;
}

ResourcePool* HarvestTile::getResourcePool()
{
	return resourcePool;
}

bool HarvestTile::hasResource(ResourceType type)
{
	return configuration[0] == type || configuration[1] == type || configuration[2] == type || configuration[3] == type;
}

string HarvestTile::toString()
{
	string str = "HarvestTile(\n";
	str += ResourceTypeToChar(configuration[0]);
	str += ResourceTypeToChar(configuration[1]);
	str += '\n';
	str += ResourceTypeToChar(configuration[3]);
	str += ResourceTypeToChar(configuration[2]);
	str += '\n)';
	return str;
}

Connection::Connection(Node* first, Node* second, bool isVertical)
{
	firstNode = first;
	secondNode = second;
	this->isVertical = isVertical;
}

Node* Connection::getConnectedNode()
{
	return secondNode;
}

ResourceType* Connection::matches()
{
	// Create pointers to store result
	ResourceType* result = new ResourceType[2]{ NONE };
	
	/*
	If the connection is vertical, compare bottom left resource of firstNode to top left resource of secondNode,
	and compare bottom right resource of firstNode to top right resource of secondNode.
	*/
	if (isVertical)
	{
		HarvestTile* topTile = firstNode->getTile();
		HarvestTile* bottomTile = secondNode->getTile();
		if (topTile->getBottomLeft() == bottomTile->getTopLeft()) {
			result[0] = topTile->getBottomLeft();
		}
		if (topTile->getBottomRight() == bottomTile->getTopRight()) {
			result[1] = topTile->getBottomRight();
		}
	}
	/*
	Otherwise if the connection is horizontal, compare top right resource of firstNode to top left resource of secondNode,
	and compare bottom right resource of firstNode to bottom left resource of secondNode.
	*/
	else {
		HarvestTile* leftTile = firstNode->getTile();
		HarvestTile* rightTile = secondNode->getTile();
		if (leftTile->getTopRight() == rightTile->getTopLeft()) {
			result[0] = leftTile->getTopRight();
		}
		if (leftTile->getBottomRight() == rightTile->getBottomLeft()) {
			result[1] = leftTile->getBottomRight();
		}
	}

	return result;
}

Node::Node()
{
	tile = NULL;
	neighbours = new Connection*[4];
}

Node::~Node()
{
	delete[] neighbours;
}

bool Node::isEmpty()
{
	return tile == nullptr;
}

HarvestTile* Node::getTile()
{
	return tile;
}

void Node::setTile(HarvestTile* tile)
{
	this->tile = tile;
}

Connection* Node::addConnection(int position, Node* other, bool isVertical)
{
	Connection* connection = new Connection(this, other, isVertical);
	neighbours[position] = connection;
	return connection;
}

Connection* Node::getConnection(int position)
{
	return neighbours[position];
}
