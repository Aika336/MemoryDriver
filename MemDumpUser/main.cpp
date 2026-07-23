#include <iostream>
#include <string>

#include <Windows.h>
#include <winternl.h>

#include "ReaderMemory/ReadProcessMemoryW.h"
#include "WriterMemory/WriteProcessMemory.h"

int main() {
	int size;
	char name[] = "HackMe.exe";
	int arr[10];

	LPVOID address = (LPVOID)0xD6FE2FFD40;

	try {
		NTSTATUS status = ReadProcessMemoryW("HackMe.exe", address, (LPVOID)arr, 40);
		if (!NT_SUCCESS(status)) {
			std::cout << "Failed #1" << std::endl;
			std::cin >> size;
			return 1;
		}

		arr[2] = 228;

		status = WriteProcessMemoryW("HackMe.exe", address, (LPVOID)(arr+2), 4);
		if (!NT_SUCCESS(status)) {
			std::cout << "Failed #3" << std::endl;
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