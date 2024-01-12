#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FRAME_HEIGHT 19         // Defining frame height.
#define FRAME_WIDTH 60          // Defining frame height.
#define CHART_HEIGHT 19         // Defining chart height.
#define CHART_WIDTH 37          // Defining chart width.
#define MAX_FILE_NAME_LENGTH 20 // Defining max file name length.

char folderPath[100] = "/Users/apple/Desktop/sudoku-HW/sudoku/sudoku-assignment/"; // Path of game folder.

void drawMenu(char frame[FRAME_HEIGHT][FRAME_WIDTH + 1], char (*menuOptions)[20], int numberOfOptions, char *heading); // This function draws the menu.
void gameMenu(char frame[FRAME_HEIGHT][FRAME_WIDTH + 1], char gameArr[9][9]);                                          // This function creates the game menu.
int playGame(char frame[FRAME_HEIGHT][FRAME_WIDTH + 1], char gameArr[9][9]);                                           // This function plays the game.
int readFile(char destinyArr[9][9], char *filePath, size_t lengthOfPath);                                              // This function reads the file.
void clearFrame(char frame[FRAME_HEIGHT][FRAME_WIDTH + 1]);                                                            // This function clears the frame
void printFrame(char frame[FRAME_HEIGHT][FRAME_WIDTH + 1]);                                                            // This function displays the frame.
void drawChart(char frame[FRAME_HEIGHT][FRAME_WIDTH + 1]);                                                             // This function creates the sudoku chart.
char getAndCheckOption(void);                                                                                          // This function gets and checks the option.
void clearscr(void);                                                                                                   // This function clears the screen.
void refreshGame(char frame[FRAME_HEIGHT][FRAME_WIDTH + 1], char gameArr[9][9]);                                       // This function refreshes the game.
char getAndCheckResponse();                                                                                            // This function gets and checks the user responds in game loop.
void saveGame(char gameArr[9][9]);                                                                                     // This function saves the game.
int placeNumber(char gameArr[9][9], char _CoordinatesXYAndNumber[3]);                                                  // This function places the number to the game array.
int isFinish(char gameArr[9][9]);                                                                                      // This function checks if the game is finished or not.

int main()
{
    char gameArr[9][9];                        // Initializing game array. This array will be used to store the game.
    char frame[FRAME_HEIGHT][FRAME_WIDTH + 1]; // Initializing frame.

    clearFrame(frame); // Clearing the frame.

    //============================================= Game Loop ==============================================
    while (1)
    {
        gameMenu(frame, gameArr); // Calling game menu function.
        playGame(frame, gameArr); // Calling play game function.
    }

    return 0;
}

void drawChart(char frame[FRAME_HEIGHT][FRAME_WIDTH + 1]) // This function creates the sudoku chart in frame array.
{
    size_t chartStartX = (FRAME_WIDTH - CHART_WIDTH) / 2;
    size_t chartStartY = 0;

    for (size_t y = 0; y < CHART_HEIGHT; y++)
    {
        for (size_t x = 0; x < CHART_WIDTH; x++)
        {
            if (((y % 2) == 1) && ((x % 12) == 0))
                frame[y + chartStartY][x + chartStartX] = '|';
            else if (((y % 2) == 0) && ((x % 4) == 0))
                frame[y + chartStartY][x + chartStartX] = '+';
            else if ((y % 6) == 0)
                frame[y + chartStartY][x + chartStartX] = '=';
            else if ((y % 2) == 0)
                frame[y + chartStartY][x + chartStartX] = '-';
            else if ((x % 4) == 0)
                frame[y + chartStartY][x + chartStartX] = ':';
            else
                frame[y + chartStartY][x + chartStartX] = ' ';
        }
    }
}

void printFrame(char frame[FRAME_HEIGHT][FRAME_WIDTH + 1]) // This function displays the frame.
{
    for (size_t y = 0; y < FRAME_HEIGHT; y++)
    {
        for (size_t x = 0; x < FRAME_WIDTH; x++)
        {
            printf("%c", frame[y][x]);
        }
        printf("\n");
    }
}

void clearscr(void) // This function clears the screen.
{
#ifdef _WIN32
    system("cls");

#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    system("clear");

#else
#error "OS not supported."
    print("error OS not supported");
#endif
}

void clearFrame(char frame[FRAME_HEIGHT][FRAME_WIDTH + 1]) // This function makes all the frame elements ' '.
{
    for (size_t y = 0; y < FRAME_HEIGHT; y++)
    {
        for (size_t x = 0; x < FRAME_WIDTH; x++)
        {
            frame[y][x] = ' ';
        }
    }
}

