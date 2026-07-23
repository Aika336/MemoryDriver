#include "../header/driver.h"
#include "../ReadMemory/MemoryReader.h"
#include "../WriteMemory/MemoryWriter.h"

#define DEVICE_NAME L"\\Device\\MemReader"
#define SYMLINK_NAME L"\\DosDevices\\MemReader"

NTSTATUS DispatchDeviceControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    UNREFERENCED_PARAMETER(DeviceObject);

    PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
    NTSTATUS status = STATUS_UNSUCCESSFUL;
    ULONG_PTR bytesReturned = 0;

    ULONG ioctl = stack->Parameters.DeviceIoControl.IoControlCode;
    ULONG inLen = stack->Parameters.DeviceIoControl.InputBufferLength;
    ULONG outLen = stack->Parameters.DeviceIoControl.OutputBufferLength;

    switch (ioctl)
    {
    case IOCTL_READ_MEMORY_BY_HANDLE:   // Read memory in a target process by name of process
    {
        if (inLen != sizeof(READ_REQUEST)) {
            status = STATUS_INVALID_PARAMETER;
            break;
        }

        PREAD_REQUEST req = (PREAD_REQUEST)Irp->AssociatedIrp.SystemBuffer;

        if (outLen < req->Size) {
            status = STATUS_BUFFER_TOO_SMALL;
            break;
        }

        status = HandleReadRequest(req->handle, (PVOID)req->Address, req->Size, Irp->AssociatedIrp.SystemBuffer);

        if (NT_SUCCESS(status)) {
            bytesReturned = req->Size;
        }
        break;

    }
    case IOCTL_READ_MEMORY_BY_NAME:     // Read memory in a target process by process id 
    {
        if (inLen != sizeof(READ_REQUEST)) {
            status = STATUS_INVALID_PARAMETER;
            break;
        }

        PREAD_REQUEST req = (PREAD_REQUEST)Irp->AssociatedIrp.SystemBuffer;

        if (outLen < req->Size) {
            status = STATUS_BUFFER_TOO_SMALL;
            break;
        }

        status = NameReadRequest(req->targetName, (PVOID)req->Address, req->Size, Irp->AssociatedIrp.SystemBuffer);

        if (NT_SUCCESS(status)) {
            bytesReturned = req->Size;
        }

        break;
    }
    case CTL_WRITE_MEMORY_BY_HANDLE:    // Write data in address of taarget process (by process id)
    {
        if (inLen != sizeof(WRITE_REQUEST)) {
            status = STATUS_INVALID_PARAMETER;
            break;
        }

        PWRITE_REQUEST req = (PWRITE_REQUEST)Irp->AssociatedIrp.SystemBuffer;
        if (outLen < req->Size) {
            status = STATUS_BUFFER_TOO_SMALL;
            break;
        }

        status = HandleWriteRequest(req->handle, req->targetAddress, req->dataBuffer, req->Size);

        if (NT_SUCCESS(status)) {
            bytesReturned = req->Size;
        }
        break;
    }
    case CTL_WRITE_MEMORY_BY_NAME:    // Write data in address of taarget process (by process name)
    {

    }
    default:
        status = STATUS_INVALID_DEVICE_REQUEST;
        break;
    }

    Irp->IoStatus.Status = status;
    Irp->IoStatus.Information = bytesReturned;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return status;
}

NTSTATUS DispatchCreateClose(PDEVICE_OBJECT deviceObject, PIRP irp) {
    UNREFERENCED_PARAMETER(deviceObject);

    irp->IoStatus.Status = STATUS_SUCCESS;
    irp->IoStatus.Information = 0;
    IoCompleteRequest(irp, IO_NO_INCREMENT);
    return STATUS_SUCCESS;
}

VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING symLink = RTL_CONSTANT_STRING(SYMLINK_NAME);
	IoDeleteSymbolicLink(&symLink);
	IoDeleteDevice(DriverObject->DeviceObject);
}

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    UNICODE_STRING devName = RTL_CONSTANT_STRING(DEVICE_NAME);
    UNICODE_STRING symLink = RTL_CONSTANT_STRING(SYMLINK_NAME);

    PDEVICE_OBJECT deviceObject = NULL;
    NTSTATUS status = IoCreateDevice(
        DriverObject, 0, &devName,
        FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN,
        FALSE, &deviceObject
    );

    if (!NT_SUCCESS(status)) return status;

    status = IoCreateSymbolicLink(&symLink, &devName);
    if (!NT_SUCCESS(status)) {
        IoDeleteDevice(deviceObject);
        return status;
    }

    DriverObject->MajorFunction[IRP_MJ_CREATE] = DispatchCreateClose;
    DriverObject->MajorFunction[IRP_MJ_CLOSE] = DispatchCreateClose;
    DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DispatchDeviceControl;
    DriverObject->DriverUnload = DriverUnload;

    deviceObject->Flags |= DO_BUFFERED_IO;
    deviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

    return STATUS_SUCCESS;
}