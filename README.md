# Tetris Game

This project focuses on creating a "Tetris" game using the WinAPI library and the C++ programming language. The project utilizes WinAPI functions for graphics and window manipulation. Standard C++ library containers such as `std::map` and `std::vector` are used for storing coordinates. The program is developed using both object-oriented and functional approaches.

Here are some screenshots of the Tetris game:

![Gameplay](https://github.com/lyuben1337/Tetris-WinAPI/assets/114613085/4877ba96-4095-4253-9bfc-db9b1210d88d)

![Menu](https://github.com/lyuben1337/Tetris-WinAPI/assets/114613085/c168b2cb-05a0-491f-92d8-cacfc711d1a5)

## Program Structure

The program follows a hierarchical class structure. At the top level of the hierarchy is the `TetrisWindow` class, which represents the game window. Below that, we have the `Canvas`, `Game`, `Tetromino`, `Block`, and `HUD` classes.

- The `Canvas` class handles the creation and updating of the game field. It includes functions for checking free coordinates, adding blocks to the field, and removing rows if they exist.

- The `Game` class is responsible for initializing the game and tracking its state (e.g., whether the game is over). It includes functions for changing the game difficulty and updating the player's score.

- The `Tetromino` class handles the creation, movement, and rotation of the Tetris pieces. It contains methods for checking the possibility of moving the piece in a certain direction and rotating it.

- The `Block` class represents each individual block on the game field. It stores the block's coordinates and color.

- The `HUD` (Head-Up Display) class displays information about the game time, the next piece, and the player's score.

- The `Menu` class is responsible for displaying the game menu, where the player can change the game difficulty, view the instructions, and so on.

All classes interact with each other to ensure the correct functioning of the game. For example, the `Tetromino` class creates blocks that are then added to the game field (Canvas), and the `Game` class monitors the game state and increases the player's score if a row is cleared.

Additionally, the program includes `Functions.h` and `Functions.cpp` files, which contain additional functions for the proper operation of the program.

The program also utilizes timers to update the screen state, allowing for instant game graphics updates and the movement of pieces downward at regular intervals.

## Tetris Game Algorithm

The algorithm for the "Tetris" game works as follows:

1. Upon launching the program, the main game window and menu with game parameters are created.
2. When the player selects the start option from the menu, a game object (Game class) is created with default difficulty parameters.
3. The game begins by creating a Tetromino object, which consists of 4 blocks (Block class) of random shape.
4. Each block has (x, y) coordinates and a color property. The coordinates are defined on a field consisting of equally sized squares. The top-left point of this field has coordinates (0, 0), and the bottom-right point has coordinates (10, 20).
5. The Tetromino object moves downward on the field at a certain speed determined by the game difficulty. If a block reaches the bottom boundary of the field or collides with another block, it remains in place, and a new Tetromino object is generated.
6. The player can control the movement of the blocks using the arrow keys (left and right) and the down key for fast downward movement. The block can also be rotated 90 degrees clockwise using the "SPACE" key.
7. If complete lines are formed as a result of block placement, they are cleared, and all blocks above them move down by the corresponding number of rows, and the player's score increases by 1.
8. The game ends when a new block cannot be placed on the field or when the player presses the ESC key.

To ensure proper program execution, the user must have a Windows XP or newer operating system. The recommended monitor resolution is 1920x1080.
