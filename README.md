<div align="justify">

# Game of life

![License](https://img.shields.io/github/license/leoraclet/cpp-skeleton)

This simple C / C++ program simulates the famous **Game of Life** which is a cellular automaton invented by Cambridge mathematician John Conway.

## Summary

* **[About](#about)**
  * [Rules](#rules)
* **[Build](#build)**
  * [Linux](#linux--macos)
  * [Windows](#windows)
* **[Libraries](#libraries)**
* **[License](#license)**
* **[Releases](#releases)**
* **[Credits](#credits)**

## About

This game became widely known when it was mentioned in an article published in 1970. It consists of a grid of cells which, based on a few mathematical rules, can live, die or multiply. Depending on the initial conditions, the cells form various patterns throughout the course of the game.

### Rules

There are only 4 simple rules to this game :
* **For a space that is populated**
  * Each cell with one or no neighbors dies, as if by solitude
  * Each cell with four or more neighbors dies, as if by overpopulation
  * Each cell with two or three neighbors survives
* **For a space that is empty of unpopulated**
  * Each cell with three neighbors becomes populated

In our case, the game is represented as a grid of cells, and we choose that a populated space is marked by a black cell, as opposite to a unpopulated space, marked by a white cell.

## Build

To build this project, you need to have CMake of Make installed depending on your system. Make the way to go if you are on Linux or MacOS, if you are on Windows, I recommend using CMake.

#### Linux / MacOS

Run the follwing commands in your terminal
```bash
$ git clone https://github.com/leoraclet/game-of-life
$ cd game-of-life/
$ make .
$ ./game-of-life
```

#### Windows

I can't guarantee that it will build the project properly on windows since I only tested it on Linux by now, so you're on your own this time.

## Libraries

- [**Dear ImGui**](https://github.com/ocornut/imgui) ~ Bloat-free Graphical User interface for C++ with minimal dependencies
- [**SDL**](https://github.com/libsdl-org/SDL) ~ Simple Directmedia Layer

## License

This project is released under the 
[**MIT**](https://github.com/leoraclet/cpp_skeleton/LICENSE)
license.

## Releases

To run the program without editing the source code or building
it yourself, go see the 
[**Releases**](https://github.com/leoraclet/cpp_skeleton/releases).

## Credits

* [**Léo Raclet**](https://github.com/leoraclet) : Creator of the project.
</div>