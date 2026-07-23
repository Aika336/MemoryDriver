#include "../header/driver.h"

NTSTATUS NameWriteRequest(PCHAR targetName, PVOID address, PVOID writeData, ULONG size);
NTSTATUS HandleWriteRequest(ULONG processId, PVOID address, PVOID writeData, ULONG size);