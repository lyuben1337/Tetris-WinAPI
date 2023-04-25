//
// Created by lyube on 4/25/2023.
//

#ifndef TETRIS_WINAPI_COORDINATE_H
#define TETRIS_WINAPI_COORDINATE_H



class Coordinate {
public:
    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    Coordinate(int x, int y);

    bool operator<(const Coordinate& other) const;

private:
    int x;
    int y;
};


#endif //TETRIS_WINAPI_COORDINATE_H
