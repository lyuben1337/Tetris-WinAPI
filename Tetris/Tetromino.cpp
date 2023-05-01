#include <ctime>
#include "Tetromino.h"

Tetromino::Tetromino(int x, int y, int type) {
    this->coordinate.setX(x);
    this->coordinate.setY(y);
    this->type = type;
    this->rotation = ROTATION_0;
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

Tetromino Tetromino::RandomTetromino() {
    srand(time(NULL));
    int x = std::rand() % 6;
    int tetrominoType;
    switch (std::rand() % 7) {
        case 0:
            tetrominoType = I_TETROMINO;
            break;
        case 1:
            tetrominoType = O_TETROMINO;
            break;
        case 2:
            tetrominoType = T_TETROMINO;
            break;
        case 3:
            tetrominoType = S_TETROMINO;
            break;
        case 4:
            tetrominoType = Z_TETROMINO;
            break;
        case 5:
            tetrominoType = J_TETROMINO;
            break;
        case 6:
            tetrominoType = L_TETROMINO;
            break;
    }
    return {x, 0, tetrominoType};
}

void Tetromino::draw(HDC hdc, const Canvas &canvas) {
    for (auto block: this->blocks) {
        block.draw(hdc, canvas);
    }
}

void Tetromino::move(int direction, Canvas canvas) {
    if (canMove(direction, canvas)) {
        switch (direction) {
            case DIRECTION_DOWN:
                for (auto &block: this->blocks) {
                    Coordinate newCoordinate = block.getCoordinate();
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    block.setCoordinate(newCoordinate);
                }
                break;
            case DIRECTION_LEFT:
                for (auto &block: this->blocks) {
                    Coordinate newCoordinate = block.getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    block.setCoordinate(newCoordinate);
                }
                break;
            case DIRECTION_RIGHT:
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

void Tetromino::rotate(Canvas canvas) {
    if (canRotate(canvas)) {
        Coordinate newCoordinate;
        switch (this->type) {
            case I_TETROMINO:
                switch (this->rotation) {
                    case ROTATION_0:
                        newCoordinate = this->blocks[0].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 1);
                        newCoordinate.setY(newCoordinate.getY() + 1);
                        this->blocks[0].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[2].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 1);
                        newCoordinate.setY(newCoordinate.getY() - 1);
                        this->blocks[2].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[3].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 2);
                        newCoordinate.setY(newCoordinate.getY() - 2);
                        this->blocks[3].setCoordinate(newCoordinate);
                        this->rotation = ROTATION_90;
                        break;
                    case ROTATION_90:
                        newCoordinate = this->blocks[0].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 1);
                        newCoordinate.setY(newCoordinate.getY() - 1);
                        this->blocks[0].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[2].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 1);
                        newCoordinate.setY(newCoordinate.getY() + 1);
                        this->blocks[2].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[3].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 2);
                        newCoordinate.setY(newCoordinate.getY() + 2);
                        this->blocks[3].setCoordinate(newCoordinate);
                        this->rotation = ROTATION_0;
                        break;
                }
                break;
            case T_TETROMINO:
                switch (this->rotation) {
                    case ROTATION_0:
                        newCoordinate = this->blocks[0].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 1);
                        newCoordinate.setY(newCoordinate.getY() - 1);
                        this->blocks[0].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[2].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 1);
                        newCoordinate.setY(newCoordinate.getY() + 1);
                        this->blocks[2].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[3].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 1);
                        newCoordinate.setY(newCoordinate.getY() - 1);
                        this->blocks[3].setCoordinate(newCoordinate);
                        this->rotation = ROTATION_90;
                        break;
                    case ROTATION_90:
                        newCoordinate = this->blocks[0].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 1);
                        newCoordinate.setY(newCoordinate.getY() + 1);
                        this->blocks[0].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[2].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 1);
                        newCoordinate.setY(newCoordinate.getY() - 1);
                        this->blocks[2].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[3].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 1);
                        newCoordinate.setY(newCoordinate.getY() - 1);
                        this->blocks[3].setCoordinate(newCoordinate);
                        this->rotation = ROTATION_180;
                        break;
                    case ROTATION_180:
                        newCoordinate = this->blocks[0].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 1);
                        newCoordinate.setY(newCoordinate.getY() + 1);
                        this->blocks[0].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[2].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 1);
                        newCoordinate.setY(newCoordinate.getY() - 1);
                        this->blocks[2].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[3].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 1);
                        newCoordinate.setY(newCoordinate.getY() + 1);
                        this->blocks[3].setCoordinate(newCoordinate);
                        this->rotation = ROTATION_270;
                        break;
                    case ROTATION_270:
                        newCoordinate = this->blocks[0].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 1);
                        newCoordinate.setY(newCoordinate.getY() - 1);
                        this->blocks[0].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[2].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 1);
                        newCoordinate.setY(newCoordinate.getY() + 1);
                        this->blocks[2].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[3].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 1);
                        newCoordinate.setY(newCoordinate.getY() + 1);
                        this->blocks[3].setCoordinate(newCoordinate);
                        this->rotation = ROTATION_0;
                        break;
                }
                break;
            case S_TETROMINO:
                switch (this->rotation) {
                    case ROTATION_0:
                        newCoordinate = this->blocks[0].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 2);
                        newCoordinate.setY(newCoordinate.getY() + 1);
                        this->blocks[0].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[1].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 1);
                        newCoordinate.setY(newCoordinate.getY());
                        this->blocks[1].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[2].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX());
                        newCoordinate.setY(newCoordinate.getY() + 1);
                        this->blocks[2].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[3].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 1);
                        newCoordinate.setY(newCoordinate.getY());
                        this->blocks[3].setCoordinate(newCoordinate);
                        this->rotation = ROTATION_90;
                        break;
                    case ROTATION_90:
                        newCoordinate = this->blocks[0].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 2);
                        newCoordinate.setY(newCoordinate.getY() - 1);
                        this->blocks[0].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[1].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 1);
                        newCoordinate.setY(newCoordinate.getY());
                        this->blocks[1].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[2].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX());
                        newCoordinate.setY(newCoordinate.getY() - 1);
                        this->blocks[2].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[3].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 1);
                        newCoordinate.setY(newCoordinate.getY());
                        this->blocks[3].setCoordinate(newCoordinate);
                        this->rotation = ROTATION_0;
                        break;
                }
                break;
            case Z_TETROMINO:
                switch (this->rotation) {
                    case ROTATION_0:
                        newCoordinate = this->blocks[0].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 1);
                        newCoordinate.setY(newCoordinate.getY());
                        this->blocks[0].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[1].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX());
                        newCoordinate.setY(newCoordinate.getY() + 1);
                        this->blocks[1].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[2].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 1);
                        newCoordinate.setY(newCoordinate.getY());
                        this->blocks[2].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[3].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 2);
                        newCoordinate.setY(newCoordinate.getY() + 1);
                        this->blocks[3].setCoordinate(newCoordinate);
                        this->rotation = ROTATION_90;
                        break;
                    case ROTATION_90:
                        newCoordinate = this->blocks[0].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 1);
                        newCoordinate.setY(newCoordinate.getY());
                        this->blocks[0].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[1].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX());
                        newCoordinate.setY(newCoordinate.getY() - 1);
                        this->blocks[1].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[2].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 1);
                        newCoordinate.setY(newCoordinate.getY());
                        this->blocks[2].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[3].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 2);
                        newCoordinate.setY(newCoordinate.getY() - 1);
                        this->blocks[3].setCoordinate(newCoordinate);
                        this->rotation = ROTATION_0;
                        break;
                }
                break;
            case J_TETROMINO:
                switch (this->rotation) {
                    case ROTATION_0:
                        newCoordinate = this->blocks[0].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 1);
                        newCoordinate.setY(newCoordinate.getY());
                        this->blocks[0].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[1].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX());
                        newCoordinate.setY(newCoordinate.getY() - 1);
                        this->blocks[1].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[2].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 1);
                        newCoordinate.setY(newCoordinate.getY());
                        this->blocks[2].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[3].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 2);
                        newCoordinate.setY(newCoordinate.getY() + 1);
                        this->blocks[3].setCoordinate(newCoordinate);
                        this->rotation = ROTATION_90;
                        break;
                    case ROTATION_90:
                        newCoordinate = this->blocks[0].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 1);
                        newCoordinate.setY(newCoordinate.getY() + 1);
                        this->blocks[0].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[1].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 2);
                        newCoordinate.setY(newCoordinate.getY());
                        this->blocks[1].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[2].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 1);
                        newCoordinate.setY(newCoordinate.getY() - 1);
                        this->blocks[2].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[3].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX());
                        newCoordinate.setY(newCoordinate.getY() - 2);
                        this->blocks[3].setCoordinate(newCoordinate);
                        this->rotation = ROTATION_180;
                        break;
                    case ROTATION_180:
                        newCoordinate = this->blocks[0].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 2);
                        newCoordinate.setY(newCoordinate.getY() + 1);
                        this->blocks[0].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[1].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 1);
                        newCoordinate.setY(newCoordinate.getY() + 2);
                        this->blocks[1].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[2].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX());
                        newCoordinate.setY(newCoordinate.getY() + 1);
                        this->blocks[2].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[3].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 1);
                        newCoordinate.setY(newCoordinate.getY());
                        this->blocks[3].setCoordinate(newCoordinate);
                        this->rotation = ROTATION_270;
                        break;
                    case ROTATION_270:
                        newCoordinate = this->blocks[0].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX());
                        newCoordinate.setY(newCoordinate.getY() - 2);
                        this->blocks[0].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[1].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 1);
                        newCoordinate.setY(newCoordinate.getY() - 1);
                        this->blocks[1].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[3].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 1);
                        newCoordinate.setY(newCoordinate.getY() + 1);
                        this->blocks[3].setCoordinate(newCoordinate);
                        this->rotation = ROTATION_0;
                        break;
                }
                break;
            case L_TETROMINO:
                switch (this->rotation) {
                    case ROTATION_0:
                        newCoordinate = this->blocks[0].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 2);
                        newCoordinate.setY(newCoordinate.getY());
                        this->blocks[0].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[1].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 1);
                        newCoordinate.setY(newCoordinate.getY() - 1);
                        this->blocks[1].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[2].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX());
                        newCoordinate.setY(newCoordinate.getY() - 2);
                        this->blocks[2].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[3].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 1);
                        newCoordinate.setY(newCoordinate.getY() - 1);
                        this->blocks[3].setCoordinate(newCoordinate);
                        this->rotation = ROTATION_90;
                        break;
                    case ROTATION_90:
                        newCoordinate = this->blocks[0].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 1);
                        newCoordinate.setY(newCoordinate.getY() + 2);
                        this->blocks[0].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[1].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX());
                        newCoordinate.setY(newCoordinate.getY() + 1);
                        this->blocks[1].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[2].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 1);
                        newCoordinate.setY(newCoordinate.getY());
                        this->blocks[2].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[3].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX());
                        newCoordinate.setY(newCoordinate.getY() - 1);
                        this->blocks[3].setCoordinate(newCoordinate);
                        this->rotation = ROTATION_180;
                        break;
                    case ROTATION_180:
                        newCoordinate = this->blocks[0].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 1);
                        newCoordinate.setY(newCoordinate.getY() - 1);
                        this->blocks[0].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[2].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 1);
                        newCoordinate.setY(newCoordinate.getY() + 1);
                        this->blocks[2].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[3].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() + 2);
                        newCoordinate.setY(newCoordinate.getY());
                        this->blocks[3].setCoordinate(newCoordinate);
                        this->rotation = ROTATION_270;
                        break;
                    case ROTATION_270:
                        newCoordinate = this->blocks[0].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX());
                        newCoordinate.setY(newCoordinate.getY() - 1);
                        this->blocks[0].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[1].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 1);
                        newCoordinate.setY(newCoordinate.getY());
                        this->blocks[1].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[2].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 2);
                        newCoordinate.setY(newCoordinate.getY() + 1);
                        this->blocks[2].setCoordinate(newCoordinate);
                        newCoordinate = this->blocks[3].getCoordinate();
                        newCoordinate.setX(newCoordinate.getX() - 1);
                        newCoordinate.setY(newCoordinate.getY() + 2);
                        this->blocks[3].setCoordinate(newCoordinate);
                        this->rotation = ROTATION_0;
                        break;
                }
                break;
            default:
                break;
        }
    }
}

