#pragma once

#include <windows.h>

#define C_BLACK 0x0
#define C_BLUE 0x1
#define C_GREEN 0x2
#define C_RED 0x4
#define C_LIGHT 0x8
#define C_WHITE 0xf

extern HANDLE hConsole;

void SetConsoleColor(int foreground = C_RED | C_GREEN | C_BLUE, int background = C_BLACK);