#pragma once
#include <Windows.h>

NTSTATUS WriteProcessMemoryW(const char* targetName, LPVOID targetAddress, LPVOID dataBuffer, int size);
NTSTATUS WriteProcessMemoryW(int pId, LPVOID targetAddress, LPVOID dataBuffer, int size);