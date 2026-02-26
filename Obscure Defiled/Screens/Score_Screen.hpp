#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef SCORE_SCREEN_HPP
#define SCORE_SCREEN_HPP
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
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
        //BgImages.push_back(iLoadImage("resources//scoreboard//scorebg.png"));
        //BgImages.push_back(iLoadImage("resources//menu_screen//title.png"));
    }

    // Load scores from score.txt file
    void load_scores_from_file() {
		cout << "load score";
        ifstream file("score.txt");
        scoreData.clear();

        if (!file.is_open()) {
            return;
        }

		ScoreEntry entry;
		while (file >> entry.rank >> entry.playerName >> entry.kills >> entry.totalScore){
			scoreData.push_back(entry);
			
		}
       
		for (ScoreEntry c : scoreData){
			cout << c.playerName << endl;
		}

        file.close();
    }

    // Draw the score board on screen
    void draw_score_board() {
        // Draw background
		//cout << BgImages[0] << endl;
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, iLoadImage("resources//scoreboard//scorebg.png"));

        // Draw title
		iShowImage(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT - 150, 400, 100, iLoadImage("resources//menu_screen//title.png"));

        // Draw score entries
        int startX = 60;
        int startY = 280;
        int rowHeight = 50;
        int columnWidth = 200;
		char t[50];


        for (const auto& entry : scoreData) {
            // Draw rank
            iSetColor(255, 255, 255); 
			sprintf_s(t, "%d", entry.rank);
            iText(startX, startY, t);
			//sprintf_s(t, "%s", entry.playerName);
            // Draw player name
			int i = 0;
			for (char c : entry.playerName){
				t[i++] = c;
			}
            iText(startX + columnWidth, startY, t);

            // Draw kills
			sprintf_s(t, "%d", entry.kills);
            iText(startX + 2 * columnWidth, startY, t);

            // Draw total score
			sprintf_s(t, "%d", entry.totalScore);
            iText(startX + 3 * columnWidth, startY, t);

            startY -= rowHeight; // Move to next row
        }
    }
};

#endif // SCORE_SCREEN_HPP
