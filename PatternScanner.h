#pragma once
DWORD PatternScan(DWORD dwModuleBase, CONST CHAR* szSignature, BOOL bSkipFirst)
{
    static auto patternToByte = [](CONST CHAR* szPattern) { auto bytes = std::vector<int>{};  const auto start = const_cast<char*>(szPattern);  const auto end = const_cast<char*>(szPattern) + strlen(szPattern);  for (auto current = start; current < end; ++current) { if (*current == '?') { ++current; if (*current == '?')  ++current;  bytes.push_back(-1); } else { bytes.push_back(strtoul(current, &current, 16)); } }  return bytes;  };
    const auto dosHeader = (PIMAGE_DOS_HEADER)dwModuleBase; const auto ntHeaders = (PIMAGE_NT_HEADERS)((PBYTE)dwModuleBase + dosHeader->e_lfanew); const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage; auto       patternBytes = patternToByte(szSignature);
    const auto scanBytes = reinterpret_cast<PBYTE>(dwModuleBase); const auto s = patternBytes.size(); const auto d = patternBytes.data(); bool bFoundFirst = false;
    for (auto i = 0ul; i < sizeOfImage - s; ++i) { bool found = true; for (auto j = 0ul; j < s; ++j) { if (scanBytes[i + j] != d[j] && d[j] != -1) { found = false;  break; } }  if (found) { if (bSkipFirst) { if (!bFoundFirst) bFoundFirst = true; else { return reinterpret_cast<DWORD>(&scanBytes[i]); } } else { return reinterpret_cast<DWORD>(&scanBytes[i]); } } }return 0;
}


DWORD PatternScanOutEngine(CONST CHAR* szSignature)
{
    DWORD dwEngineEntry = (DWORD)GetModuleHandleA("Engine.exe");
    static auto patternToByte = [](CONST CHAR* szPattern) { auto bytes = std::vector<int>{};  const auto start = const_cast<char*>(szPattern);  const auto end = const_cast<char*>(szPattern) + strlen(szPattern);  for (auto current = start; current < end; ++current) { if (*current == '?') { ++current; if (*current == '?')  ++current;  bytes.push_back(-1); } else { bytes.push_back(strtoul(current, &current, 16)); } }  return bytes;  };
    const auto dosHeader = (PIMAGE_DOS_HEADER)dwEngineEntry; const auto ntHeaders = (PIMAGE_NT_HEADERS)((PBYTE)dwEngineEntry + dosHeader->e_lfanew); const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage; auto       patternBytes = patternToByte(szSignature);
    const auto scanBytes = reinterpret_cast<PBYTE>(dwEngineEntry); const auto s = patternBytes.size(); const auto d = patternBytes.data(); bool bFoundFirst = false;
    for (auto i = 0ul; i < sizeOfImage - s; ++i) {
        bool found = true; for (auto j = 0ul; j < s; ++j)
        {
            if (scanBytes[i + j] != d[j] && d[j] != -1) { found = false;  break; }
        }
        if (found) { return reinterpret_cast<DWORD>(&scanBytes[i]); }
    }return 0;
}
DWORD PatternScanOutAdderEngine(CONST CHAR* szSignature, DWORD Adder)
{
    DWORD pattern = PatternScanOutEngine(szSignature);  if (pattern) pattern = *(DWORD*)(pattern + Adder);
    return pattern;
}
DWORD PatternScanAdderEngine(CONST CHAR* szSignature, BOOL bSkipFirst, DWORD Adder)
{
    DWORD dwEngineEntry = (DWORD)GetModuleHandleA("Engine.exe");
    DWORD pattern = PatternScan(dwEngineEntry, szSignature, bSkipFirst);  if (pattern) pattern = *(DWORD*)(pattern + Adder);
    return pattern;
}

DWORD PatternScanOutCshell(CONST CHAR* szSignature)
{
    DWORD dwCShellEntry = (DWORD)GetModuleHandleA("cshell.dll");
    static auto patternToByte = [](CONST CHAR* szPattern) { auto bytes = std::vector<int>{};  const auto start = const_cast<char*>(szPattern);  const auto end = const_cast<char*>(szPattern) + strlen(szPattern);  for (auto current = start; current < end; ++current) { if (*current == '?') { ++current; if (*current == '?')  ++current;  bytes.push_back(-1); } else { bytes.push_back(strtoul(current, &current, 16)); } }  return bytes;  };
    const auto dosHeader = (PIMAGE_DOS_HEADER)dwCShellEntry; const auto ntHeaders = (PIMAGE_NT_HEADERS)((PBYTE)dwCShellEntry + dosHeader->e_lfanew); const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage; auto       patternBytes = patternToByte(szSignature);
    const auto scanBytes = reinterpret_cast<PBYTE>(dwCShellEntry); const auto s = patternBytes.size(); const auto d = patternBytes.data(); bool bFoundFirst = false;
    for (auto i = 0ul; i < sizeOfImage - s; ++i) {
        bool found = true; for (auto j = 0ul; j < s; ++j)
        {
            if (scanBytes[i + j] != d[j] && d[j] != -1) { found = false;  break; }
        }
        if (found) { return reinterpret_cast<DWORD>(&scanBytes[i]); }
    }return 0;
}
DWORD PatternScanOutAdderCshell(CONST CHAR* szSignature, DWORD Adder)
{
    DWORD pattern = PatternScanOutCshell(szSignature);  if (pattern) pattern = *(DWORD*)(pattern + Adder);
    return pattern;
}
DWORD PatternScanAdderCshell(CONST CHAR* szSignature, BOOL bSkipFirst, DWORD Adder)
{
    DWORD dwCShellEntry = (DWORD)GetModuleHandleA("cshell.dll");
    DWORD pattern = PatternScan(dwCShellEntry, szSignature, bSkipFirst);  if (pattern) pattern = *(DWORD*)(pattern + Adder);
    return pattern;
}