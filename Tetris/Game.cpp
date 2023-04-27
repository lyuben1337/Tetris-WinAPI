
#include "Game.h"

int Game::getDifficulty() const {
    return difficulty;
}

void Game::setDifficulty(int difficulty) {
    Game::difficulty = difficulty;
}

int Game::getScore() const {
    return score;
}

void Game::setScore(int score) {
    Game::score = score;
}

bool Game::isGameOver() const {
    return gameOver;
}

void Game::setIsGameOver(bool gameOver) {
    Game::gameOver = gameOver;
}

Game::Game(int difficulty) {
    this->difficulty = difficulty;
    this->score = 0;
    this->gameOver = false;
    this->startTime = time(NULL);
}

double Game::getGameTime() const {
    return difftime(time(NULL), this->startTime) * 1000;
}

void Game::setGameOver(bool gameOver) {
    Game::gameOver = gameOver;
}

time_t Game::getStartTime() const {
    return startTime;
}

void Game::setStartTime(time_t startTime) {
    Game::startTime = startTime;
}
