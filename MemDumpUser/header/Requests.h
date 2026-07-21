#include <Windows.h>

#define MAX_PROCESS_NAME 15

typedef struct _READ_REQUEST {
	CHAR targetName[MAX_PROCESS_NAME];
	ULONG handle;
	ULONG_PTR  Address;
	ULONG Size;
} READ_REQUEST, * PREAD_REQUEST;