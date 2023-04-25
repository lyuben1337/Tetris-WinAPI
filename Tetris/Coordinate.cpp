//
// Created by lyube on 4/25/2023.
//

#include "Coordinate.h"

int Coordinate::getX() const {
    return x;
}

void Coordinate::setX(int x) {
    Coordinate::x = x;
}

int Coordinate::getY() const {
    return y;
}

void Coordinate::setY(int y) {
    Coordinate::y = y;
}

Coordinate::Coordinate(int x, int y) : x(x), y(y) {}

bool Coordinate::operator<(const Coordinate &other) const {
    if (x < other.x) {
        return true;
    }
    if (x > other.x) {
        return false;
    }
    return y < other.y;
}

Coordinate::Coordinate() = default;
