#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef level_handler_H
#define level_handler_H
#define TOTAL_PICS 4
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
struct playerInfo {
	string playerName;
    int kills;
    int totalScore;
    int levelReached;
};
void initPlayerProfile(playerInfo& info){
    ifstream file("player.txt");
	if (file.is_open()){
		cout << "open file"<< endl;
	}
    if (file.is_open()) {
        file >> info.playerName >> info.levelReached >> info.kills >> info.totalScore;
        file.close();
    }
}
void savePlayerProfile(const playerInfo& info) {
    ofstream file("player.txt");
    if (file.is_open()) {
        file << info.playerName << " " << info.levelReached << " " << info.kills << " " << info.totalScore;
        file.close();
    }
}
#endif