#include "GamePlayerDataRecorder.h"

nlohmann::json GamePlayerDataRecorder::Record(nlohmann::json record)
{
	auto avatarPosition = GameFunctions::GetInstance().ActorUtils_GetAvatarPos(nullptr);
	auto mainCam = GameFunctions::GetInstance().GameObject_Find(
		GameFunctions::GetInstance().string_to_il2cppi("/EntityRoot/MainCamera(Clone)"), nullptr);
	auto mainCamTransform = GameFunctions::GetInstance().GameObject_get_transform(mainCam, nullptr);
	auto t_eulerAngles = GameFunctions::GetInstance().Transform_get_eulerAngles(mainCamTransform, nullptr);
	auto pitch = t_eulerAngles.x;
	auto yaw = t_eulerAngles.y;
	auto roll = t_eulerAngles.z;

	auto root = record["game_player_info"];
	root["yaw"] = yaw;
	root["pitch"] = pitch;
	root["roll"] = roll;
	root["world_x"] = avatarPosition.x;
	root["world_y"] = avatarPosition.y;
	root["world_z"] = avatarPosition.z;
	//root["avatar_index"] = 0;
	record["game_player_info"] = root;
	return record;
}
