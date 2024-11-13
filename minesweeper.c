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
	Cell **board = (Cell **) malloc(size * sizeof(Cell*));

    for(int i = 0; i < size; i++)
    {
        board[i] = (Cell *) malloc(size * sizeof(Cell));
    }

    return board;
}

void freeBoard(Cell **board, int size)
{
    for(int i = 0; i < size; i++)
    {
        free(board[i]);
    }

    free(board);
}

void initializeBoard(Board *board)
{
    for(int i = 0; i < board -> size; i++)
    {
        for(int j = 0; j < board -> size; j++)
        {
            board -> cells[i][j].isMine = false;
            board -> cells[i][j].isRevealed = false;
            board -> cells[i][j].isFlagged = false;
            board -> cells[i][j].nearbyMines = 0;
        }
    }
}

void printBoard(Board *board) 
{
    printf("    ");  //Add extra spaces for alignment with two-digit column headers
    
    //Print the column headers (0, 1, 2, ..., size-1)
    for (int i = 0; i < board -> size; i++) 
    {
        printf("%2d ", i);  //Print each column number with 2-character width
    }
    
    printf("\n   +");  //Start the separator line below the column headers
    
    for (int i = 0; i < board -> size; i++) 
    {
        printf("---");  //Print a separator line matching the column width
    }
    
    printf("\n");

    //Print each row of the board
    for (int i = 0; i < board -> size; i++) 
    {
        printf("%2d |", i);  //Print the row number with 2-character width followed by a pipe
        
        for (int j = 0; j < board -> size; j++) 
        {
            //Print the cell based on its state (revealed, flagged, or hidden)
            if (board -> cells[i][j].isRevealed) 
            {
                if (board -> cells[i][j].isMine) 
                {
                    printf(" * ");  //If the cell contains a mine, print '*'
                } 
                
                else 
                {
                    printf(" %d ", board -> cells[i][j].nearbyMines);  //Otherwise, print the number of nearby mines
                }
                
            } 
            
            else if (board -> cells[i][j].isFlagged) 
            {
                printf(" F ");  //Print 'F' for flagged cells
            } 
            
            else 
            {
                printf(" . ");  //Print '.' for unrevealed cells
            }
        }
        
        printf("\n");  //Move to the next row
    }
}

void placeMines(Board *board, int firstRow, int firstCol)
{
    srand(time(NULL));
    int placedMines = 0;

    while (placedMines < board -> mineCount)
    {
        int row = rand() % board -> size;
        int col = rand() % board -> size;

        if((row == firstRow && col == firstCol) || board -> cells[row][col].isMine)
        {
            continue;
        }

        board -> cells[row][col].isMine = true;
        placedMines++;
    }

}

void calculateNearbyMines(Board *board)
{
    int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};  //Row offsets to check 8 neighboring cells
    int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};  //Column offsets to check 8 neighboring cells

    // loop through rows
    for(int i = 0; i < board -> size; i++)
    {
        // loop through columns
        for(int j = 0; j < board -> size; j++)
        {
            if(board -> cells[i][j].isMine)
            {
                continue;
            }

            int minesCount = 0;
            
            // loop through surrounding cells
            for(int k = 0; k < 8; k++)
            {
                int newRow = i + dx[k];
                int newCol = j + dy[k];
            }
        }
    }
}


int main(void)
{
    selectDifficulty();
}