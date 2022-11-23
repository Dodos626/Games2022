#include "TileParser.h"


// THIS WAY IS KINDA SLOW , BETTER TO USE C STYLE READING
// TOO BORED TO MAKE IT ATM

using namespace std;


vector<int> stringSplitToInt(string s, char del);

int TileParseFile(string filename) {
    fstream file;
    file.open(filename, ios::in);

    vector<vector<int>> tileMap;

    string temp;
    
    while(file >> temp){
        tileMap.push_back(stringSplitToInt(temp, ','));
    }
    
	file.close();

    PrintTileMap(tileMap);

    return 0;
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
void PrintTileMap(vector<vector<int>> tileMap){
    for(int i = 0; i < tileMap.size(); i++){
        for(int j = 0; j < tileMap[i].size(); j++){
            cout << tileMap[i][j] << " ";
        }
        cout << endl;
    }
}