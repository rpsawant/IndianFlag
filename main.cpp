#include <graphics.h>
#include <math.h>
#include <dos.h> // for delay()
#define M_PI 3.14159265358979323846 

// Window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int FLAG_WIDTH = 400;
const int FLAG_HEIGHT = 200;

// Function to get wave offset
float getWaveOffset(float x, float time) {
    float frequency = 0.04f;  // Adjust frequency for smoother wave
    float amplitude = 12.0f;  // Adjust amplitude for realistic waving
    return amplitude * sin(frequency * x + time);
}

// Function to draw a stripe with smoother rectangles
void drawFlagStripe(int startX, int startY, int width, int stripeHeight, int color, float time) {
    setcolor(color);
    setfillstyle(SOLID_FILL, color);

    for (int x = 0; x < width; x += 5) {  // Break stripe into small rectangles for smoother wave
        int offset = getWaveOffset(x, time);
        bar(startX + x, startY + offset, startX + x + 5, startY + stripeHeight + offset);
    }
}

// Function to draw Ashoka Chakra with spokes
void drawAshokaChakra(int centerX, int centerY, int radius) {
    setcolor(BLUE);
    circle(centerX, centerY, radius);
    for (int i = 0; i < 24; ++i) {
        float angle = i * 15.0 * M_PI / 180.0;  // Convert to radians
        int xEnd = centerX + radius * cos(angle);
        int yEnd = centerY + radius * sin(angle);
        line(centerX, centerY, xEnd, yEnd);
    }
}

int main() {
    // Initialize graphics window
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int midX = getmaxx() / 2;
    int midY = getmaxy() / 2;

    // Set up the flag's position
    int startX = midX - FLAG_WIDTH / 2;
    int startY = midY - FLAG_HEIGHT / 2;

    int time = 0;

    // Main animation loop
    while (!kbhit()) {  // Press any key to stop
        // Draw flagpole
        setcolor(BROWN);
        setfillstyle(SOLID_FILL, BROWN);
        bar(startX - 10, startY, startX, startY + FLAG_HEIGHT + 100);

        // Draw flag stand
        bar(startX - 30, startY + FLAG_HEIGHT + 90, startX + 20, startY + FLAG_HEIGHT + 110);

        // Draw saffron stripe
        drawFlagStripe(startX, startY, FLAG_WIDTH, FLAG_HEIGHT / 3, COLOR(255, 153, 51), time);

        // Draw white stripe
        drawFlagStripe(startX, startY + FLAG_HEIGHT / 3, FLAG_WIDTH, FLAG_HEIGHT / 3, WHITE, time);

        // Draw green stripe
        drawFlagStripe(startX, startY + 2 * FLAG_HEIGHT / 3, FLAG_WIDTH, FLAG_HEIGHT / 3, COLOR(19, 136, 8), time);

        // Draw the Ashoka Chakra in the center of the white stripe
        int chakraCenterX = startX + FLAG_WIDTH / 2;
        int chakraCenterY = startY + FLAG_HEIGHT / 2;
        int chakraRadius = 25;
        drawAshokaChakra(chakraCenterX, chakraCenterY, chakraRadius);

        // Update time for the wave effect
        time += 1;
        delay(30);  // Adjust delay for smoother animation

        // Clear screen for next frame
        cleardevice();
    }

    closegraph();
    return 0;
}

