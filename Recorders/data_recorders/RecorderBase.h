#pragma once
#include <fstream>
#include <ctime>
#include <chrono>
#include <string>
#include <nlohmann/json.hpp>
#include <windows.h>
#include <conio.h>
#include <PolyM/Msg.hpp>
#include <PolyM/Queue.hpp>
#include "ProcessHelper.h"
#include "game-functions.h"

class RecorderBase
{
protected:
	std::ofstream m_logFileStream;
	nlohmann::json m_json_root = {};
	std::string m_currentFileName;
	PolyM::Queue m_mqueue;

public:
	virtual void Initialize();
	void Close();
	void Write(std::string jsonString);
	virtual void Record(int64_t timeStamp);
	virtual nlohmann::json Record(nlohmann::json json);
	void InitLogConfigs();
	void InitVideoConfigs();
};

