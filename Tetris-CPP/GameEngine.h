//
//  GameEngine.h
//  Tetris-CPP
//
//  Created by 허준서 on 3/31/25.
//

#ifndef __GAMEENGINE_H__
#define __GAMEENGINE_H__

#include "Tetris.h"

#define USERBLOCK_SIZE 4

class GameEngine {
public:
    enum class GameState {
        PLAYING, GAMEOVER
    };
    
    GameState state = GameState::PLAYING;
    
    int gameGridData[GRID_HEIGHT][GRID_WIDTH] = { 0, };
    
    int userBlock[USERBLOCK_SIZE][USERBLOCK_SIZE] = { 0, };
    
    int blockX = 3;
    int blockY = 0;
    
    double elapsed = 0.0;
    double controlled = 0.0;
    
    int userBlockVarious[7][USERBLOCK_SIZE][USERBLOCK_SIZE] = {
        {
            {0,0,0,0},
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,0,0,0},
            {1,1,1,1},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,0,0,1},
            {0,1,1,1},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {1,0,0,0},
            {1,1,1,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,0,1,0},
            {0,1,1,1},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,0,1,1},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0}
        }
    };
    
    
    
    void init();
    
    void next(double dt, char key);
    
    void makeUserBlock();
    
    void makeDisplayData(); // Assign gameGridData + userBlock to displayData
    
    bool canGoDown();
    
    bool canGoLeft();
    
    bool canGoRight();
    
    bool canRotate(int rotated[USERBLOCK_SIZE][USERBLOCK_SIZE]);
    
    void rotate();
    
    bool isFilled(int line);
    
    void erase(int line);
    
    void drop(int line);
    
    void determineGameState();
};

#endif
