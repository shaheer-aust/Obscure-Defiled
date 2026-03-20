#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef level_handler_H
#define level_handler_H
#define TOTAL_PICS 4
#include <iostream>
#include <cstdio>
#include <cstdlib>
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
    FILE *file = fopen("player.txt", "r");
    if (!file){
        return;
    }

    char buffer[512];
    string line;

    if (fgets(buffer, sizeof(buffer), file)) {
        line = buffer;
        while (!line.empty() && (line.back() == '\n' || line.back() == '\r')) line.pop_back();
        if (!line.empty() && line.back() == ',') line.pop_back();
        info.playerName = line;
    }
    if (fgets(buffer, sizeof(buffer), file)) {
		line = buffer;
        while (!line.empty() && (line.back() == '\n' || line.back() == '\r')) line.pop_back();
		string to_remove = "level: ";
        if (line.rfind(to_remove, 0) == 0) {
			line.erase(0, to_remove.length());
        }
        if (!line.empty() && line.back() == ',') line.pop_back();
		info.levelReached = atoi(line.c_str());
    }
    if (fgets(buffer, sizeof(buffer), file)) {
		line = buffer;
        while (!line.empty() && (line.back() == '\n' || line.back() == '\r')) line.pop_back();
		string to_remove = "Kills: ";
        if (line.rfind(to_remove, 0) == 0) {
			line.erase(0, to_remove.length());
        }
        if (!line.empty() && line.back() == ',') line.pop_back();
		info.kills = atoi(line.c_str());
    }
    if (fgets(buffer, sizeof(buffer), file)) {
		line = buffer;
        while (!line.empty() && (line.back() == '\n' || line.back() == '\r')) line.pop_back();
		string to_remove = "Score: ";
        if (line.rfind(to_remove, 0) == 0) {
			line.erase(0, to_remove.length());
        }
        info.totalScore = atoi(line.c_str());
    }
    fclose(file);
}
void savePlayerProfile(const playerInfo& info) {
    FILE *file = fopen("player.txt", "w");
    if (!file) {
        return;
    }

    fprintf(file, "%s,\n", info.playerName.c_str());
    fprintf(file, "level: %d,\n", info.levelReached);
    fprintf(file, "Kills: %d,\n", info.kills);
    fprintf(file, "Score: %d", info.totalScore);
    fclose(file);
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
    int rank;
    string playerName;
    int kills;
    int totalScore;
};

void upsertScoreEntry(const playerInfo &info)
{
    vector<ScoreStorageEntry> entries;
    FILE *inputFile = fopen("score.txt", "r");

    if (inputFile)
    {
        ScoreStorageEntry entry;
        char playerNameBuffer[256];
        while (fscanf(inputFile, "%d %255s %d %d", &entry.rank, playerNameBuffer, &entry.kills, &entry.totalScore) == 4)
        {
            entry.playerName = playerNameBuffer;
            entries.push_back(entry);
        }
        fclose(inputFile);
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
        newEntry.rank = 0;
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

    FILE *outputFile = fopen("score.txt", "w");
    if (!outputFile)
    {
        return;
    }

    for (size_t i = 0; i < entries.size(); ++i)
    {
        fprintf(outputFile, "%d %s %d %d\n", (int)(i + 1), entries[i].playerName.c_str(), entries[i].kills, entries[i].totalScore);
    }
    fclose(outputFile);
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