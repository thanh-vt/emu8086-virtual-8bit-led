#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include"io.h"

void print_led_line(int val, HANDLE hConsole);

int extract_bit(int num, int bit_position);

void clear_screen();

int main() {
    // you can loop k higher to see more color choices
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0 , 0 , 30 , 5}; //change the values
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    // PCONSOLE_SCREEN_BUFFER_INFO* bufferInfo;
    // GetConsoleScreenBufferInfo(hConsole, bufferInfo);

    COORD coord = { 10, 10};
    SetConsoleScreenBufferSize(hConsole, coord);
    while (1) {
        const unsigned char val = READ_IO_BYTE(0x2C0);
        print_led_line(val, hConsole);
    }
    return 0;
}

void print_led_line(int val, HANDLE hConsole) {
    for (int j = 7; j >= 0; j--) {
        const int i = extract_bit(val, j);
        if (i == 0) {
            SetConsoleTextAttribute(hConsole, 160);
            printf("  |");
        } else {
            SetConsoleTextAttribute(hConsole, 120);
            printf("  |");
        }
    }
    SetConsoleTextAttribute(hConsole, 0);
    Sleep(100);
    clear_screen(hConsole);
    // system("cls");
}

int extract_bit(int num, int bit_position) {
    // Binary: 01100111
    // Extracting the 5th bit (0-based index)
    // Create a mask with only the 5th bit set to 1
    int mask = 1 << bit_position;
    // Extract the bit using AND and right shift
    return (num & mask) >> bit_position;
}

void clear_screen(HANDLE hStdOut) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    COORD homeCoords = {0, 0};

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR) ' ',
        cellCount,
        homeCoords,
        &count
    ))
        return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    ))
        return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}
