#include "GBMap.h"

HarvestTile::HarvestTile(ResourceType* configuration)
{
	this->configuration = configuration;
	this->resourcePool = new ResourcePool();
	for (int i = 0; i < 4; i++) {
		resourcePool->add(configuration[i], 1);
	}
}

HarvestTile::~HarvestTile()
{
	delete configuration;
	delete resourcePool;
	configuration = nullptr;
	resourcePool = nullptr;
}

ResourcePool* HarvestTile::getResourcePool()
{
	return resourcePool;
}
