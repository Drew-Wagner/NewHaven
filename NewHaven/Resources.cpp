#include "Resources.h"

using namespace std;

ResourcePool::ResourcePool(int meadow, int forest, int quarry, int wheat)
{
	this->meadow = meadow;
	this->forest = forest;
	this->quarry = quarry;
	this->wheat = wheat;
}

int ResourcePool::get(ResourceType type)
{
	if (type == MEADOW) {
		return this->meadow;
	}
	else if (type == FOREST) {
		return this->forest;
	}
	else if (type == QUARRY) {
		return this->quarry;
	}
	else if (type == WHEAT) {
		return this->wheat;
	}
	else {
		return 0;
	}
}

void ResourcePool::add(ResourceType type, int count) {
	if (type == MEADOW) {
		this->meadow += count;
	}
	else if (type == FOREST) {
		this->forest += count;
	}
	else if (type == QUARRY) {
		this->quarry += count;
	}
	else if (type == WHEAT) {
		this->wheat += count;
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
