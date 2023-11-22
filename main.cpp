#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <termios.h>
#include "head.h"

using namespace std;

const int SIZE = 4;

int board[SIZE][SIZE];

void initBoard() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = 0;
        }
    }

    // 初始化两个随机位置
    srand(time(0));
    int randRow1 = rand() % SIZE;
    int randCol1 = rand() % SIZE;
    int randRow2, randCol2;
    
    do {
        randRow2 = rand() % SIZE;
        randCol2 = rand() % SIZE;
    } while (randRow1 == randRow2 && randCol1 == randCol2);

    board[randRow1][randCol1] = 2;
    board[randRow2][randCol2] = 2;
}

void printBoard() {
     clearScreen();

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << setw(5) << board[i][j];
        }
        cout << endl;
    }
}

bool isGameOver() {
    // 检查是否有空位置
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }

    // 检查是否有相邻相等的数字
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE - 1; ++j) {
            if (board[i][j] == board[i][j + 1] || board[j][i] == board[j + 1][i]) {
                return false;
            }
        }
    }

    return true;
}

void generateRandom() {
    // 在随机空位置生成2或4
    int emptyCount = 0;
    int emptyPositions[SIZE * SIZE][2];

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                emptyPositions[emptyCount][0] = i;
                emptyPositions[emptyCount][1] = j;
                ++emptyCount;
            }
        }
    }

    if (emptyCount > 0) {
        int randIndex = rand() % emptyCount;
        int randValue = (rand() % 2 + 1) * 2;  // 生成2或4
        board[emptyPositions[randIndex][0]][emptyPositions[randIndex][1]] = randValue;
    }
}

void moveLeft() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE - 1; ++j) {
            if (board[i][j] == 0) {
                for (int k = j + 1; k < SIZE; ++k) {
                    if (board[i][k] != 0) {
                        board[i][j] = board[i][k];
                        board[i][k] = 0;
                        break;
                    }
                }
            } else {
                for (int k = j + 1; k < SIZE; ++k) {
                    if (board[i][k] != 0) {
                        if (board[i][j] == board[i][k]) {
                            board[i][j] *= 2;
                            board[i][k] = 0;
                        }
                        break;
                    }
                }
            }
        }
    }
}

void handleInput() {
    char ch =getChar();  // 使用macos下独特的输入方式，macos下要实现不按下enter输入较困难

    switch (ch) {
        case 'a':
            moveLeft();
            break;
        case 's':
            // 处理其他方向的移动，如下移动 's'
            // moveDown();
            break;
        // 处理其他方向的移动
        // case 'w':
        //     moveUp();
        //     break;
        // case 'd':
        //     moveRight();
        //     break;
        default:
            break;
    }
}

int main() {
    initBoard();
    
    while (!isGameOver()) {
        printBoard();
        handleInput();
        generateRandom();
    }

    cout << "Game Over!" << endl;

    return 0;
}
