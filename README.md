# Console Snake Game (C / ncurses)

A simple and dynamic "Snake" game written in pure C using the **ncurses** library for rendering graphics directly inside the terminal. The project features a modular structure and is fully optimized for dynamic terminal window resizing.

## Features

* **Intuitive Controls:** Move using the keyboard arrow keys, and return to the menu seamlessly by pressing `q` or upon hitting a Game Over.
* **Adaptive Interface:** Both the main menu and the game board windows automatically center themselves based on your real terminal size.
* **Main Menu:** A fully functional, interactive menu ("Start" / "Exit") with active option highlighting.
* **Clean Memory Management:** Built with manual memory allocation, ensuring data structures (the snake's tail) are completely freed up and cleared upon restart.

## Requirements

To build and run this project, you will need:
* A `gcc` or `clang` compiler (supporting C11/C23 standards)
* The `make` utility
* The `ncurses` development library

## Build & Run

Run the following commands in your terminal to compile and play the game:

```bash
# Build the project using the Makefile
make

# Run the game
./snake