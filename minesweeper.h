/******************************************** Libraries ***********************************************/

#include <stdio.h>    //Includes the standard I/O library for input/output operations
#include <stdlib.h>   //Includes the standard library for memory allocation and utilities
#include <stdbool.h>  //Includes the library for boolean data type (true/false)
#include <time.h>     //Includes the time library, used to seed random number generator

/******************************************************************************************************/



/********************************************* Structs ************************************************/

//Definition of the Cell structure to represent each cell on the Minesweeper board
typedef struct cell
{
    bool isMine;        //True if the cell contains a mine
    bool isRevealed;    //True if the cell has been revealed by the player
    bool isFlagged;     //True if the player has flagged the cell as a mine
    int nearbyMines;    //Number of mines in adjacent cells
} Cell;

//Definition of the Board structure to represent the entire Minesweeper board
typedef struct board
{
    Cell **cells;       //2D array of cells, representing the grid
    int size;           //Size of the board (e.g., 7x7, 10x10, etc.)
    int mineCount;      //Total number of mines on the board
} Board;

/******************************************************************************************************/



/********************************************* Prototypes *********************************************/

Cell **createBoard(int size);                      			//Dynamically create a 2D array of cells
void freeBoard(Cell **board, int size);            			//Free the dynamically allocated memory for the board
void initializeBoard(Board *board);                			//Initialize the board by setting default cell values
void placeMines(Board *board, int firstRow, int firstCol);  //Randomly place mines, avoiding the first cell selected
void calculateNearbyMines(Board *board);           			//Calculate the number of mines in adjacent cells for each cell
void printBoard(Board *board);                     			//Print the current state of the board to the console
void revealCell(Board *board, int row, int col);   			//Reveal a specific cell
void revealAdjacentCells(Board *board, int row, int col);   //Recursively reveal adjacent cells if there are no nearby mines
bool playTurn(Board *board);      			//Handle player input and play one turn of the game
void playFirstTurn(Board *board);
bool checkWin(Board *board);                       			//Check if the player has won by revealing all non-mine cells
int calculateMineCount(int size, float minePercentage); 	//Calculate the number of mines based on board size and percentage
Board selectDifficulty();                          			//Allow player to select difficulty and initialize the board

/******************************************************************************************************/