bool Tetromino::canMove(int direction, Canvas canvas) {
    switch (direction) {
        case DIRECTION_DOWN: {
            for (auto block: this->blocks) {
                Coordinate newCoordinate = block.getCoordinate();
                newCoordinate.setY(newCoordinate.getY() + 1);
                if (!canvas.isCoordinateFree(newCoordinate)) {
                    return false;
                }
            }
            return true;
        }
        case DIRECTION_LEFT: {
            for (auto block: this->blocks) {
                Coordinate newCoordinate = block.getCoordinate();
                newCoordinate.setX(newCoordinate.getX() - 1);
                if (!canvas.isCoordinateFree(newCoordinate)) {
                    return false;
                }
            }
            return true;
        }
        case DIRECTION_RIGHT: {
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

bool Tetromino::canRotate(Canvas canvas) {
    Coordinate newCoordinate;
    switch (this->type) {
        case I_TETROMINO:
            switch (this->rotation) {
                case ROTATION_0:
                    newCoordinate = this->blocks[0].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[2].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    newCoordinate.setY(newCoordinate.getY() - 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[3].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 2);
                    newCoordinate.setY(newCoordinate.getY() - 2);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    return true;
                case ROTATION_90:
                    newCoordinate = this->blocks[0].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    newCoordinate.setY(newCoordinate.getY() - 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[2].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[3].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 2);
                    newCoordinate.setY(newCoordinate.getY() + 2);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    return true;
            }
            return true;
        case T_TETROMINO:
            switch (this->rotation) {
                case ROTATION_0:
                    newCoordinate = this->blocks[0].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    newCoordinate.setY(newCoordinate.getY() - 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[2].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[3].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    newCoordinate.setY(newCoordinate.getY() - 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    return true;
                case ROTATION_90:
                    newCoordinate = this->blocks[0].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[2].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    newCoordinate.setY(newCoordinate.getY() - 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[3].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    newCoordinate.setY(newCoordinate.getY() - 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    return true;
                case ROTATION_180:
                    newCoordinate = this->blocks[0].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[2].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    newCoordinate.setY(newCoordinate.getY() - 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[3].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    return true;
                case ROTATION_270:
                    newCoordinate = this->blocks[0].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    newCoordinate.setY(newCoordinate.getY() - 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[2].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[3].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    return true;
            }
            return true;
        case S_TETROMINO:
            switch (this->rotation) {
                case ROTATION_0:
                    newCoordinate = this->blocks[0].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 2);
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[1].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    newCoordinate.setY(newCoordinate.getY());
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[2].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX());
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[3].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    newCoordinate.setY(newCoordinate.getY());
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    return true;
                case ROTATION_90:
                    newCoordinate = this->blocks[0].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 2);
                    newCoordinate.setY(newCoordinate.getY() - 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[1].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    newCoordinate.setY(newCoordinate.getY());
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[2].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX());
                    newCoordinate.setY(newCoordinate.getY() - 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[3].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    newCoordinate.setY(newCoordinate.getY());
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    return true;
            }
            return true;
        case Z_TETROMINO:
            switch (this->rotation) {
                case ROTATION_0:
                    newCoordinate = this->blocks[0].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    newCoordinate.setY(newCoordinate.getY());
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[1].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX());
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[2].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    newCoordinate.setY(newCoordinate.getY());
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[3].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 2);
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    return true;
                case ROTATION_90:
                    newCoordinate = this->blocks[0].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    newCoordinate.setY(newCoordinate.getY());
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[1].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX());
                    newCoordinate.setY(newCoordinate.getY() - 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[2].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    newCoordinate.setY(newCoordinate.getY());
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[3].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 2);
                    newCoordinate.setY(newCoordinate.getY() - 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    return true;
            }
            return true;
        case J_TETROMINO:
            switch (this->rotation) {
                case ROTATION_0:
                    newCoordinate = this->blocks[0].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    newCoordinate.setY(newCoordinate.getY());
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[1].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX());
                    newCoordinate.setY(newCoordinate.getY() - 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[2].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    newCoordinate.setY(newCoordinate.getY());
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[3].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 2);
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    return true;
                case ROTATION_90:
                    newCoordinate = this->blocks[0].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[1].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 2);
                    newCoordinate.setY(newCoordinate.getY());
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[2].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    newCoordinate.setY(newCoordinate.getY() - 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[3].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX());
                    newCoordinate.setY(newCoordinate.getY() - 2);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    return true;
                case ROTATION_180:
                    newCoordinate = this->blocks[0].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 2);
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[1].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    newCoordinate.setY(newCoordinate.getY() + 2);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[2].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX());
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[3].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    newCoordinate.setY(newCoordinate.getY());
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    return true;
                case ROTATION_270:
                    newCoordinate = this->blocks[0].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX());
                    newCoordinate.setY(newCoordinate.getY() - 2);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[1].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    newCoordinate.setY(newCoordinate.getY() - 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[3].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    return true;
            }
            return true;
        case L_TETROMINO:
            switch (this->rotation) {
                case ROTATION_0:
                    newCoordinate = this->blocks[0].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 2);
                    newCoordinate.setY(newCoordinate.getY());
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[1].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    newCoordinate.setY(newCoordinate.getY() - 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[2].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX());
                    newCoordinate.setY(newCoordinate.getY() - 2);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[3].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    newCoordinate.setY(newCoordinate.getY() - 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    return true;
                case ROTATION_90:
                    newCoordinate = this->blocks[0].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    newCoordinate.setY(newCoordinate.getY() + 2);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[1].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX());
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[2].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    newCoordinate.setY(newCoordinate.getY());
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[3].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX());
                    newCoordinate.setY(newCoordinate.getY() - 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    return true;
                case ROTATION_180:
                    newCoordinate = this->blocks[0].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    newCoordinate.setY(newCoordinate.getY() - 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[2].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 1);
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[3].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() + 2);
                    newCoordinate.setY(newCoordinate.getY());
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    return true;
                case ROTATION_270:
                    newCoordinate = this->blocks[0].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX());
                    newCoordinate.setY(newCoordinate.getY() - 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[1].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    newCoordinate.setY(newCoordinate.getY());
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[2].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 2);
                    newCoordinate.setY(newCoordinate.getY() + 1);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    newCoordinate = this->blocks[3].getCoordinate();
                    newCoordinate.setX(newCoordinate.getX() - 1);
                    newCoordinate.setY(newCoordinate.getY() + 2);
                    if (!canvas.isCoordinateFree(newCoordinate)) {
                        return false;
                    }
                    return true;
            }
            return true;
        default:
            return false;
    }
}

const std::vector<Block> &Tetromino::getBlocks() const {
    return blocks;
}

int Tetromino::getType() const {
    return type;
}
