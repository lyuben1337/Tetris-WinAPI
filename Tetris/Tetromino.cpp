#include "Tetromino.h"

Tetromino::Tetromino(int x, int y, int type) {
    this->coordinate.setX(x);
    this->coordinate.setY(y);
    this->type = type;
    switch (type) {
        case I_TETROMINO:
            this->blocks.emplace_back(x, y, COLOR_CYAN);
            this->blocks.emplace_back(x, y + 1, COLOR_CYAN);
            this->blocks.emplace_back(x, y + 2, COLOR_CYAN);
            this->blocks.emplace_back(x, y + 3, COLOR_CYAN);
            break;
        case O_TETROMINO:
            this->blocks.emplace_back(x, y, COLOR_YELLOW);
            this->blocks.emplace_back(x, y + 1, COLOR_YELLOW);
            this->blocks.emplace_back(x + 1, y, COLOR_YELLOW);
            this->blocks.emplace_back(x + 1, y + 1, COLOR_YELLOW);
            break;
        case T_TETROMINO:
            this->blocks.emplace_back(x, y, COLOR_PURPLE);
            this->blocks.emplace_back(x + 1, y, COLOR_PURPLE);
            this->blocks.emplace_back(x + 2, y, COLOR_PURPLE);
            this->blocks.emplace_back(x + 1, y + 1, COLOR_PURPLE);
            break;
        case S_TETROMINO:
            this->blocks.emplace_back(x, y, COLOR_GREEN);
            this->blocks.emplace_back(x, y + 1, COLOR_GREEN);
            this->blocks.emplace_back(x + 1, y + 1, COLOR_GREEN);
            this->blocks.emplace_back(x + 1, y + 2, COLOR_GREEN);
            break;
        case Z_TETROMINO:
            this->blocks.emplace_back(x, y, COLOR_RED);
            this->blocks.emplace_back(x + 1, y, COLOR_RED);
            this->blocks.emplace_back(x + 1, y + 1, COLOR_RED);
            this->blocks.emplace_back(x + 2, y + 1, COLOR_RED);
            break;
        case J_TETROMINO:
            this->blocks.emplace_back(x, y, COLOR_BLUE);
            this->blocks.emplace_back(x, y + 1, COLOR_BLUE);
            this->blocks.emplace_back(x + 1, y + 1, COLOR_BLUE);
            this->blocks.emplace_back(x + 2, y + 1, COLOR_BLUE);
            break;
        case L_TETROMINO:
            this->blocks.emplace_back(x, y, COLOR_ORANGE);
            this->blocks.emplace_back(x, y + 1, COLOR_ORANGE);
            this->blocks.emplace_back(x, y + 2, COLOR_ORANGE);
            this->blocks.emplace_back(x + 1, y + 2, COLOR_ORANGE);
            break;
        default:
            this->blocks.emplace_back(x, y, COLOR_YELLOW);
            this->blocks.emplace_back(x, y + 1, COLOR_YELLOW);
            this->blocks.emplace_back(x + 1, y, COLOR_YELLOW);
            this->blocks.emplace_back(x + 1, y + 1, COLOR_YELLOW);
            break;
    }
}

void Tetromino::draw(HDC hdc, const Canvas &canvas) {
    for (auto block: this->blocks) {
        block.draw(hdc, canvas);
    }
}

void Tetromino::move(int direction, Canvas canvas) {
    if (canMove(direction, canvas)) {
        switch (direction) {
            case D_DOWN:
                for (auto &block: this->blocks) {
                    Coordinate newCoordinate = block.getCoordinate();
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    block.setCoordinate(newCoordinate);
                }
                break;
            case D_LEFT:
                for (auto &block: this->blocks) {
                    Coordinate newCoordinate = block.getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    block.setCoordinate(newCoordinate);
                }
                break;
            case D_RIGHT:
                for (auto &block: this->blocks) {
                    Coordinate newCoordinate = block.getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    block.setCoordinate(newCoordinate);
                }
                break;
            default:
                break;
        }
    }
}

bool Tetromino::canMove(int direction, Canvas canvas) {
    switch (direction) {
        case D_DOWN: {
            for (auto block: this->blocks) {
                Coordinate newCoordinate = block.getCoordinate();
                newCoordinate.setY(newCoordinate.getY() + 1);
                if (!canvas.isCoordinateFree(newCoordinate)) {
                    return false;
                }
            }
            return true;
        }
        case D_LEFT: {
            for (auto block: this->blocks) {
                Coordinate newCoordinate = block.getCoordinate();
                newCoordinate.setX(newCoordinate.getX() - 1);
                if (!canvas.isCoordinateFree(newCoordinate)) {
                    return false;
                }
            }
            return true;
        }
        case D_RIGHT: {
            for (auto block: this->blocks) {
                Coordinate newCoordinate = block.getCoordinate();
                newCoordinate.setX(newCoordinate.getX() + 1);
                if (!canvas.isCoordinateFree(newCoordinate)) {
                    return false;
                }
            }
            return true;
        }
        default:
            return false;
    }
}
