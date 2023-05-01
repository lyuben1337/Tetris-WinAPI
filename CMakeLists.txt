cmake_minimum_required(VERSION 3.24)
project(Tetris_WinAPI)

if(WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0A00)
endif()
set(CMAKE_SYSTEM_VERSION 10.0)

set(CMAKE_EXE_LINKER_FLAGS "-static")

set(CMAKE_CXX_STANDARD 17)

add_executable(Tetris_WinAPI
        Tetris/main.cpp Tetris/TetrisWindow.h Tetris/TetrisWindow.cpp Tetris/Canvas.h Tetris/Functions.h Tetris/Coordinate.h Tetris/Coordinate.cpp Tetris/Canvas.cpp Tetris/Functions.cpp Tetris/Block.h Tetris/Tetromino.h Tetris/Block.cpp Tetris/Tetromino.cpp Tetris/Game.h Tetris/Game.cpp Tetris/HUD.h Tetris/HUD.cpp Tetris/Menu.h Tetris/Menu.cpp)

target_link_libraries(Tetris_WinAPI shcore.lib)