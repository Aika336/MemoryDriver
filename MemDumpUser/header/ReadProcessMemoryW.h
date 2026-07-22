#include <Windows.h>

NTSTATUS ReadProcessMemoryW(char* targetName, LPVOID address, LPVOID outBuffer, int size);
NTSTATUS ReadProcessMemoryW(int pId, LPVOID address, LPVOID outBuffer, int size);