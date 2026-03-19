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

string trimLower(string text)
{
    int left = 0;
    int right = (int)text.size() - 1;
    while (left <= right && isspace((unsigned char)text[left])) left++;
    while (right >= left && isspace((unsigned char)text[right])) right--;

    string cleaned = (left <= right) ? text.substr(left, right - left + 1) : "";
    for (char &ch : cleaned)
    {
        ch = (char)tolower((unsigned char)ch);
    }
    return cleaned;
}

bool shouldSkipPlayerStorage(const string &playerName)
{
    string normalized = trimLower(playerName);
    return normalized.empty() || normalized == "unknown player";
}

int nextScoreRank()
{
    ifstream file("score.txt");
    if (!file.is_open())
    {
        return 1;
    }

    int rank = 0;
    int kills = 0;
    int totalScore = 0;
    int maxRank = 0;
    string playerName;

    while (file >> rank >> playerName >> kills >> totalScore)
    {
        if (rank > maxRank)
        {
            maxRank = rank;
        }
    }
    file.close();
    return maxRank + 1;
}

void appendScoreEntry(const playerInfo &info)
{
    ofstream file("score.txt", ios::app);
    if (!file.is_open())
    {
        return;
    }

    int rank = nextScoreRank();

	file << rank << " " << info.playerName << " " << info.kills << " " << info.totalScore << "\n";
    file.close();
}

void savePlayerWinDetails(const playerInfo &info)
{
    if (shouldSkipPlayerStorage(info.playerName))
    {
        return;
    }
    savePlayerProfile(info);
    appendScoreEntry(info);
}
#endif