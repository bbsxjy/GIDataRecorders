#include "GameWorldVarsRecorder.h"

nlohmann::json GameWorldVarsRecorder::Record(nlohmann::json record)
{
	auto root = record["game_variables"];
	root["fps"] = GameFunctions::GetInstance().Application_get_targetFrameRate(nullptr);
	root["resolution_x"] = GameFunctions::GetInstance().Screen_get_width(nullptr);
	root["resolution_y"] = GameFunctions::GetInstance().Screen_get_height(nullptr);
	record["game_variables"] = root;
	return record;
}
