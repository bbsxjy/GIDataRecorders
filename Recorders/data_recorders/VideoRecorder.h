#pragma once
#include "RecorderBase.h"
#include "Screenshot.h"

class VideoRecorder :
    public RecorderBase
{
public:
    HWND m_hWnd;
    std::unordered_map<std::string, Mat> m_timestamp_to_video_frame_map;
    Screenshot m_screenshot;
    std::string m_current_sc_folder_path;
public:
    virtual void Initialize() override;
    virtual void Record(int64_t timeStamp) override;
    void Write();
    void SetCurrentSCFolderPath(std::string path);
    std::string GetCurrentSCFolderPath();
};

