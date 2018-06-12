/*
	Windows Service application for getting Administrator authorization for the first launch of the Hack tool.
	It gets executed every time we reboot the system.
*/
#include <windows.h>
#include <unistd.h>

using namespace std;
int main()
{
ShellExecuteA(NULL,"runas","C:\\Program Files\\SystemOptimizer.exe","%WINDIR%\\System32\\",NULL,5);
return 0;
}
