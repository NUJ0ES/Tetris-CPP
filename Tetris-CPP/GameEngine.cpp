//
//  GameEngine.cpp
//  Tetris-CPP
//
//  Created by 허준서 on 3/31/25.
//

#include "Tetris.h"
#include "GameEngine.h"

GameEngine::GameState state = GameEngine::GameState::PLAYING;

void GameEngine::init() {
    // Initialize
    makeUserBlock();
}

void GameEngine::next(double dt, char key) {
    // This will be called every frame
    if (controlled > 0.1) {
        if (key == 'l') {
            if (canGoLeft()) {
                blockX--;
                controlled = 0.0;
            }
        }
        else if (key == 'r') {
            if (canGoRight()) {
                blockX++;
                controlled = 0.0;
            }
        }
        else if (key == 'u') {
            rotate();
            controlled = 0.0;
        }
        else if (key == 'd') {
            if (canGoDown()) {
                blockY++;
                controlled = 0.0;
            }
        }
    }
    else controlled += dt;
    
    if (elapsed > 1) {
        if (canGoDown()){
            blockY++;
            elapsed = 0.0;
        }
        else {
            for (int y = 0; y < USERBLOCK_SIZE; y++) {
                for (int x = 0; x < USERBLOCK_SIZE; x++) {
                    if (!gameGridData[blockY + y][blockX + x]) gameGridData[blockY + y][blockX + x] = userBlock[y][x];
                }
            }
            for (int y = 0; y < USERBLOCK_SIZE; y++) {
                if (isFilled(blockY + y)) {
                    erase(blockY + y);
                    drop(blockY + y);
                }
            }
            
            makeUserBlock();
        }
        
    }
    else elapsed += dt;
}

void GameEngine::makeUserBlock() {
    blockX = 3;
    blockY = 0;
    
    int various = rand() % 7;
    for (int y = 0; y < USERBLOCK_SIZE; y++) {
        for (int x = 0; x < USERBLOCK_SIZE; x++) {
            GameEngine::userBlock[y][x] = GameEngine::userBlockVarious[various][y][x];
        }
    }
}

void GameEngine::makeDisplayData() {
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            displayData[y][x] = gameGridData[y][x];
        }
    }
    
    for (int y = 0; y < USERBLOCK_SIZE; y++) {
        for (int x = 0; x < USERBLOCK_SIZE; x++) {
            displayData[blockY + y][blockX + x] = gameGridData[blockY + y][blockX + x] | userBlock[y][x];
        }
    }
}

bool GameEngine::canGoDown() {
    for (int y = 0; y < USERBLOCK_SIZE; y++) {
        for (int x = 0; x < USERBLOCK_SIZE; x++) {
            if (userBlock[y][x] && (blockY + y + 2) > GRID_HEIGHT) return false;
            if (userBlock[y][x] && gameGridData[blockY + y + 1][blockX + x]) return false;
        }
    }
    return true;
}

bool GameEngine::canGoLeft() {
    for (int y = 0; y < USERBLOCK_SIZE; y++) {
        for (int x = 0; x < USERBLOCK_SIZE; x++) {
            if (userBlock[y][x] && (blockX + x - 1) < 0) return false;
            if (userBlock[y][x] && gameGridData[blockY + y][blockX + x - 1]) return false;
        }
    }
    return true;
}

bool GameEngine::canGoRight() {
    for (int y = 0; y < USERBLOCK_SIZE; y++) {
        for (int x = 0; x < USERBLOCK_SIZE; x++) {
            if (userBlock[y][x] && (blockX + x + 2) > GRID_WIDTH) return false;
            if (userBlock[y][x] && gameGridData[blockY + y][blockX + x + 1]) return false;
        }
    }
    return true;
}

bool GameEngine::canRotate(int rotated[USERBLOCK_SIZE][USERBLOCK_SIZE]) {
    for (int y = 0; y < USERBLOCK_SIZE; y++) {
        for (int x = 0; x < USERBLOCK_SIZE; x++) {
            if (rotated[y][x] && blockX + x < 0) return false;
            if (rotated[y][x] && blockX + x >= GRID_WIDTH) return false;
        }
    }
    
    return true;
}

void GameEngine::rotate() {
    int temp[USERBLOCK_SIZE][USERBLOCK_SIZE] = { 0, };
    
    for (int y = 0; y < USERBLOCK_SIZE; y++) {
        for (int x = 0; x < USERBLOCK_SIZE; x++) {
            temp[USERBLOCK_SIZE - x - 1][y] = userBlock[y][x];
        }
    }
    
    for (int y = 0; y < USERBLOCK_SIZE; y++) {
        for (int x = 0; x < USERBLOCK_SIZE; x++) {
            userBlock[y][x] = temp[y][x];
        }
    }
    
    if (!canRotate(temp) && blockX < 0) blockX++;
    else if (!canRotate(temp) && blockX > GRID_WIDTH - USERBLOCK_SIZE - 1) blockX--;
}

bool GameEngine::isFilled(int line) {
    for (int x = 0; x < GRID_WIDTH; x++) {
        if (!gameGridData[line][x]) return false;
    }
    return true;
}

void GameEngine::erase(int line) {
    for (int x = 0; x < GRID_WIDTH; x++) {
        gameGridData[line][x] = 0;
    }
}

void GameEngine::drop(int line) {
    for (int y = 0; y < line; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            gameGridData[line - y][x] = gameGridData[line - y - 1][x];
        }
    }
}
