#include "Color.hpp"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void SetConsoleColor(int foreground, int background)
{
    SetConsoleTextAttribute(hConsole, foreground + background * 16);
}
