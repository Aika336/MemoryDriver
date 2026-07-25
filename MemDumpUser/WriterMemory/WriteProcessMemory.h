#pragma once
#include <Windows.h>

bool WriteProcessMemoryW(const char* targetName, LPVOID targetAddress, LPVOID dataBuffer, int size);
bool WriteProcessMemoryW(int pId, LPVOID targetAddress, LPVOID dataBuffer, int size);