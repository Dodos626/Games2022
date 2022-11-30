
#include "UnitTest1.h"
#include "../../Engine/Src/Misc/WhereAmI.h"

#define width 21
#define height 42
int UnitTest1() {
    GetPath();

	TileMap map(width, height, "UnitTests/UnitTest1Media/media/map1_Kachelebene 1.csv");
	map.PrintSelf();

	
    return 0;
}
