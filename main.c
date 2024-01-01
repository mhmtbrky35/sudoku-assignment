#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FRAME_LENGTH 40 // Defining frame length
#define FRAME_WIDTH 50  // Defining frame length
#define CHART_LENGTH 19 // Defining chart length
#define CHART_WIDTH 37  // Defining chart width

void createChart(char frame[FRAME_LENGTH][FRAME_WIDTH + 1]); // This function creates the sudoku chart
void printFrame(char frame[FRAME_LENGTH][FRAME_WIDTH + 1]);  // This function displays the frame
void clearFrame(char frame[FRAME_LENGTH][FRAME_WIDTH + 1]);  // This function clears the frame
void gameMenu(char frame[FRAME_LENGTH][FRAME_WIDTH + 1]);    // This function creates the game menu
void clearscr(void);                                         // This function clears the screen

int main()
{
    char frame[FRAME_LENGTH][FRAME_WIDTH + 1]; // Initializing frame
    clearFrame(frame);
    gameMenu(frame);
    printFrame(frame);

    return 0;
}

void createChart(char frame[FRAME_LENGTH][FRAME_WIDTH + 1]) // This function creates the sudoku chart
{
    for (size_t y = 0; y < CHART_LENGTH; y++)
    {
        for (size_t x = 0; x < CHART_WIDTH; x++)
        {
            if (((y % 2) == 1) && ((x % 12) == 0))
                frame[y][x] = '|';
            else if (((y % 2) == 0) && ((x % 4) == 0))
                frame[y][x] = '+';
            else if ((y % 6) == 0)
                frame[y][x] = '=';
            else if ((y % 2) == 0)
                frame[y][x] = '-';
            else if ((x % 4) == 0)
                frame[y][x] = ':';
            else
                frame[y][x] = ' ';
        }
    }
}

void printFrame(char frame[FRAME_LENGTH][FRAME_WIDTH + 1]) // This function displays the chart.
{
    for (size_t y = 0; y < FRAME_LENGTH; y++)
    {
        for (size_t x = 0; x < FRAME_WIDTH; x++)
        {
            printf("%c", frame[y][x]);
        }
        printf("\n");
    }
}

void clearscr(void) // This function clears the screen
{
#ifdef _WIN32
    system("cls");

#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    system("clear");
// add some other OSes here if needed
#else
#error "OS not supported."
    print("error OS not supported");
#endif
}

void clearFrame(char frame[FRAME_LENGTH][FRAME_WIDTH + 1])
{
    for (size_t y = 0; y < FRAME_LENGTH; y++)
    {
        for (size_t x = 0; x < FRAME_WIDTH; x++)
        {
            frame[y][x] = ' ';
        }
    }
}

void gameMenu(char frame[FRAME_LENGTH][FRAME_WIDTH + 1])
{
    unsigned int menuLength = 6;
    unsigned int menuWidth = 30;

    char lx = '0';

    unsigned int menuStartX = (FRAME_WIDTH - menuWidth) / 2;
    unsigned int menuStartY = (FRAME_LENGTH - menuLength) / 2;

    clearFrame(frame);

    for (int y = 0; y < FRAME_LENGTH; y++)
    {
        frame[y][0] = '*';
        frame[y][FRAME_WIDTH - 1] = '*';
    }

    for (int y = 0; y < FRAME_WIDTH - 1; y++)
    {
        frame[0][y] = '*';
        frame[FRAME_LENGTH - 1][y] = '*';
    }

    for (unsigned int y = 0; y < menuLength; y++)
    {
        frame[menuStartY + y][menuStartX] = '*';
        frame[menuStartY + y][menuStartX + menuWidth] = '*';
    }

    for (unsigned int x = 0; x < menuWidth; x++)
    {
        frame[menuStartY][menuStartX + x] = '*';
        frame[menuStartY + menuLength][menuStartX + x] = '*';
    }
}