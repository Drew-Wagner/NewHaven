#include "NewHaven.h"

using namespace std;

int main() {
	ResourcePool pool;
	Board board = Board(7, 7);
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (!(i == 0 || i == 6) || !(j == 0 || j == 6)) {
				board.setNodeAtPosition(i, j, new Node());
			}
		}
	}
	cout << board.toString() << endl;
	
	HarvestTile tile1 = HarvestTile(MEADOW, MEADOW, MEADOW, FOREST);
	HarvestTile tile2 = HarvestTile(MEADOW, MEADOW, QUARRY, QUARRY);

	Player player = Player(&board);
	player.placeTile(2, 2, &tile1, &pool);
	
	system("CLS");
	cout << board.toString() << endl;
	cout << pool.toString() << endl;
	
	player.placeTile(3, 2, &tile2, &pool);
	system("CLS");
	cout << board.toString() << endl;
	cout << pool.toString() << endl;
	return 0;
}
