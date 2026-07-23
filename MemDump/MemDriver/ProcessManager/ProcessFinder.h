#include <ntddk.h>

NTKERNELAPI
PCHAR
PsGetProcessImageFileName(
    _In_ PEPROCESS Process
);

PEPROCESS FindProcessByName(UCHAR targetName);