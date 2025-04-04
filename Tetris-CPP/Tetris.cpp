//
//  Tetris.cpp
//  Tetris-CPP
//
//  Created by 허준서 on 3/31/25.
//

#include "Tetris.h"
#include "Display.h"
#include "GameEngine.h"

#define INTERVAL 1.0 / 60.0

int displayData[GRID_HEIGHT][GRID_WIDTH] = { 0, };

int main(int argc, const char * argv[]) {
    printf("\e[?25l"); // Make cursor invisible
    
    
    srand((unsigned int)(time(NULL)));
    rand(); // This line is to make random truely random. I can't find a way to prevent first random number from being 6.
            // Why is first random number's remainder always 6, even though every number is different???? How is it possible???
    
    double prev = (double)clock() / CLOCKS_PER_SEC;
    
    Display* display = new Display;
    GameEngine* gameEngine = new GameEngine;
    
    gameEngine->init();
    
    while (true) {
        double curr = (double)clock() / CLOCKS_PER_SEC;
        double dt = curr - prev;
        
        if (dt < INTERVAL) continue;
        prev = curr;
        
        if (CGEventSourceKeyState(kCGEventSourceStateHIDSystemState, kVK_LeftArrow)) {
            gameEngine->next(dt, 'l');
        }
        else if (CGEventSourceKeyState(kCGEventSourceStateHIDSystemState, kVK_RightArrow)) {
            gameEngine->next(dt, 'r');
        }
        else if (CGEventSourceKeyState(kCGEventSourceStateHIDSystemState, kVK_UpArrow)) {
            gameEngine->next(dt, 'u');
        }
        else if (CGEventSourceKeyState(kCGEventSourceStateHIDSystemState, kVK_DownArrow)) {
            gameEngine->next(dt, 'd');
        }
        gameEngine->next(dt, 0);
        
        gameEngine->makeDisplayData();
        display->draw();
        
    }

    return 0;
}
