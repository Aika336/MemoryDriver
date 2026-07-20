#include "DeviceRaii.h"

DeviceRaii::DeviceRaii() {
	hDevice = CreateFileW(
		DeviceSymbolicName,
		GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, 0, NULL
	);
}