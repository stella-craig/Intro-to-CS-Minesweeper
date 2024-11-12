#include "minesweeper.h"

void selectDifficulty()
{
    int difficulty, size = 0, mineCount = 0;

    printf("Select difficulty:\n");
    printf("1) Easy  (7x7 with 10%% mines)\n");
    printf("2) Medium  (10x10 with 15%% mines)\n");
    printf("3) Hard  (20x20 with 25%% mines)\n");
    printf("4) Custom\n");


    scanf("%d", &difficulty);

    switch (difficulty)
    {
        case 1: // Easy
            size = 7;
            mineCount = (int)(size * size * 0.10);
            printf("You chose the easy difficulty.\n");
            break;

        case 2: // Medium
            size = 10;
            mineCount = (int)(size * size * 0.15);
            printf("You chose the medium difficulty.\n");
            break;

        case 3: // Hard
            size = 20;
            mineCount = (int)(size * size * 0.25);
            printf("You chose the hard difficulty.\n");
            break;

        case 4: // Custom
            printf("Enter custom board size:\n");
            scanf("%d", &size);

            float minePercentage;
            printf("Enter the percentage of mines (as a decimal):\n");
            scanf("%f", &minePercentage);

            mineCount = (int)(size * size * minePercentage);
            break;

        default: // Defaults to Medium
			printf("Invalid selection. Defaulting to Medium.\n");
            size = 10;
            mineCount = (int)(size * size * 0.15);
            break;
    }
	
	Board board;
	board.size = size;
	board.mineCount = mineCount;
	board.cells = createBoard(size);

    return board;
	
}

Cell **createBoard(int size)
{
	// Implemented in November 12th Meeting
}


int main(void)
{
    selectDifficulty();
}