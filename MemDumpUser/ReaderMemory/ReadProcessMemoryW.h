#pragma once
#include <Windows.h>

BOOL ReadProcessMemoryW(const char* targetName, LPVOID address, LPVOID outBuffer, int size);
BOOL ReadProcessMemoryW(int pId, LPVOID address, LPVOID outBuffer, int size);