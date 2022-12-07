#include "CS454.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

//https://github.com/nlohmann/json#read-json-from-a-file
//gia to manual tu json
int main()
{
		std::ifstream f("Engine/Configs/MainConfig.json");
		json data = json::parse(f);
		
	
	
	
	
	app::App* app = new app::App();
	return 0;

	
}

