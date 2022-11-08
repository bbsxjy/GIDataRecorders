#pragma once

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

#include "util.h"

bool ManualMapDLL(HANDLE hProc, const std::string& filepath);
bool ManualMapDLL(HANDLE hProc, BYTE* pSrcData, SIZE_T FileSize, bool ClearHeader = false, bool ClearNonNeededSections = false, bool AdjustProtections = true, bool SEHExceptionSupport = false, DWORD fdwReason = DLL_PROCESS_ATTACH);
bool LoadLibraryDLL(HANDLE hProc, const std::string& dllpath);
bool InjectDLL(HANDLE hProc, const std::string& filepath);