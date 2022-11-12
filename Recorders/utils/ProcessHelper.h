#pragma once
#include <filesystem>
#include <cstdint>
#include <Windows.h>
#include <stdio.h>
class ProcessHelper
{
public:
	static bool CloseHandleByName(const wchar_t* name);
	static std::string GetModulePaths(HMODULE hModule);
	static void SetCurrentPath(const std::filesystem::path& current_path);
	static std::filesystem::path GetCurrentPath();
	static int64_t GetCurrentTimeMillisec();
};

