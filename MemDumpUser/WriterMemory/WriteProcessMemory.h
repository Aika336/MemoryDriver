#pragma once
#include <Windows.h>

NTSTATUS ReadProcessMemoryW(const char* targetName, LPVOID targetAddress, LPVOID dataBuffer, int size);
NTSTATUS ReadProcessMemoryW(int pId, LPVOID targetAddress, LPVOID dataBuffer, int size);