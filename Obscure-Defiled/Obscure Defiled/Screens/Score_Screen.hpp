#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef SCORE_SCREEN_HPP
#define SCORE_SCREEN_HPP

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
struct ScoreEntry {
    int rank;
    string playerName;
    int kills;
    int totalScore;
};

class ScoreScreen {

public:
    ScoreScreen() {
        init_score_screen();
        load_scores_from_file();
    }
    vector<ScoreEntry> scoreData;
    vector<int> BgImages;
    
    // Initialize score screen with background and title images
    void init_score_screen() {
        BgImages.push_back(iLoadImage("resources/scoreboard/scorebg.png"));
        BgImages.push_back(iLoadImage("resources/menu_screen/title.png"));
    }

    // Load scores from score.txt file
    void load_scores_from_file() {
        ifstream file("score.txt");
        scoreData.clear();

        if (!file.is_open()) {
            return;
        }

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            ScoreEntry entry;

            // Parse: rank,playerName,kills,totalScore
            if (getline(iss, line, ',')) {
                entry.rank = stoi(line);
            }
            if (getline(iss, entry.playerName, ',')) {
                // Trim whitespace
                entry.playerName.erase(0, entry.playerName.find_first_not_of(" \t"));
                entry.playerName.erase(entry.playerName.find_last_not_of(" \t") + 1);
            }
            if (getline(iss, line, ',')) {
                entry.kills = stoi(line);
            }
            if (getline(iss, line)) {
                entry.totalScore = stoi(line);
            }

            scoreData.push_back(entry);
        }

        file.close();
    }

    // Draw the score board on screen
    void draw_score_board() {
        // Draw background
        iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BgImages[0]);

        // Draw title
        iShowImage(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT - 150, 400, 100, BgImages[1]);

        // Draw score entries
        int startX = 60;
        int startY = 280;
        int rowHeight = 50;
        int columnWidth = 200;


        for (const auto& entry : scoreData) {
            // Draw rank
            iSetColor(255, 255, 255);
            iText(startX, startY, to_string(entry.rank).c_str());

            // Draw player name
            iText(startX + columnWidth, startY, entry.playerName.c_str());

            // Draw kills
            iText(startX + 2 * columnWidth, startY, to_string(entry.kills).c_str());

            // Draw total score
            iText(startX + 3 * columnWidth, startY, to_string(entry.totalScore).c_str());

            startY -= rowHeight; // Move to next row
        }
    }
};

#endif // SCORE_SCREEN_HPP
