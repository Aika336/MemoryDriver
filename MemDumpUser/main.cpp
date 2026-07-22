#include <iostream>
#include <string>

#include <Windows.h>
#include <winternl.h>

#include "ReaderMemory/ReadProcessMemoryW.h"

int main() {
	int size;
	char name[] = "HackMe.exe";
	int arr[10];

	try {
		NTSTATUS status = ReadProcessMemoryW("HackMe.exe", (LPVOID)(0xF02492F810), (LPVOID)arr, 40);
		if (!NT_SUCCESS(status)) {
			std::cout << "Failed #1" << std::endl;
			std::cin >> size;
			return 1;
		}
	}
	catch (...) {
		std::cout << "Failed #2" << std::endl;
		std::cin >> size;
		return 1;
	}
	
	for (int i = 0; i < 10; i++) {
		std::cout << arr[i] << " ";
	}

	std::cin >> size;
	return 0;
}