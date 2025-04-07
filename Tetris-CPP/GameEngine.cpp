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
    if (key == 'l') {
        if (controlled > 0.1) {
            if (canGoLeft()) {
                blockX--;
                controlled = 0.0;
            }
        }
        else controlled += dt;
    }
    else if (key == 'r') {
        if (controlled > 0.1) {
            if (canGoRight()) {
                blockX++;
                controlled = 0.0;
            }
        }
        else controlled += dt;
    }
    else if (key == 'u') {
        if (controlled > 0.2) {
            rotate();
            controlled = 0.0;
        }
        else controlled += dt;
    }
    else if (key == 'd') {
        if (controlled > 0.1) {
            if (canGoDown()) {
                blockY++;
                controlled = 0.0;
            }
        }
        else controlled += dt;
    }
    
    if (elapsed > 1) {
        if (canGoDown()){
            blockY++;
            elapsed = 0.0;
        }
        else {
            for (int i = 0; i < USERBLOCK_SIZE; i++) {
                for (int k = 0; k < USERBLOCK_SIZE; k++) {
                    if (!gameGridData[blockY + i][blockX + k]) gameGridData[blockY + i][blockX + k] = userBlock[i][k];
                }
            }
            for (int i = 0; i < USERBLOCK_SIZE; i++) {
                if (isFilled(blockY + i)) {
                    erase(blockY + i);
                    drop(blockY + i);
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
    for (int i = 0; i < USERBLOCK_SIZE; i++) {
        for (int k = 0; k < USERBLOCK_SIZE; k++) {
            GameEngine::userBlock[i][k] = GameEngine::userBlockVarious[various][i][k];
        }
    }
}

void GameEngine::makeDisplayData() {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int k = 0; k < GRID_WIDTH; k++) {
            displayData[i][k] = gameGridData[i][k];
        }
    }
    
    for (int i = 0; i < USERBLOCK_SIZE; i++) {
        for (int k = 0; k < USERBLOCK_SIZE; k++) {
            displayData[blockY + i][blockX + k] = gameGridData[blockY + i][blockX + k] | userBlock[i][k];
        }
    }
}

bool GameEngine::canGoDown() {
    for (int i = 0; i < USERBLOCK_SIZE; i++) {
        for (int k = 0; k < USERBLOCK_SIZE; k++) {
            if (userBlock[i][k] && (blockY + i + 2) > GRID_HEIGHT) return false;
            if (userBlock[i][k] && gameGridData[blockY + i + 1][blockX + k]) return false;
        }
    }
    return true;
}

bool GameEngine::canGoLeft() {
    for (int i = 0; i < USERBLOCK_SIZE; i++) {
        for (int k = 0; k < USERBLOCK_SIZE; k++) {
            if (userBlock[i][k] && (blockX + k - 1) < 0) return false;
            if (userBlock[i][k] && gameGridData[blockY + i][blockX + k - 1]) return false;
        }
    }
    return true;
}

bool GameEngine::canGoRight() {
    for (int i = 0; i < USERBLOCK_SIZE; i++) {
        for (int k = 0; k < USERBLOCK_SIZE; k++) {
            if (userBlock[i][k] && (blockX + k + 2) > GRID_WIDTH) return false;
            if (userBlock[i][k] && gameGridData[blockY + i][blockX + k + 1]) return false;
        }
    }
    return true;
}

bool GameEngine::canRotate(int rotated[USERBLOCK_SIZE][USERBLOCK_SIZE]) {
    for (int i = 0; i < USERBLOCK_SIZE; i++) {
        for (int k = 0; k < USERBLOCK_SIZE; k++) {
            if (rotated[i][k] && blockX + k < 0) return false;
            if (rotated[i][k] && blockX + k >= GRID_WIDTH) return false;
        }
    }
    
    return true;
}

void GameEngine::rotate() {
    int temp[USERBLOCK_SIZE][USERBLOCK_SIZE] = { 0, };
    
    for (int i = 0; i < USERBLOCK_SIZE; i++) {
        for (int k = 0; k < USERBLOCK_SIZE; k++) {
            temp[USERBLOCK_SIZE - k - 1][i] = userBlock[i][k];
        }
    }
    
    for (int i = 0; i < USERBLOCK_SIZE; i++) {
        for (int k = 0; k < USERBLOCK_SIZE; k++) {
            userBlock[i][k] = temp[i][k];
        }
    }
    
    if (!canRotate(temp) && blockX < 0) blockX++;
    else if (!canRotate(temp) && blockX > GRID_WIDTH - USERBLOCK_SIZE - 1) blockX--;
}

bool GameEngine::isFilled(int line) {
    for (int i = 0; i < GRID_WIDTH; i++) {
        if (!gameGridData[line][i]) return false;
    }
    return true;
}

void GameEngine::erase(int line) {
    for (int i = 0; i < GRID_WIDTH; i++) {
        gameGridData[line][i] = 0;
    }
}

void GameEngine::drop(int line) {
    for (int i = 0; i < line; i++) {
        for (int k = 0; k < GRID_WIDTH; k++) {
            gameGridData[line - i][k] = gameGridData[line - i - 1][k];
        }
    }
}