void gameMenu(char frame[FRAME_HEIGHT][FRAME_WIDTH + 1], char gameArr[9][9]) // Game menu function. It involves all about game menu.
{
    char menuOptions1[4][20] = {"Please Press", "1 - Play New Game", "2 - Load Game", "3 - Quit"}; // Menu options.
    char menuOptions2[3][20] = {"1 - Easy", "2 - Medium", "3 - Hard"};                             // Second menu options.
    char heading1[] = " Welcome to IZTECH Sudoku Game ";                                           // Heading of menu.
    char heading2[] = " Game Mode ";                                                               // Heading of second menu.
                                                                                                   //
    char *fileName = (char *)malloc(MAX_FILE_NAME_LENGTH * sizeof(char));                          // Initializing file name. This variable will be used to store the name of the file.
                                                                                                   //
    int isValid = 0;                                                                               // This variable will be used to check if the file name is valid or not.

    // ================================== MAIN MENU ==========================================
    clearscr();
    clearFrame(frame);
    drawMenu(frame, menuOptions1, 4, heading1); // Drawing first menu.
    printFrame(frame);                          // Printing first menu.

    char menuOption = getAndCheckOption(); // Getting and checking option.
    // ============================== End of the main menu. =====================================
    switch (menuOption)
    {
    case '1':
        // ================================== GAME MODE MENU =========================================
        clearFrame(frame);
        clearscr();
        drawMenu(frame, menuOptions2, 3, heading2); // Drawing second menu.
        printFrame(frame);                          // Printing second menu.
        menuOption = getAndCheckOption();           // Getting and checking option. If user enters an invalid option, it will ask again.

        switch (menuOption)
        {
        case '1':
            strcpy(fileName, "easy.txt");
            break;
        case '2':
            strcpy(fileName, "medium.txt");
            break;
        case '3':
            strcpy(fileName, "hard.txt");
            break;
        }

        char *myPath = malloc(strlen(folderPath) + strlen(fileName) + sizeof('/') + 1); // This string will be used to store the path of the file.
        strcpy(myPath, folderPath);                                                     // This line copies folder path to myPath variable.
        if (myPath[strlen(myPath) - 1] != '/')                                          // This line checks if the last character of the path is '/'.
            strcat(myPath, "/");                                                        // If myPath does not end with '/', this line adds '/' to the end of the path.
        strcat(myPath, fileName);                                                       // This line adds file name to the path.
                                                                                        //
        readFile(gameArr, myPath, strlen(myPath));                                      // This line checks the file name. If it is valid, reads the file.

        // ============================== End of the game mode menu. =====================================
        break;

    case '2': // Loading the game.

        while (isValid == 0)
        {
            printf("\nPlease enter the name of the file (Do not forget \".txt\" and do not use space): ");
            char *myPath = malloc(strlen(folderPath) + strlen(fileName) + sizeof('/') + 1); // This string will be used to store the path of the file.
            strcpy(myPath, folderPath);                                                     // This line copies folder path to myPath variable.
            if (myPath[strlen(myPath) - 1] != '/')                                          // If myPath does not end with '/', this line adds '/' to the end of the path.
                strcat(myPath, "/");                                                        //
                                                                                            //
            scanf("%19s", fileName);                                                        // Getting file name.
            strcat(myPath, fileName);                                                       // This line adds file name to the path.
            isValid = readFile(gameArr, myPath, strlen(myPath));                            // This line checks the file name. If it is valid, reads the file.
        }
        break;

    case '3': // Quitting the game.
        exit(0);
        break;
    }

    free(fileName); // Freeing the file name.
}

void drawMenu(char frame[FRAME_HEIGHT][FRAME_WIDTH + 1], char (*menuOptions)[20], int numberOfOptions, char *heading) // This function draws menu.
{
    // int menuHeight = sizeof(menuOptions) / sizeof(menuOptions[0]); // Height of menu.
    int menuHeight = numberOfOptions + 1; // Height of menu.
    int menuWidth = 57;                   // Width of menu. (Width was determined by the output from the homework pdf.)

    int headingLength = (int)strlen(heading); // This variable will be used to position the heading in the middle of the menu.

    int menuStartX = (FRAME_WIDTH - menuWidth) / 2;                     // This variable will be used to position the menu in the middle of the menu.
    int menuStartY = (FRAME_HEIGHT - menuHeight) / 2;                   // This variable will be used to position the menu in the middle of the menu.
    int headingStartX = ((menuWidth - headingLength) / 2) + menuStartX; // This variable will be used to position the heading in the middle of the menu.

    for (int x = 0; x < menuWidth; x++) // This loop creates the menu.
    {
        if ((x % 2) == 0)
        {
            frame[menuStartY][menuStartX + x] = '*';
            frame[menuStartY + menuHeight][menuStartX + x] = '*';
        }
        else
        {
            frame[menuStartY][menuStartX + x] = '-';
            frame[menuStartY + menuHeight][menuStartX + x] = '-';
        }
    }

    for (int i = headingStartX; i < (headingStartX + headingLength); i++)
    {
        frame[menuStartY][i] = heading[i - headingStartX];
    }

    for (int y = 1; y < menuHeight; y++)
    {
        int i = 0;
        frame[menuStartY + y][menuStartX] = '*';
        frame[menuStartY + y][menuStartX + menuWidth - 1] = '*';

        while (menuOptions[y - 1][i] != '\0')
        {
            frame[menuStartY + y][i + 24] = menuOptions[y - 1][i];
            i++;
        }
    }
}

