#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef level_handler_H
#define level_handler_H
#define TOTAL_PICS 4
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
using namespace std;
map<string,pair<int,int>> playerInfoMap; // Map to store player info with player name as key
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

            info.totalScore = stoi(line);
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



bool shouldSkipPlayerStorage(const string &playerName)
{
    
    return playerName=="unknown player"? true : false;
}


void appendScoreEntry(const playerInfoMap &info)
{
    FILE *file_read = fopen("scores.txt", "rb");
    map<string, pair<int, int>> existingEntries;
    if (file_read)    {
        fread(&existingEntries, sizeof(existingEntries), 1, file_read);
        fclose(file_read);
    }
    existingEntries[info.first] = make_pair(info.second.first, info.second.second);
    FILE *file = fopen("scores.txt", "wb");
    if (!file)
    {
        return;
    }
    fwrite(&existingEntries, sizeof(existingEntries), 1, file);
    
    fclose(file);
}

void savePlayerWinDetails(const playerInfo &info)
{
    if (shouldSkipPlayerStorage(info.playerName))
    {
        return;
    }
    savePlayerProfile(info);
    playerInfoMap[info.playerName] = make_pair(info.kills, info.totalScore);
    appendScoreEntry(playerInfoMap);
}
#endif