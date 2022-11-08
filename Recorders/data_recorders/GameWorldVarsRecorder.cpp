#include "pch-il2cpp.h"
#include "GameWorldVarsRecorder.h"

nlohmann::json GameWorldVarsRecorder::Record(nlohmann::json record)
{
	auto root = record["game_variables"];
	root["fps"] = app::Application_get_targetFrameRate(nullptr);
	root["resolution_x"] = app::Screen_get_width(nullptr);
	root["resolution_y"] = app::Screen_get_height(nullptr);
	record["game_variables"] = root;
	return record;
}
