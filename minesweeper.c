#include "minesweeper.h"

// Function to select difficulty level and set up the board size and number of mines
Board selectDifficulty()
{
    int difficulty, size = 0, mineCount = 0;

    // Prompt the user to choose a difficulty level
    printf("Select difficulty:\n");
    printf("1) Easy  (7x7 with 10%% mines)\n");
    printf("2) Medium  (10x10 with 15%% mines)\n");
    printf("3) Hard  (20x20 with 25%% mines)\n");
    printf("4) Custom\n");

    // Read the user's input for difficulty level
    scanf("%d", &difficulty);

    // Set up the board parameters based on the difficulty level
    switch (difficulty)
    {
        case 1: // Easy
            size = 7; // 7x7 grid
            mineCount = (int)(size * size * 0.10); // 10% mines
            printf("You chose the easy difficulty.\n");
            break;

        case 2: // Medium
            size = 10; // 10x10 grid
            mineCount = (int)(size * size * 0.15); // 15% mines
            printf("You chose the medium difficulty.\n");
            break;

        case 3: // Hard
            size = 20; // 20x20 grid
            mineCount = (int)(size * size * 0.25); // 25% mines
            printf("You chose the hard difficulty.\n");
            break;

        case 4: // Custom settings
            printf("Enter custom board size:\n");
            scanf("%d", &size);

            float minePercentage;
			while(true)
			{
				printf("Enter the percentage of mines (as a decimal):\n");
				scanf("%f", &minePercentage);
				if(minePercentage < 1 && minePercentage > 0)
				{
					break;
				}
				else
				{
					printf("Invalid value. Must be between 0 and 1. Please try again.\n");
				}
			}

            mineCount = (int)(size * size * minePercentage);
            break;

        default: // Invalid selection defaults to Medium
            printf("Invalid selection. Defaulting to Medium.\n");
            size = 10;
            mineCount = (int)(size * size * 0.15);
            break;
    }
    
    // Create and initialize the board
    Board board;
    board.size = size;
    board.mineCount = mineCount;
    board.cells = createBoard(size);

    return board; // Return the configured board
}

// Function to allocate memory for the game board
Cell **createBoard(int size)
{
    Cell **board = (Cell **) malloc(size * sizeof(Cell*)); // Allocate memory for rows

    for (int i = 0; i < size; i++)
    {
        board[i] = (Cell *) malloc(size * sizeof(Cell)); // Allocate memory for columns in each row
    }

    return board;
}

// Function to free allocated memory for the board
void freeBoard(Cell **board, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(board[i]); // Free each row
    }

    free(board); // Free the array of row pointers
}

// Function to initialize the board cells
void initializeBoard(Board *board)
{
    for (int i = 0; i < board->size; i++)
    {
        for (int j = 0; j < board->size; j++)
        {
            board->cells[i][j].isMine = false;      // No mines initially
            board->cells[i][j].isRevealed = false; // All cells are hidden
            board->cells[i][j].isFlagged = false;  // No cells are flagged
            board->cells[i][j].nearbyMines = 0;    // No nearby mines initially
        }
    }
}

// Function to display the game board in the terminal
void printBoard(Board *board)
{
	printf("\033[2J\033[1;1H");
    printf("    "); // Extra spaces for alignment with column headers
    
    // Print column headers (0, 1, ..., size-1)
    for (int i = 0; i < board->size; i++)
    {
        printf("%2d ", i);
    }
    printf("\n   +");
    
    // Print horizontal separator line
    for (int i = 0; i < board->size; i++)
    {
        printf("---");
    }
    printf("\n");

    // Print each row of the board
    for (int i = 0; i < board->size; i++)
    {
        printf("%2d |", i); // Row number followed by a separator
        
        for (int j = 0; j < board->size; j++)
        {
            // Print cell state
            if (board->cells[i][j].isRevealed)
            {
                if (board->cells[i][j].isMine)
                {
                    printf(" * "); // Mine
                }
                else
                {
                    printf(" %d ", board->cells[i][j].nearbyMines); // Number of nearby mines
                }
            }
            else if (board->cells[i][j].isFlagged)
            {
                printf(" F "); // Flagged cell
            }
            else
            {
                printf(" . "); // Hidden cell
            }
        }
        printf("\n");
    }
}

// Function to randomly place mines on the board
void placeMines(Board *board, int firstRow, int firstCol)
{
    srand(time(NULL)); // Seed for random number generation
    int placedMines = 0;

    // Place mines until the desired count is reached
    while (placedMines < board->mineCount)
    {
        int row = rand() % board->size;
        int col = rand() % board->size;

        // Avoid placing a mine at the first clicked cell or overwriting an existing mine
        if ((row == firstRow && col == firstCol) || board->cells[row][col].isMine)
        {
            continue;
        }

        board->cells[row][col].isMine = true;
        placedMines++;
    }
}

