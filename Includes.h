#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <d3d9.h>
#include <d3dx9.h>
#include <sstream>
#include <fstream>
#include <filesystem>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "PatternScanner.h"


std::ofstream ofile;
void __cdecl add_log(const char* fmt, ...)
{
	ofile.open("C:\\LoggerFile.txt", std::ios::app); va_list va_alist; char logbuf[256] = { 0 };
	va_start(va_alist, fmt);
	vsnprintf(logbuf + strlen(logbuf), sizeof(logbuf) - strlen(logbuf), fmt, va_alist);
	va_end(va_alist);
	ofile << logbuf << std::endl; ofile.close();
}