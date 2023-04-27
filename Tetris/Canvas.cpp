//
// Created by lyube on 4/25/2023.
//

#include <algorithm>
#include "Canvas.h"

Canvas::Canvas() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 20; ++j) {
            Coordinate coordinate(i, j);
            coordinates[coordinate] = true;
        }
    }
}

const RECT &Canvas::getRect() const {
    return rect;
}

void Canvas::setRect(const RECT &rect) {
    Canvas::rect = rect;
}

void Canvas::draw(HDC hdc) {
    HBRUSH hBrushFill = CreateSolidBrush(RGB(0, 0, 0));
    HBRUSH hBrushBorder = CreateSolidBrush(RGB(255, 255, 255));
    int borderSize = 2;

    RECT borderRect = this->rect;
    borderRect.bottom += borderSize;
    borderRect.left -= borderSize;
    borderRect.top -= borderSize;
    borderRect.right += borderSize;

    FillRect(hdc, &borderRect, hBrushBorder);
    FillRect(hdc, &this->rect, hBrushFill);

    DeleteObject(hBrushFill);
    DeleteObject(hBrushBorder);

    for (auto& block: this->blocks) {
        block.draw(hdc, *this);
    }
}

bool Canvas::isCoordinateFree(const Coordinate &coordinate) {
    return this->coordinates[coordinate];
}

void Canvas::addBlocks(const std::vector<Block>& blocks) {
    for (auto& block: blocks) {
        this->blocks.push_back(block);
        this->coordinates[block.getCoordinate()] = false;
    }
}

const std::vector<Block> &Canvas::getBlocks() const {
    return blocks;
}

int Canvas::breakLines() {
    int brokenLinesCount = 0;
    for (int i = 19; i >= 0; --i) {
        bool canBreak = true;
        for (int j = 0; j < 10; ++j) {
            Coordinate coordinate(j, i);
            if(coordinates[coordinate]) {
                canBreak = false;
            }
        }
        if(canBreak) {
            breakLine(i);
            i = 20;
            brokenLinesCount++;
        }
    }
    return brokenLinesCount;
}

void Canvas::breakLine(const int &i) {
    for (int j = 0; j < 10; ++j) {
        Coordinate coordinate(j, i);
        coordinates[coordinate] = true;
        auto it = std::find_if(blocks.begin(), blocks.end(), [j, i](const Block& block) {
            return block.getCoordinate().getX() == j && block.getCoordinate().getY() == i;
        });
        if (it != blocks.end()) {
            blocks.erase(it);
        }
    }

    // check for free coordinates in each row below the broken line
    for (int k = i - 1; k >= 0; --k) {
        for (int j = 0; j < 10; ++j) {
            auto it = std::find_if(blocks.begin(), blocks.end(), [j, k](const Block& block) {
                return block.getCoordinate().getX() == j && block.getCoordinate().getY() == k;
            });
            if (it != blocks.end()) {
                coordinates[it->getCoordinate()] = true;
                Coordinate newBlockCoordinate = Coordinate(it->getCoordinate());
                newBlockCoordinate.setY(newBlockCoordinate.getY() + 1);
                it->setCoordinate(newBlockCoordinate);
                coordinates[newBlockCoordinate] = false;
            }
        }
    }
}

Canvas::Canvas(RECT rect) {
    this->rect = rect;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 20; ++j) {
            Coordinate coordinate(i, j);
            coordinates[coordinate] = true;
        }
    }
}

