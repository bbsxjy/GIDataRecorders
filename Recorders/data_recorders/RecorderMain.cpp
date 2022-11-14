#include "RecorderMain.h"

auto maxX = -999999.f;
auto minX = -999999.f;
auto maxY = -999999.f;
auto minY = -999999.f;
void RecorderMain::Init()
{
	//init configs and create files
	this->Initialize();

	//create instances
	this->m_gpdr = new GamePlayerDataRecorder;
	this->m_gwvr = new GameWorldVarsRecorder;
	this->m_ior = new IORecorder;
	this->m_vr = new VideoRecorder;
	this->m_vr->Initialize();
	printf("录制器启动成功！请进入游戏看到人物再进行录制！\n");
	printf("操作提示：按F7开始录制，F8停止录制！\n");
}

bool IsInGame()
{
	auto avatarPosition = GameFunctions::GetInstance().ActorUtils_GetAvatarPos(nullptr);

	if (avatarPosition.x != 0.0f)
	{
		return true;
	}
	return false;
}

void RecorderMain::Run()
{
	while (520) {
		//setup interruption shortcuts - F7
		if (GetAsyncKeyState(0x76) & 0x8000) {
			this->m_is_interrupted = false;
			if (!this->m_logFileStream.is_open())
			{
				this->InitLogConfigs();
			}

			//open a file stream
			using namespace std::chrono;
			milliseconds ms = duration_cast<milliseconds>(
				system_clock::now().time_since_epoch()
				);
			std::string screenshotsDirectory = (ProcessHelper::GetCurrentPath() / "ScreenShots").string() + "/" + std::to_string(ms.count());
			CreateDirectory(screenshotsDirectory.c_str(), nullptr);
			this->m_vr->SetCurrentSCFolderPath(screenshotsDirectory);
			//printf("Recording at path %s.\n", screenshotsDirectory);
		}

		//setup continue shortcuts - F8
		if (GetAsyncKeyState(0x77) & 0x8000) {
			this->m_is_interrupted = true;
			//save json to file
			this->Write(this->m_json_root.dump(2));
			//sync save frames
			//this->m_vr->Write();
		}
		
		//on game update / each frame, check in game first.
		if (IsInGame())
		{
			auto dx = GameFunctions::GetInstance().Input_GetAxis(GameFunctions::GetInstance().string_to_il2cppi("Mouse X"), nullptr);
			auto dy = GameFunctions::GetInstance().Input_GetAxis(GameFunctions::GetInstance().string_to_il2cppi("Mouse Y"), nullptr);
			auto width = GameFunctions::GetInstance().Screen_get_width(nullptr);
			auto height = GameFunctions::GetInstance().Screen_get_height(nullptr);

			if (!this->m_is_in_game && this->m_ior->m_psuedo_mouse.x != 0.0f && this->m_ior->m_psuedo_mouse.y != 0.0f)
			{
				//printf("Init.");
				this->m_ior->Initialize();
				this->m_is_in_game = true;
				maxX = this->m_ior->m_psuedo_mouse.x + width / 2.0f;
				minX = this->m_ior->m_psuedo_mouse.x - width / 2.0f;
				maxY = this->m_ior->m_psuedo_mouse.y + height / 2.0f;
				minY = this->m_ior->m_psuedo_mouse.y - height / 2.0f;
			}

			this->m_ior->m_psuedo_mouse.x += dx;
			this->m_ior->m_psuedo_mouse.y += dy;

			if (maxX != -999999.f && minX != -999999.f && maxY != -999999.f && minY != -999999.f)
			{
				if (this->m_ior->m_psuedo_mouse.x >= maxX)
				{
					this->m_ior->m_psuedo_mouse.x = minX;
				}

				else if (this->m_ior->m_psuedo_mouse.x <= minX)
				{
					this->m_ior->m_psuedo_mouse.x = maxX;
				}

				if (this->m_ior->m_psuedo_mouse.y >= maxY)
				{
					this->m_ior->m_psuedo_mouse.y = minY;
				}

				else if (this->m_ior->m_psuedo_mouse.y <= minY)
				{
					this->m_ior->m_psuedo_mouse.y = maxY;
				}
			}

			//printf("Psuedo mouse: %lf, %lf, %lf, %lf, %lf, %lf\r", this->m_ior->m_psuedo_mouse.x, this->m_ior->m_psuedo_mouse.y, maxX, minX, maxY, minY);
			Sleep(17);
		}

		if (!IsInGame() || this->m_is_interrupted)
		{
			Sleep(17);
			continue;
		}

		//create json object
		nlohmann::json record;

		//record io data
		record = this->m_ior->Record(record);
		record = this->m_gwvr->Record(record);
		record = this->m_gpdr->Record(record);

		//add time stamp
		auto currentTime = ProcessHelper::GetCurrentTimeMillisec();
		record["time_stamp"] = currentTime;
		
		this->m_json_root["action_records"].push_back(record);

		//record video
		this->m_vr->Record(currentTime);

		//record at 30fps
		Sleep(17);
	}

	//close stream
    this->Close();
}

