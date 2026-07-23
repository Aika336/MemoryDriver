#pragma once
#include <ntifs.h>

NTKERNELAPI
PCHAR
PsGetProcessImageFileName(
    _In_ PEPROCESS Process
);

PEPROCESS FindProcessByName(PCHAR targetName);