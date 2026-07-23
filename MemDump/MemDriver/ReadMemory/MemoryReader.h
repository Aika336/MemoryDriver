#pragma once
#include "../header/driver.h"

NTSTATUS NameReadRequest(PCHAR targetName, PVOID address, ULONG size, PVOID outBuffer);
NTSTATUS HandleReadRequest(ULONG pid, PVOID address, ULONG size, PVOID outBuffer);