// Function to calculate the number of nearby mines for each cell
void calculateNearbyMines(Board *board)
{
    int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0}; // Row offsets for 8 neighbors
    int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1}; // Column offsets for 8 neighbors

    // Loop through all cells
    for (int i = 0; i < board->size; i++)
    {
        for (int j = 0; j < board->size; j++)
        {
            if (board->cells[i][j].isMine)
            {
                continue; // Skip mine cells
            }

            int minesCount = 0;

            // Check all 8 neighboring cells
            for (int k = 0; k < 8; k++)
            {
                int newRow = i + dx[k];
                int newCol = j + dy[k];

                // Ensure the neighbor is within bounds and contains a mine
                if (newRow >= 0 && newRow < board->size && newCol >= 0 && newCol < board->size && board->cells[newRow][newCol].isMine)
                {
                    minesCount++;
                }
            }

            board->cells[i][j].nearbyMines = minesCount; // Update nearby mines count
        }
    }
}

void revealCell(Board *board, int row, int col)
{
    // Checks for revealed and flagged cells
    if(board -> cells[row][col].isRevealed || board -> cells[row][col].isFlagged)
    {
        return;
    }

    board -> cells[row][col].isRevealed = true; //Marks cell as revealed

    //If mine, return with no action (come back to)
    if(board -> cells[row][col].isMine)
    {
        return;
    }

    if(board -> cells[row][col].nearbyMines == 0)
    {
        revealAdjacentCells(board, row, col);
    }

}

void revealAdjacentCells(Board *board, int row, int col)
{
        int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0}; // Row offsets for 8 neighbors
        int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1}; // Column offsets for 8 neighbors

        for(int i = 0; i < 8; i++)
        {
            int newRow = row + dx[i];
            int newCol = col + dy[i];

            if (newRow >= 0 && newRow < board -> size && newCol >= 0 && newCol < board -> size && !board -> cells[newRow][newCol].isRevealed) 
            {
                revealCell(board, newRow, newCol);
            }
        }       
}

void playFirstTurn(Board *board) {
    int row, col;
    bool data1 = true;

    // ask for col and row until valid
    while(data1){
        printf("Enter row and column (row col): ");
        scanf("%d %d", &row, &col);

        if(row < 0 || row >= board -> size || col < 0 || col >= board -> size)
        {
            printf("Invalid coordinates! Try again!\n");
            break;
        }
        else{
            data1 = false;
        }
    }

    // Will now set up board and reveal given cell
    placeMines(board, row, col);
    calculateNearbyMines(board);
    
    // reveal cells
    revealCell(board, row, col);
    
    return;
}

// returns bool
// true means game continues
// false means game over
bool playTurn(Board *board)
{
    int row, col;
    char action;
    bool data1 = true;
    bool data2 = true;

    // ask for col and row until valid
    while(data1){
        printf("Enter row and column (row col): ");
        scanf("%d %d", &row, &col);

        if(row < 0 || row >= board -> size || col < 0 || col >= board -> size)
        {
            printf("Invalid coordinates! Try again!\n");
            break;
        }
        else{
            data1 = false;
        }
    }

    // ask for the action until valid
    while(data2){
        printf("Enter action (r for reveal, f for flag): ");
        scanf(" %c", &action);

        if(action == 'r' || action == 'f'){
            data2 = false;
        }
        else{
            printf("Invalid selection. Try again!\n");
        }
    }

    // Handle player's action
    // If they chose reveal...
    if(action == 'r'){
        // is it flagged?
        // cannot reveal it
        if(board -> cells[row][col].isFlagged) {
            return true;
        }

        // is it a mine?
        else if(board -> cells[row][col].isMine){
            printf("Uh oh! You hit a mine! That's a game over!\n");
            return false;
        }

        // reveal that cell
        else{
            revealCell(board, row, col);
        }
    }

    // If they chose flag...
    else if(action == 'f'){
        // is it already flagged?
        // if yes, unflag it
        if(board->cells[row][col].isFlagged){
            board->cells[row][col].isFlagged = false;
            return true;
        }

        // if no, flag it
        else{
            board-> cells[row][col].isFlagged = true;
            return true;
        }
    }

    // continue game
    return true;
}

// Check win function
bool checkWin(Board * board)
{
    int revealedCells = 0;

    for(int i = 0; i < board -> size; i++)
    {
        for(int j = 0; j < board -> size; j++)
        {
            if(board -> cells[i][j].isRevealed && !board -> cells[i][j].isMine)
            {
                revealedCells++;
            }
        }
    }

    return (revealedCells == (board -> size) * (board -> size) - (board -> mineCount));
}

// Main function to start the game
int main(void)
{
    
    Board board = selectDifficulty(); // Prompt user for difficulty and set up the board
    initializeBoard(&board);
    bool gameOver = false;


    // first play
    playFirstTurn(&board);

    // while loop of regualr plays until game over
    while(!gameOver)
    {
        printBoard(&board);
        gameOver = !playTurn(&board);

        if(checkWin(&board))
        {
            printf("Congrats! You won!\n");
            break;
        }
    }

    // inside loop check if there was a win

    // free board
    freeBoard(board.cells, board.size);
    return 0;
}