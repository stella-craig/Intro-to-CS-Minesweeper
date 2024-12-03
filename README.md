# Minesweeper in C - Intro to CS Org

Welcome to the **Minesweeper in C** project! This program is a recreation of the classic Minesweeper game, designed to run in the terminal. It is written in C and developed by members of the **Intro to CS Special Interest Group through the Mizzou Computing Association**, a group dedicated to teaching computer science fundamentals to college freshmen. This group is led by [Stella Craig](https://github.com/stella-craig) and [Andrew Klusmeyer](https://github.com/andrewklusmeyer).

## Features
- **Customizable Difficulty Levels**: Choose from Easy, Medium, Hard, or define your own custom grid size and mine percentage.
- **Dynamic Memory Management**: Efficiently allocates and deallocates memory for the game board.
- **Randomized Mines**: Mines are placed randomly, avoiding the first tile clicked.
- **Nearby Mines Calculation**: Displays the number of mines adjacent to revealed tiles.
- **Intuitive Terminal Display**: Clearly shows revealed tiles, hidden tiles, flagged tiles, and mines.
- **Win/Loss Detection**: Automatically determines if the player has won or lost.

## How to Play
The objective is to clear the board without detonating any mines. Use logic to deduce the location of mines based on the numbers displayed on revealed tiles. Mark suspected mines to avoid uncovering them accidentally.

### Controls
1. **Reveal a Tile**: Enter the row and column of the tile you want to uncover.
2. **Flag/Unflag a Tile**: Mark tiles suspected to contain mines.
3. **Quit the Game**: Exit the program at any time by typing the quit command.

### Rules
- Numbers on revealed tiles indicate how many mines are adjacent to that tile.
- Use these clues to deduce the location of mines.
- The game ends when:
  - All non-mine tiles are revealed (win).
  - A mine is revealed (loss).

## Compilation and Execution
1. Make sure you have a C compiler (e.g., `gcc`) installed on your system.
2. Clone or download the project files.
3. Compile the program using the following command:
```gcc minesweeper.c```
4. Run the program:
```./a.out```

## Code Highlights
### 1. Difficulty Selection
The program allows you to select a difficulty level:
- Easy (7x7 with 10% mines)
- Medium (10x10 with 15% mines)
- Hard (20x20 with 25% mines)
- Custom (define your own grid size and mine percentage)

If an invalid selection is made, the program defaults to Medium difficulty.

### 2. Dynamic Memory Allocation
The game dynamically allocates memory for the game board to efficiently handle different board sizes. This ensures optimal use of system resources.

### 3. Mine Placement Logic
Mines are placed randomly across the board, ensuring the first tile clicked is never a mine. This improves the player experience by avoiding immediate losses.

### 4. Nearby Mines Calculation
The program calculates the number of mines adjacent to each cell using an 8-directional algorithm. This information is used to display numbers on revealed tiles.

### 5. Board Display
The terminal display includes:
- Hidden tiles: `.` 
- Flagged tiles: `F`
- Revealed tiles:
  - Numbers (`1`, `2`, etc.) indicating nearby mines
  - `*` to indicate a mine if revealed

## Project Goals
- Introduce freshmen to key programming concepts in C, such as:
  - Dynamic memory management
  - Structs for data organization
  - Functions and modular design
  - Random number generation
  - User input handling
- Foster teamwork and problem-solving skills through collaborative coding.
- Encourage logical thinking and debugging practices.

## Acknowledgments
This project was created by the **Intro to CS SIG at Mizzou** as part of our mission to make computer science accessible and engaging for beginners. Special thanks to all club members for their hard work and contributions.
