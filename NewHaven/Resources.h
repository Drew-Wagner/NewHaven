#pragma once

#include <string>
#include <stdlib.h>

enum ResourceType {
	MEADOW,
	FOREST,
	QUARRY,
	WHEAT,
	EMPTY
};

class ResourcePool {
private:
	int meadow{ 0 };
	int forest{ 0 };
	int quarry{ 0 };
	int wheat{ 0 };
public:
	ResourcePool() {}
	ResourcePool(int meadow, int forest, int quarry, int wheat);

	/*
	Get the resource count for the specified ResourceType
	*/
	int get(ResourceType type);

	/*
	Add the specified amount to the resource specified by ResourceType
	*/
	void add(ResourceType type, int count);

	std::string toString();
};