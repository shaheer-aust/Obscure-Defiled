#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef level_handler_H
#define level_handler_H
#define TOTAL_PICS 4
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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

struct ScoreStorageEntry
{
    string playerName;
    int kills;
    int totalScore;
};

void upsertScoreEntry(const playerInfo &info)
{
    vector<ScoreStorageEntry> entries;
    ifstream inputFile("score.txt");

    if (inputFile.is_open())
    {
        ScoreStorageEntry entry;
        while (inputFile >> entry.playerName >> entry.kills >> entry.totalScore)
        {
            entries.push_back(entry);
        }
        inputFile.close();
    }

    bool found = false;
    string normalizedName = trimLower(info.playerName);
    for (ScoreStorageEntry &entry : entries)
    {
        if (trimLower(entry.playerName) == normalizedName)
        {
            entry.kills = info.kills;
            entry.totalScore = info.totalScore;
            found = true;
            break;
        }
    }

    if (!found)
    {
        ScoreStorageEntry newEntry;
        newEntry.playerName = info.playerName;
        newEntry.kills = info.kills;
        newEntry.totalScore = info.totalScore;
        entries.push_back(newEntry);
    }

    sort(entries.begin(), entries.end(), [](const ScoreStorageEntry &a, const ScoreStorageEntry &b)
    {
        if (a.totalScore != b.totalScore)
        {
            return a.totalScore > b.totalScore;
        }
        if (a.kills != b.kills)
        {
            return a.kills > b.kills;
        }
        return trimLower(a.playerName) < trimLower(b.playerName);
    });

    vector<ScoreStorageEntry> uniqueEntries;
    vector<string> seenNames;
    for (const ScoreStorageEntry &entry : entries)
    {
        string normalizedEntryName = trimLower(entry.playerName);
        bool alreadySeen = false;
        for (const string &seen : seenNames)
        {
            if (seen == normalizedEntryName)
            {
                alreadySeen = true;
                break;
            }
        }

        if (!alreadySeen)
        {
            seenNames.push_back(normalizedEntryName);
            uniqueEntries.push_back(entry);
        }
    }
    entries = uniqueEntries;

    ofstream outputFile("score.txt", ios::trunc);
    if (!outputFile.is_open())
    {
        return;
    }

    for (size_t i = 0; i < entries.size(); ++i)
    {
        outputFile << entries[i].playerName << " " << entries[i].kills << " " << entries[i].totalScore << "\n";
    }
    outputFile.close();
}

void savePlayerWinDetails(const playerInfo &info)
{
    if (shouldSkipPlayerStorage(info.playerName))
    {
        return;
    }
    savePlayerProfile(info);
    upsertScoreEntry(info);
}
#endif