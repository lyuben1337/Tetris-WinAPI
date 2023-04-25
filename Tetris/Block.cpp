#include "Block.h"

Block::Block(int x, int y, int color) {
    coordinate.setX(x);
    coordinate.setY(y);
    this->color = color;
}

void Block::draw(HDC hdc, const Canvas& canvas) {
    HBRUSH hBrush = CreateBrush(this->color);
    int blockX = canvas.getRect().left + this->coordinate.getX() * BLOCK_SIZE;
    int blockY = canvas.getRect().top + this->coordinate.getY() * BLOCK_SIZE;
    RECT blockRect = { blockX + 1, blockY + 1, blockX + BLOCK_SIZE - 1, blockY + BLOCK_SIZE - 1 };
    FillRect(hdc, &blockRect, hBrush);
}

const Coordinate &Block::getCoordinate() const {
    return coordinate;
}

void Block::setCoordinate(const Coordinate &coordinate) {
    Block::coordinate = coordinate;
}