char getAndCheckOption(void) // This function gets and checks the option.
{
    char _menuOption[10]; // This variable will be used to store the option.

    printf("Please enter your option: ");
    scanf("%9s", _menuOption); // Getting option.

    while ((strlen(_menuOption) != 1) || (_menuOption[0] < '1') || (_menuOption[0] > '3')) // Checking if the option is valid or not.
    {
        printf("Please enter a valid option: ");
        scanf("%s", _menuOption);
    }

    return _menuOption[0]; // Returning the option.
}

int readFile(char destinyArr[9][9], char *filePath, size_t lengthOfPath) // This function reads the file.
{
    if (filePath[lengthOfPath - 1] != 't' || filePath[lengthOfPath - 2] != 'x' || filePath[lengthOfPath - 3] != 't' || filePath[lengthOfPath - 4] != '.') // Checking if the file name does not end with ".txt".
    {
        printf("\nPlease do not forget \".txt\".\n");
        return 0;
    }

    FILE *file;                                       // This variable will be used to open the file.
    char *buffer = (char *)malloc(19 * sizeof(char)); // This a buffer array that will be used to store lines of the file.

    file = fopen(filePath, "r"); // Opening the file.

    if (file == NULL) // Checking if the file is opened or not.
    {
        printf("File could not be opened.\n");
        return 0;
    }

    int a = 0;                              // Line counter.
    while (fgets(buffer, 19, file) != NULL) // Reading the file line by line. When it reaches the end of the file, it will stop.
    {
        if (a == 9) // For safety.
            break;

        for (int x = 0; x < 9; x++) // This loop copies the line to the destiny array one by one.
            destinyArr[a][x] = buffer[2 * x];

        a++; // Increasing the line counter.
    }

    fclose(file); // Closing the file.

    free(buffer); // Freeing the buffer.
    return 1;
}

void refreshGame(char frame[FRAME_HEIGHT][FRAME_WIDTH + 1], char gameArr[9][9]) // This function refreshes the game.
{
    size_t chartStartX = (FRAME_WIDTH - CHART_WIDTH) / 2;   // This variable will be used to position the chart in the middle of the frame.
    size_t chartStartY = (FRAME_HEIGHT - CHART_HEIGHT) / 2; // This variable will be used to position the chart in the middle of the frame.

    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            if (gameArr[y][x] == '0') // If the element is '0', it will be printed as ' '.
                continue;
            frame[2 * y + 1][4 * x + 2 + chartStartX] = gameArr[y][x]; // This line prints the element to the frame.
        }
    }
}

int playGame(char frame[FRAME_HEIGHT][FRAME_WIDTH + 1], char gameArr[9][9]) // This function plays the game.
{
    char *printThem[7] = {"Row", "Column", "Number"};
    char _CoordinatesXYAndNumber[3]; // Saves the coordinates(index 0: X, index 1: Y) and number(index 3).
    char _ResponseBuffer;            // This variable will be used to store the response of the user.
    clearFrame(frame);               // SETUP FOR GAME
    drawChart(frame);                // SETUP FOR GAME

    // ============================================ GAME PLAY LOOP ============================================
    while (1)
    {
        clearscr();                  // Clearing the screen.
        refreshGame(frame, gameArr); // Refreshing the game.
        printFrame(frame);           // Printing the frame.

        for (int index = 0; index < 3; index++)
        {
            printf("\nPlease enter %s (1-9 or 'S'):", printThem[index]); // Getting response from user.

            _ResponseBuffer = getAndCheckResponse(); // Gets response to a buffer.

            if (_ResponseBuffer == 0) // Getting answer from user and checks if it is valid.
            {
                printf("\nPlease enter a valid %s", printThem[index]);
                index--;
                continue;
            }
            else if (_ResponseBuffer == ('S' - '0')) // Saving game
            {
                saveGame(gameArr); // This function saves the game.
                return 0;
            }
            else                                                  // Normal gaming process
                _CoordinatesXYAndNumber[index] = _ResponseBuffer; // If the response is valid, it will be saved to the _CoordinatesXYAndNumber array.
        }

        placeNumber(gameArr, _CoordinatesXYAndNumber); // Placing the number to the game array.

        if (isFinish(gameArr)) // Checking if the game is finished or not.
        {
            clearscr();                                                         // Clearing the screen.
            printf("\n\n\nCongratulations! You have finished the game!\n\n\n"); // If game is finished, this line will be printed.
            sleep(5);                                                           // When game is finished, it will wait 5 seconds and then it will return to the main menu.
            return 0;
        }
    }
    // ============================================ END OF GAME PLAY LOOP ============================================
    return 0;
}

