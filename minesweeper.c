#include "minesweeper.h"

// Function to select difficulty level and set up the board size and number of mines
void selectDifficulty()
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
            printf("Enter the percentage of mines (as a decimal):\n");
            scanf("%f", &minePercentage);

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

// Main function to start the game
int main(void)
{
    selectDifficulty(); // Prompt user for difficulty and set up the board
    return 0;
}
