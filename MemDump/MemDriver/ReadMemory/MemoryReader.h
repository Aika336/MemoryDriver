#pragma once
#include "../header/driver.h"

NTSTATUS MmCopyVirtualMemory(
    PEPROCESS SourceProcess,
    PVOID SourceAddress,
    PEPROCESS TargetProcess,
    PVOID TargetAddress,
    SIZE_T BufferSize,
    KPROCESSOR_MODE PreviousMode,
    PSIZE_T ReturnSize
);

NTSTATUS NameReadRequest(PCHAR targetName, PVOID address, ULONG size, PVOID outBuffer);
NTSTATUS HandleReadRequest(ULONG pid, PVOID address, ULONG size, PVOID outBuffer);