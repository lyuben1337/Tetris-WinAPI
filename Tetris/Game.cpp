
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

Game::Game(int difficulty) {
    this->difficulty = difficulty;
    this->score = 0;
    this->startTime = time(NULL);
}

double Game::getGameTime() const {
    return difftime(time(NULL), this->startTime) * 1000;
}

