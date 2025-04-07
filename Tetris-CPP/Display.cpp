//
//  Display.cpp
//  Tetris-CPP
//
//  Created by 허준서 on 3/31/25.
//

#include "Tetris.h"
#include "Display.h"

void Display::draw() {
    printf("\033[H\033[J"); // Make console clear
    //system("clear");
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            printf(displayData[y][x] ? "■ " : "□ ");
        }
        printf("\n");
    }
}
