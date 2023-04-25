cmake_minimum_required(VERSION 3.24)
project(Tetris_WinAPI)

set(CMAKE_CXX_STANDARD 14)

add_executable(Tetris_WinAPI
        Tetris/main.cpp Tetris/TetrisWindow.h Tetris/TetrisWindow.cpp Tetris/Canvas.h Tetris/Functions.h Tetris/Coordinate.h Tetris/Coordinate.cpp Tetris/Canvas.cpp Tetris/Functions.cpp)
