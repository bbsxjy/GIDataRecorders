#include "pch-il2cpp.h"
#include "RecorderBase.h"

void RecorderBase::Initialize()
{
	this->InitLogConfigs();
	this->InitVideoConfigs();
}

void RecorderBase::Record(int64_t timeStamp)
{
	//need to be overrided by inherited classes.
}

nlohmann::json RecorderBase::Record(nlohmann::json json)
{
	//need to be overrided by inherited classes.
	return NULL;
}

void RecorderBase::InitLogConfigs()
{
	//open a file stream
	using namespace std::chrono;
	milliseconds ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);

	//create json file if not there
	std::string logsDirectory = (util::GetCurrentPath() / "Actions").string();
	this->m_currentFileName = logsDirectory + "/Action_" + std::to_string(ms.count()) + ".json";
	CreateDirectory(logsDirectory.c_str(), nullptr);
	m_json_root["action_records"] = {};
	//LOG_DEBUG("Log recorder configs initialized.");
}

void RecorderBase::InitVideoConfigs()
{
	//open a file stream
	using namespace std::chrono;
	milliseconds ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);
	std::string screenshotsDirectory = (util::GetCurrentPath() / "ScreenShots").string();
	CreateDirectory(screenshotsDirectory.c_str(), nullptr);
	//LOG_DEBUG("Video recorder configs initialized.");
}

void RecorderBase::Close()
{
	//close up streams
	this->m_logFileStream.close();
}

void RecorderBase::Write(std::string jsonString)
{
	//save MetaData
	this->m_logFileStream.open(this->m_currentFileName.c_str(), std::ofstream::out);
	if (this->m_logFileStream.is_open())
	{
		this->m_logFileStream << jsonString << std::endl;
		this->m_logFileStream.flush();
	}
	this->Close();
	LOG_DEBUG("Meta data wrote to file.");
}


