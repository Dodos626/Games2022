
#include "UnitTest1.h"
#include "../../Engine/Src/Misc/WhereAmI.h"

#define width 21
#define height 42
int UnitTest1() {
    GetPath();

	try {
		BitMap bitMap("UnitTests/UnitTest1Media/media/overworld_tileset_grass.png", 12,
			21);

	}
	catch (std::string e) {
		std::cout << e << std::endl;
		std::cout << "UnitTest1 has failed\n";
		return -1;
	}

	TileMap map(width, height, "UnitTests/UnitTest1Media/media/map1_Kachelebene 1.csv");
	map.PrintSelf();

	
    return 0;
}