char getAndCheckResponse() // The function
{
    char response[10];      // Declaring response array.
    scanf("%9s", response); // Getting response from user.

    if ((strlen(response) == 1) && (((response[0] >= '1') && (response[0] <= '9')) || (response[0] == 'S'))) // If response is valid,
        return response[0] - '0';                                                                            // returning value of response.(Value of 'S' will determining at play game function.)

    return 0; // If the response is invalid, function returns 0.
}

void saveGame(char gameArr[9][9]) // This function saves the game if
{
    FILE *file;

    printf("\nPlease enter the name of the file (Do not forget \".txt\" and do not use space): ");
    char *fileName = (char *)malloc(MAX_FILE_NAME_LENGTH * sizeof(char));           // Initializing file name. This variable will be used to store the name of the file.
    char *myPath = malloc(strlen(folderPath) + strlen(fileName) + sizeof('/') + 1); // This string will be used to store the path of the file.
    strcpy(myPath, folderPath);                                                     // This line copies folder path to myPath variable.
    if (myPath[strlen(myPath) - 1] != '/')                                          // If myPath does not end with '/', this line adds '/' to the end of the path.
        strcat(myPath, "/");                                                        //
                                                                                    //
    scanf("%19s", fileName);                                                        // Getting file name.
    strcat(myPath, fileName);                                                       // This line adds file name to the path.

    // ================================= Starting to Writing to File =================================
    file = fopen(myPath, "w");

    for (size_t row = 0; row < 9; row++) // This loop for writing sudoku values to file row by row.(We know that sudoku chart has 9 row.)
    {
        for (size_t index = 0; index < 9; index++) // This loop for writing sudoku values one by one.We know that sudoku chart has 9 columns.)
        {
            putc(gameArr[row][index], file); // This line puts the character to file.
            putc(' ', file);                 // This line puts space between the characters.
        }
        putc('\n', file); // To getting new row in file.
    }

    free(fileName); // Freeing the file name.
    free(myPath);   // Freeing the path.
}

int placeNumber(char gameArr[9][9], char _CoordinatesXYAndNumber[3]) // This function places the number to the game array.
{
    _CoordinatesXYAndNumber[1]--; //(X) This line is for converting coordinate to index of gameArr.
    _CoordinatesXYAndNumber[0]--; //(Y) This line is for converting coordinate to index of gameArr.

    char _number = _CoordinatesXYAndNumber[2] + '0';

    if (gameArr[_CoordinatesXYAndNumber[0]][_CoordinatesXYAndNumber[1]] != '0') // If cell is not empty.
    {
        printf("\nCell is not empty\n");
        return 0;
    }

    // ================================== Row and Column checking Part ==================================
    for (int i = 0; i < 9; i++) // Checking Row
    {
        if (_number == gameArr[_CoordinatesXYAndNumber[0]][i]) // If the number is already in the row, it will return 0.
        {

            printf("\nThe Row has same number!\n");
            return 0;
        }
        else if (_number == gameArr[i][_CoordinatesXYAndNumber[1]]) // If the number is already in the column, it will return 0.
        {

            printf("\nThe Column has same number!\n");
            return 0;
        }
    }
    // ================================== Sub-grid checking Part ==================================
    int sub_gridX = (_CoordinatesXYAndNumber[1] / 3) * 3;
    int sub_gridY = (_CoordinatesXYAndNumber[0] / 3) * 3;

    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (_number == gameArr[sub_gridY + j][sub_gridX + i]) // If the number is already in the sub-grid, it will return 0.
            {
                printf("\nThe Sub-grid has same number!\n");
                return 0;
            }
        }
    }
    gameArr[_CoordinatesXYAndNumber[0]][_CoordinatesXYAndNumber[1]] = _number; // If the number is not in the row, column and sub-grid, it will be placed to the game array.

    return 1;
}

int isFinish(char gameArr[9][9]) // If game is finished, this function returns 1.
{
    for (size_t row = 0; row < 9; row++)
    {
        for (size_t index = 0; index < 9; index++)
        {
            if (gameArr[row][index] == '0')
                return 0;
        }
    }
    return 1;
}
