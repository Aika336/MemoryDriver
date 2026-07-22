#pragma once
#include "driver.h"

NTKERNELAPI
PCHAR
PsGetProcessImageFileName(
    _In_ PEPROCESS Process
);

NTSTATUS NameReadRequest(PCHAR targetName, PVOID address, ULONG size, PVOID outBuffer);
NTSTATUS HandleReadRequest(ULONG pid, PVOID address, ULONG size, PVOID outBuffer);