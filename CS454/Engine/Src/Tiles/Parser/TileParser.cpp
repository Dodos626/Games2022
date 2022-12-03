#include "TileParser.h"


// THIS WAY IS KINDA SLOW , BETTER TO USE C STYLE READING
// TOO BORED TO MAKE IT ATM

using namespace std;


vector<int> stringSplitToInt(string s, char del);

std::vector<std::vector<int>> ReadTextMap(std::string filename, int width, int height){

    fstream file;
    file.open(filename, ios::in);

	if (!file.is_open()) {
		throw "File "+filename+" not found";
	}

    vector<vector<int>> tileMap;

    string temp;

    while (file >> temp) {
		tileMap.push_back(stringSplitToInt(temp, ','));
    }
    file.close();
    return tileMap;
}

// splits a string into a vector of ints
vector<int> stringSplitToInt(string s, char del)
{
    vector<int> tokens;
    stringstream ss(s);
    string word;
    while (!ss.eof()) {
        getline(ss, word, del);
        tokens.push_back(stoi(word));
    }
    return tokens;
}

// prints a 2d vector
void PrintTileMap(std::vector<std::vector<int>> tileMap, int width, int height) {
	{
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				cout << tileMap[i][j]<< " ";
			}
			cout << endl;
		}
	}
}