#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef SCORE_SCREEN_HPP
#define SCORE_SCREEN_HPP
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#include <cstdio>
#include <iostream>
#include <sstream>
#include <algorithm>
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
        //BgImages.push_back(iLoadImage("resources//scoreboard//scorebg.png"));
        //BgImages.push_back(iLoadImage("resources//menu_screen//title.png"));
    }

    void sort_scores() {
		sort(scoreData.begin(), scoreData.end(), [](ScoreEntry& a, ScoreEntry& b){
			return a.totalScore >= b.totalScore; });// Sort in descending order
        };
    // Load scores from score.txt file
    void load_scores_from_file() {
		cout << "load score";
        scoreData.clear();

        FILE *file = fopen("score.txt", "r");
        if (!file) {
            return;
        }

		ScoreEntry entry;
		char playerNameBuffer[256];
		
		while (fscanf(file, "%d %255s %d %d", &entry.rank, playerNameBuffer, &entry.kills, &entry.totalScore) == 4){
			entry.playerName = playerNameBuffer;
			scoreData.push_back(entry);
			
		}
       
		for (ScoreEntry c : scoreData){
			cout << c.playerName << endl;
		}
        sort_scores();
        fclose(file);
    }

    // Draw the score board on screen
    void draw_score_board() {
        // Draw background
		//cout << BgImages[0] << endl;
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, iLoadImage("resources//scoreboard//scorebg.png"));

        // Draw title
		iShowImage(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT - 150, 400, 200, iLoadImage("resources//menu_screen//title.png"));

        // Draw score entries
        int startX = 60;
        int startY = 420;
        int rowHeight = 49;
        int columnWidth = 200;
		char t[50];


        for (const auto& entry : scoreData) {
            // Draw rank
            iSetColor(255, 255, 255); 
			//sprintf_s(t, "%d", entry.rank);
            //iText(startX, startY, t);
			//sprintf_s(t, "%s", entry.playerName);
            // Draw player name
            sprintf_s(t, "%s", entry.playerName.c_str());
            iText(startX + columnWidth, startY, t);

            // Draw kills
			sprintf_s(t, "%d", entry.kills); 
			iSetColor(0, 0, 0);
            iText(startX + 2 * columnWidth-10, startY, t,GLUT_BITMAP_HELVETICA_18);
			iSetColor(255, 255, 255);

            // Draw total score
			sprintf_s(t, "%d", entry.totalScore);
            iText(startX + 3 * columnWidth-120, startY, t);

            startY -= rowHeight; // Move to next row
        }
    }
};

#endif // SCORE_SCREEN_HPP
