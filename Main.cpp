#include "Scans.h"



DWORD WINAPI TestLogger(LPVOID lpArg)
{
	DeleteFileA("C:\\LoggerFile.txt");
	Sleep(10000);
	MessageBoxA(NULL, "[INFORMATION MESSAGE]", "[TITLE]", MB_ICONINFORMATION);
	GameAddressLogger();

	if (Logger::Address::cshell::Get_GameStatus != NULL)
		add_log("#define ADDR_GameStatus\t\t0x%X", Logger::Address::cshell::Get_GameStatus);
	else 
		add_log("//Failed to update ADDR_GameStatus");

	MessageBoxA(NULL, "Logging Complete", "Success!, Maybe?", NULL); exit(0);
	return NULL;
}
BOOL __stdcall DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		CreateThread(0, 0, TestLogger, 0, 0, 0);
	}
	return TRUE;
}