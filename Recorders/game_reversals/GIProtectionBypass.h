#pragma once
#include <cstdio>
#include <cstdint>
#include <map>
#include <string>
#include "windows.h"
#include <libloaderapi.h>
#include "../libs/MinHook/include/MinHook.h"

class GIProtectionBypass
{
public:
	void InstallHooks();
	void InitBypass();

public:
	static GIProtectionBypass& GetInstance();

public:
	std::map<int32_t, std::string> m_CorrectSignatures;
};

