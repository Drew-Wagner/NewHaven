// NewHaven.cpp : Defines the entry point for the application.
//

#include "NewHaven.h"

using namespace std;

int main()
{
	HarvestTile tile = HarvestTile(new ResourceType[4]{ MEADOW, MEADOW, QUARRY, WHEAT });
	ResourcePool pool = *(tile.getResourcePool());
	cout << pool.toString() << endl;
	return 0;
}
