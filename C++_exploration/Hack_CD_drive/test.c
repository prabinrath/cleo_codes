/*
	Test file for checking the IOCL system call for the Hack tool.
*/
#include <windows.h>
#include <stdio.h>

int main(void)
{
    DWORD bytes = 0;
    while(2>1)
    {
	    HANDLE HCDrom = CreateFile("\\\\.\\F:",GENERIC_READ,FILE_SHARE_WRITE,0,OPEN_EXISTING,0,0);
	    if(HCDrom != INVALID_HANDLE_VALUE)
	    {
	    	DeviceIoControl(HCDrom, FSCTL_LOCK_VOLUME, 0, 0, 0, 0, &bytes, 0);
	    	DeviceIoControl(HCDrom, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &bytes, 0);
	    	DeviceIoControl(HCDrom, IOCTL_STORAGE_EJECT_MEDIA, 0, 0, 0, 0, &bytes, 0);
	    }
	    CloseHandle(HCDrom);
	}
    return 0;
}
