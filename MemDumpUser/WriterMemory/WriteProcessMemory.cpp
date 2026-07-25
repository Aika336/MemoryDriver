#include "WriteProcessMemory.h"

#include "../Driver/DeviceRaii.h"
#include "../Driver/IoCtlCodes.h"
#include "../Driver/Requests.h"

#include <stdexcept>
#include <ntstatus.h>

bool WriteProcessMemoryW(const char* targetName, LPVOID targetAddress, LPVOID dataBuffer, int size) {
	if (!targetName || !targetAddress || !dataBuffer || size < 0 || strlen(targetName) <= 0) {
		throw std::invalid_argument("Invalid parameters passed to WriteProcessMemoryW");
	}

	DeviceRaii device;

	WRITE_REQUEST request{(char*)targetName , NULL, (ULONG_PTR)targetAddress, (ULONG_PTR)dataBuffer, size};

	DWORD bytesRet;

	BOOL state = DeviceIoControl(
		device.hDevice,
		CTL_WRITE_MEMORY_BY_NAME,
		&request, sizeof(request),
		NULL, 0,
		&bytesRet,
		NULL
	);

	return state;
}

bool WriteProcessMemoryW(int processId, LPVOID targetAddress, LPVOID dataBuffer, int size) {
	if (!targetAddress || !dataBuffer || processId < 4 || size < 0) {
		throw std::invalid_argument("Invalid parameters passed to WriteProcessMemoryW");
	}

	DeviceRaii device;

	WRITE_REQUEST request{ NULL , processId, (ULONG_PTR)targetAddress, (ULONG_PTR)dataBuffer, size };

	DWORD bytesRet;

	BOOL state = DeviceIoControl(
		device.hDevice,
		CTL_WRITE_MEMORY_BY_HANDLE,
		&request, sizeof(request),
		NULL, 0,
		&bytesRet,
		NULL
	);

	return state;
}