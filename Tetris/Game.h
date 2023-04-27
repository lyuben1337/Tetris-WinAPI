#ifndef TETRIS_WINAPI_GAME_H
#define TETRIS_WINAPI_GAME_H

#include "Functions.h"
#include "Canvas.h"
#include "Tetromino.h"
#include <ctime>

class Game {
public:
    Canvas canvas{};
    Tetromino currentTetromino = Tetromino::RandomTetromino();
    Tetromino nextTetromino = Tetromino::RandomTetromino();

    int getDifficulty() const;

    void setDifficulty(int difficulty);

    int getScore() const;

    void setScore(int score);

    bool isGameOver() const;

    void setIsGameOver(bool gameOver);

    explicit Game(int difficulty = DIFFICULTY_EASY);

    double getGameTime() const;

    void setGameOver(bool gameOver);

    time_t getStartTime() const;

    void setStartTime(time_t startTime);

private:
    int difficulty{};
    int score{};
    bool gameOver{};
    time_t startTime{};
};


#endif //TETRIS_WINAPI_GAME_H
