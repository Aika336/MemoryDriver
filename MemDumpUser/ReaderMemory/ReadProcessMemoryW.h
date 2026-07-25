#pragma once
#include <Windows.h>

bool ReadProcessMemoryW(const char* targetName, LPVOID address, LPVOID outBuffer, int size);
bool ReadProcessMemoryW(int pId, LPVOID address, LPVOID outBuffer, int size);