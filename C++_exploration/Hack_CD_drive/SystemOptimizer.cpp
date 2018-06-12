/*
	The major application or Hack tool for accessing the CD drive tray through IOCL system calls.
	It first finds the location of the CD drive and then runs an infinite loop to keep the tray open.
*/
#include <windows.h>
#include <stdio.h>
#include<string>
#include<unistd.h>
char getDrivePath()
{
	DWORD bytes = 0;
    std::string path="\\\\.\\C:";
    while(true)
    {
	    HANDLE HCDrom = CreateFile(path.c_str(),GENERIC_READ,FILE_SHARE_WRITE,0,OPEN_EXISTING,0,0);
	    if(HCDrom == INVALID_HANDLE_VALUE)
	    {
	    		path[4]++;
	    }
	    else
	    {
	    	CloseHandle(HCDrom);
	    	break;
		}
	    CloseHandle(HCDrom);
	}
	return path.c_str()[4];
}
int main(void)
{
    DWORD bytes = 0;
    std::string path="\\\\.\\C:";path[4]=getDrivePath();
    while(true)
    {
    	printf("%s",path.c_str());
	    HANDLE HCDrom = CreateFile(path.c_str(),GENERIC_READ,FILE_SHARE_WRITE,0,OPEN_EXISTING,0,0);
	    if(HCDrom != INVALID_HANDLE_VALUE)
	    {
	    	DeviceIoControl(HCDrom, FSCTL_LOCK_VOLUME, 0, 0, 0, 0, &bytes, 0);
	    	DeviceIoControl(HCDrom, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &bytes, 0);
	    	DeviceIoControl(HCDrom, IOCTL_STORAGE_EJECT_MEDIA, 0, 0, 0, 0, &bytes, 0);
	    }
	    else
	    {
	    	path[4]=getDrivePath();
		}
	    CloseHandle(HCDrom);
	}
    return 0;
}
