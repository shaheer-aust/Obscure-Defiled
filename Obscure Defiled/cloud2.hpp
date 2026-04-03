#ifndef CLOUD2_H
#define CLOUD2_H

// CloudLayer for Level 2
// - Covers the top 1280x295 pixels of the screen (y = 425 to 720)
// - Uses multiple overlapping copies of resources/cloud/image.png
// - Scrolls with the background when the hero moves
// - Layering order: BG --> CloudLayer (this) --> Hero/Enemies --> Health Bar + Score

#define CLOUD2_Y 520   // Updated for 250 height (720 - 250)
#define CLOUD2_H 250   // Exactly 250 as requested
#define CLOUD2_W 640   // Width of one cloud tile
#define CLOUD2_NUM 10  // Increased for extreme density

struct CloudLayer
{
    int  cloudImage;      // loaded image handle
    bool isActive;        // only active during specific level
    double offsetX;       // horizontal scroll offset driven by hero movement
    int targetLevel;      // level this cloud layer attaches to

    void initCloudLayer(const char* imagePath, int attachLevel)
    {
        char tempPath[256];
        strcpy_s(tempPath, 256, imagePath);
        cloudImage = iLoadImage(tempPath);
        isActive   = true;
        offsetX    = 0.0;
        targetLevel = attachLevel;
    }

    // Call this every frame the hero moves right (+dx) or left (-dx)
    void shift(double dx)
    {
        if (!isActive) return;
        offsetX += dx;

        // Wrap offset so it stays within one tile width (seamless loop)
        if (offsetX >  CLOUD2_W) offsetX -= CLOUD2_W;
        if (offsetX < -CLOUD2_W) offsetX += CLOUD2_W;
    }

    // Draw the cloud band across the top of the screen
    void draw(int currentLevel)
    {
        if (currentLevel != targetLevel) return;
        if (!isActive)         return;
        if (cloudImage == -1)  return;

        // Start tiles far enough to the left to cover the screen
        double baseStart = offsetX - (CLOUD2_W * 3);

        // Layer 1: Base layer
        for (int i = 0; i < CLOUD2_NUM; i++) {
            iShowImage((int)(baseStart + i * (CLOUD2_W * 0.8)), CLOUD2_Y, CLOUD2_W, CLOUD2_H, cloudImage);
        }

        // Layer 2: Horizontal offset layer
        for (int i = 0; i < CLOUD2_NUM; i++) {
            iShowImage((int)(baseStart + i * (CLOUD2_W * 0.8) + 150), CLOUD2_Y + 10, CLOUD2_W + 20, CLOUD2_H, cloudImage);
        }

        // Layer 3: Fills gaps in the middle
        for (int i = 0; i < CLOUD2_NUM; i++) {
            iShowImage((int)(baseStart + i * (CLOUD2_W * 0.8) - 100), CLOUD2_Y - 15, CLOUD2_W + 40, CLOUD2_H + 20, cloudImage);
        }

        // Layer 4: Front layer for maximum coverage
        for (int i = 0; i < CLOUD2_NUM; i++) {
            iShowImage((int)(baseStart + i * (CLOUD2_W * 0.8) + 300), CLOUD2_Y - 5, CLOUD2_W - 30, CLOUD2_H + 5, cloudImage);
        }
    }
};

#endif  // CLOUD2_H
