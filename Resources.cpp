#include "Resources.h"

using namespace std;

ResourcePool::ResourcePool(int meadow, int forest, int quarry, int wheat)
{
	this->meadow = meadow;
	this->forest = forest;
	this->quarry = quarry;
	this->wheat = wheat;
}

ResourcePool ResourcePool::operator+(ResourcePool const& obj)
{
	return ResourcePool(
		meadow + obj.meadow,
		forest + obj.forest,
		quarry + obj.quarry,
		wheat + obj.wheat
		);
}

int ResourcePool::get(ResourceType type)
{
	if (type == MEADOW) {
		return meadow;
	}
	else if (type == FOREST) {
		return forest;
	}
	else if (type == QUARRY) {
		return quarry;
	}
	else if (type == WHEAT) {
		return wheat;
	}
	return 0;
}

void ResourcePool::add(ResourceType type, int value)
{
	if (type == MEADOW) {
		meadow += value;
	}
	else if (type == FOREST) {
		forest += value;
	}
	else if (type == QUARRY) {
		quarry += value;
	}
	else if (type == WHEAT) {
		wheat += value;
	}
}

void ResourcePool::set(ResourceType type, int value)
{
	if (type == MEADOW) {
		meadow = value;
	}
	else if (type == FOREST) {
		forest = value;
	}
	else if (type == QUARRY) {
		quarry = value;
	}
	else if (type == WHEAT) {
		wheat = value;
	}
}

string ResourcePool::toString()
{
	return "ResourcePool(meadow: "
		+ to_string(meadow)
		+ ", forest: "
		+ to_string(forest)
		+ ", quarry: "
		+ to_string(quarry)
		+ ", wheat: "
		+ to_string(wheat)
		+ ")";
}

char ResourceTypeToChar(ResourceType type)
{
	switch (type) {
	case NONE:
		return '.';
	case MEADOW:
		return 'M';
	case FOREST:
		return 'F';
	case QUARRY:
		return 'Q';
	case WHEAT:
		return 'W';
	}
}