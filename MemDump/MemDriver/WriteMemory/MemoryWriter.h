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

NTSTATUS NameWriteRequest(PCHAR targetName, PVOID address, PVOID writeData, ULONG size);
NTSTATUS HandleWriteRequest(ULONG processId, PVOID address, PVOID writeData, ULONG size);