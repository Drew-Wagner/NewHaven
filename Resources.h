#pragma once

#include <string>

enum ResourceType {
	NONE = 0,
	MEADOW,
	FOREST,
	QUARRY,
	WHEAT
};

/*
Converts a ResourceType to a char.
*/
char ResourceTypeToChar(ResourceType type);

/*
Stores counts for each of the four resources.
*/
class ResourcePool {
private:
	int meadow{ 0 };
	int forest{ 0 };
	int quarry{ 0 };
	int wheat{ 0 };
public:
	ResourcePool() {}
	ResourcePool(int meadow, int forest, int quarry, int wheat);

	// Combine two resource pools
	ResourcePool operator + (ResourcePool const& obj);

	// Get the the number of the specified resource.
	int get(ResourceType type);

	// Add value to the specified resource.
	void add(ResourceType type, int value);

	// Set the value for the specified resource.
	void set(ResourceType type, int value);
	
	std::string toString();
};