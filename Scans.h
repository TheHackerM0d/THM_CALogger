#include "Includes.h"

namespace Logger
{
	namespace Address
	{
		namespace engine
		{

		}
		namespace cshell
		{
			DWORD Get_GameStatus;
		}
	}
	namespace Pattern
	{
		namespace engine
		{

		}
		namespace cshell
		{
			const char Patt_GameStatus[] = "? 00 00 00 00 00 00 00 ? ? ? 37 00 00 00 00 FF FF FF FF";
		}
	}
}


void GameAddressLogger()
{
	Logger::Address::cshell::Get_GameStatus = PatternScanOutCshell(Logger::Pattern::cshell::Patt_GameStatus);
}
