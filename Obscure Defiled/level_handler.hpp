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
        string line;
        // expected format:
        // Player Name,
        // level: 1,
        // Kills: 3,
        // Score: 500
        if (getline(file, line)) {
            // remove trailing comma
            if (!line.empty() && line.back() == ',') line.pop_back();
            info.playerName = line;
        }
        if (getline(file, line)) {
			string to_remove = "level: ";
			line.erase(0, to_remove.length());
			line.pop_back();
           
			info.levelReached = stoi(line);
            
        }
        if (getline(file, line)) {
			string to_remove = "Kills: ";
			line.erase(0, to_remove.length());
			line.pop_back();

			info.kills = stoi(line);
        }
        if (getline(file, line)) {
			string to_remove = "Score: ";
			line.erase(0, to_remove.length());
			//line.pop_back();

			info.kills = stoi(line);
        }
        file.close();
    }
}
void savePlayerProfile(const playerInfo& info) {
    ofstream file("player.txt");
    if (file.is_open()) {
        file << info.playerName << ",\n"
             << "level: " << info.levelReached << ",\n"
             << "Kills: " << info.kills << ",\n"
             << "Score: " << info.totalScore;
        file.close();
    }
}
#endif