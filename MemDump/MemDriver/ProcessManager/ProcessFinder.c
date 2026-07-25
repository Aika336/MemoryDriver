#include "ProcessFinder.h"
#include "../../Math/math.h"

PEPROCESS FindProcessByName(PCHAR targetName) {
    const int pidDevider = 4;
    int maxProcessIdes = Exponent(2, 16);

    ANSI_STRING ansi;
    UNICODE_STRING targeNameUnicode;
    RtlInitAnsiString(&ansi, targetName);

    if (!NT_SUCCESS(RtlAnsiStringToUnicodeString(&targeNameUnicode, &ansi, TRUE))) {
        return NULL;
    }

    for (int i = pidDevider; i <= maxProcessIdes; i += pidDevider) {
        PEPROCESS candidate = NULL;

        NTSTATUS status = PsLookupProcessByProcessId((HANDLE)i, &candidate);
        if (!NT_SUCCESS(status)) {
            continue;
        }

        PUNICODE_STRING fullPath = NULL;
        status = SeLocateProcessImageName(candidate, &fullPath);

        if (NT_SUCCESS(status) && fullPath && fullPath->Length > 0) {
            UNICODE_STRING fileName = *fullPath;
            for (int j = fileName.Length / sizeof(WCHAR) - 1; j >= 0; j--) {
                if (fileName.Buffer[j] == L'\\') {
                    fileName.Buffer += (USHORT)(j + 1);
                    fileName.Length -= (USHORT)((j + 1) * sizeof(WCHAR));
                    break;
                }
            }

            if (RtlEqualUnicodeString(&targeNameUnicode, &fileName, TRUE)) {
                ExFreePool(fullPath);
                RtlFreeUnicodeString(&targeNameUnicode);
                return candidate;
            }
        }

        ExFreePool(fullPath);
        ObDereferenceObject(candidate);
    }

    RtlFreeUnicodeString(&targeNameUnicode);
    
    return NULL;
}