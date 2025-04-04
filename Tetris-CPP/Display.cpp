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
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int k = 0; k < GRID_WIDTH; k++) {
            printf(displayData[i][k] ? "■ " : "□ ");
        }
        printf("\n");
    }
}
