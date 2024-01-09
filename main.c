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
void drawChart(char frame[FRAME_HEIGHT][FRAME_WIDTH + 1]);                                                             // This function creates the sudoku chart.
void printFrame(char frame[FRAME_HEIGHT][FRAME_WIDTH + 1]);                                                            // This function displays the frame.
void clearFrame(char frame[FRAME_HEIGHT][FRAME_WIDTH + 1]);                                                            // This function clears the frame
void gameMenu(char frame[FRAME_HEIGHT][FRAME_WIDTH + 1], char gameArr[9][9], char fileName[MAX_FILE_NAME_LENGTH]);     // This function creates the game menu.
char getAndCheckOption(void);
void clearscr(void); // This function clears the screen.
int readFile(char destinyArr[9][9], char *filePath, size_t lengthOfPath);

int main()
{
    char frame[FRAME_HEIGHT][FRAME_WIDTH + 1]; // Initializing frame.
    char gameArr[9][9];                        // Initializing game array. This array will be used to store the game.

    clearscr();        // Calling clear screen function.
    clearFrame(frame); // Calling clear frame function.
    drawChart(frame);  // Calling create chart function.
    printFrame(frame); // Calling print frame function.

    char *fileName = (char *)malloc(MAX_FILE_NAME_LENGTH * sizeof(char)); // Initializing file name. This variable will be used to store the name of the file.
    gameMenu(frame, gameArr, fileName);                                   // Calling game menu function.

    // =========================== This part is for file name and file path. ===========================

    // printf("%s, %zu\n", myPath, strlen(myPath)); // This line prints the path of the file.(DEBUG)

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

void gameMenu(char frame[FRAME_HEIGHT][FRAME_WIDTH + 1], char gameArr[9][9], char fileName[MAX_FILE_NAME_LENGTH]) // Game menu function. It involves all about game menu.
{
    char menuOptions1[4][20] = {"Please Press", "1 - Play New Game", "2 - Load Game", "3 - Quit"}; // Menu options.
    char menuOptions2[3][20] = {"1 - Easy", "2 - Medium", "3 - Hard"};                             // Second menu options.
    char heading1[] = " Welcome to IZTECH Sudoku Game ";                                           // Heading of menu.
    char heading2[] = " Game Mode ";                                                               // Heading of second menu.

    int isValid = 0; // This variable will be used to check if the file name is valid or not.

    // ================================== MAIN MENU ==========================================
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
        menuOption = getAndCheckOption();           // Getting and checking option.
        clearscr();
        // ============================== End of the game mode menu. =====================================
        break;
    case '2': // Loading the game.

        while (isValid == 0)
        {
            printf("\nPlease enter the name of the file (Do not forget \".txt\" and do not use space): ");
            char *myPath = malloc(strlen(folderPath) + strlen(fileName) + sizeof('/') + 1); // This variable will be used to store the path of the file.
            strcpy(myPath, folderPath);                                                     // This line copies folder path to myPath variable.
            if (myPath[strlen(myPath) - 1] != '/')                                          // This line checks if the last character of the path is '/'.
                strcat(myPath, "/");

            scanf("%19s", fileName);                             // Getting file name.
            strcat(myPath, fileName);                            // This line adds file name to the path.
            isValid = readFile(gameArr, myPath, strlen(myPath)); // This line checks the file name. If it is valid, reads the file.
        }
        break;
    case '3': // Quitting the game.
        exit(0);
        break;
    }
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

    for (int x = 0; x < menuWidth; x++)
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
    char _menuOption[10];
    printf("Please enter your option: ");
    scanf("%9s", _menuOption);

    while ((strlen(_menuOption) != 1) || (_menuOption[0] < '1') || (_menuOption[0] > '3'))
    {
        printf("Please enter a valid option: ");
        scanf("%s", _menuOption);
    }

    return _menuOption[0];
}

int readFile(char destinyArr[9][9], char *filePath, size_t lengthOfPath) // This function reads the file.
{
    FILE *file;                                       // This variable will be used to open the file.
    char *buffer = (char *)malloc(19 * sizeof(char)); // This a buffer array that will be used to store lines of the file.

    file = fopen(filePath, "r"); // Opening the file.
    if (file == NULL)            // Checking if the file is opened or not.
    {
        printf("File could not be opened.\n");
        return 0;
    }

    // printf("file opened\n"); //FIXME: DEBUG

    int a = 0; // Line counter.
    while (fgets(buffer, 19, file) != NULL)
    {
        if (a == 9) // For safety.
            break;

        for (int x = 0; x < 9; x++)
        {
            destinyArr[a][x] = buffer[2 * x];
        }
        /*
        for (int i = 0; i < 9; i++)  // FIXME: This loop prints the array.(DEBUG)
        {
            printf("%c", destinyArr[a][i]);
        }
        a++;
        printf("\n");
        */
    }
    fclose(file); // Closing the file.

    free(buffer); // Freeing the buffer.
    return 1;
}
