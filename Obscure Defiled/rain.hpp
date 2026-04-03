#ifndef RAIN_H
#define RAIN_H

#include <vector>
#include <cstdlib>

struct BoundingBox {
    double x, y, w, h;
};

struct RainDrop {
    double x, y;
    bool isActive;
    bool isTouching;
    int touchTimer;
};

struct RainSystem {
    int dropImage;
    int touchImage;
    std::vector<RainDrop> drops;
    double rainSpeed;
    bool isActive;

    void initRain() {
        dropImage = iLoadImage("resources\\Rain\\drop\\rain_drop.png");
        touchImage = iLoadImage("resources\\Rain\\drop_touch\\touch.png");
        
        drops.resize(1000);
        for(int i = 0; i < 1000; i++) {
            drops[i].x = rand() % 1280;
            // Spread initial Y across a wide range so rain is full screen immediately
            drops[i].y = 100 + (rand() % 620); 
            drops[i].isActive = true;
            drops[i].isTouching = false;
            drops[i].touchTimer = 0;
        }
        rainSpeed = 1.3; // Decreased to 1.3 for a slower, smooth effect
        isActive = true;
    }

    bool isPointInside(double px, double py, double rx, double ry, double rw, double rh) {
        return (px >= rx && px <= rx + rw && py >= ry && py <= ry + rh);
    }

    void drawRain(double passedGroundY, const std::vector<BoundingBox>& surfaces) {
        if (!isActive) return;

        // Use a fixed ground Y of 100.0 as requested
        double fixedGroundY = 100.0;

        for (int i = 0; i < 1000; i++) {
            if (drops[i].isTouching) {
                if (touchImage != -1) {
                    iShowImage((int)drops[i].x - 5, (int)drops[i].y, 20, 20, touchImage); 
                }
                drops[i].touchTimer++;
                if (drops[i].touchTimer > 5) {
                    // Reset to top (under cloud layer area)
                    drops[i].x = rand() % 1280;
                    drops[i].y = 520 + (rand() % 100);
                    drops[i].isTouching = false;
                    drops[i].touchTimer = 0;
                }
            } else {
                drops[i].y -= rainSpeed;

                bool collided = false;
                // Check fixed ground at 100px
                if (drops[i].y <= fixedGroundY) {
                    collided = true;
                } else {
                    // Check other surfaces (hero, enemy, etc)
                    for (size_t j = 0; j < surfaces.size(); j++) {
                        if (isPointInside(drops[i].x, drops[i].y, surfaces[j].x, surfaces[j].y, surfaces[j].w, surfaces[j].h)) {
                            collided = true;
                            break;
                        }
                    }
                }

                if (collided) {
                    drops[i].isTouching = true;
                    drops[i].touchTimer = 0;
                } else {
                    if (dropImage != -1) {
                        iShowImage((int)drops[i].x, (int)drops[i].y, 10, 20, dropImage); 
                    }
                }
            }
        }
    }
};

#endif
