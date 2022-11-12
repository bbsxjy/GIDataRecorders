#include "VideoRecorder.h"

struct ImageData {
    Mat mat;
    LPVOID screen_data;
    std::string screen_shots_directory = "";
};

void AsyncWriter(PolyM::Queue& q)
{
    //LOG_DEBUG("Spawned video frames writer listener thread");
    while (520) {
        auto currentMessage = q.get();
        if (currentMessage == nullptr) {
            continue;
        }
        auto& recastDataMessage = dynamic_cast<PolyM::DataMsg<ImageData>&>(*currentMessage);
        cv::imwrite(recastDataMessage.getPayload().screen_shots_directory + "/Screenshot_" + std::to_string(recastDataMessage.getMsgId()) + ".jpeg", recastDataMessage.getPayload().mat);
        recastDataMessage.getPayload().mat.release();
        delete(recastDataMessage.getPayload().screen_data);
        //delete(&recastDataMessage.getPayload().mat);
        
        if (q.getQSize() == 0)
        {
            printf("Frames wrote to files.\n");
        }
    }
}

void VideoRecorder::Initialize()
{
    this->m_hWnd = FindWindowA(0, "原神");
    while (!this->m_hWnd)
    {
        Sleep(500);
        this->m_hWnd = FindWindowA(0, "原神");
    }

    std::thread t1(AsyncWriter, std::ref(m_mqueue));
    t1.detach();

    //LOG_DEBUG("VideoRecorder initialized!");
}

void VideoRecorder::Record(int64_t timeStamp)
{
    RECT WindowRect;

    GetWindowRect(this->m_hWnd, &WindowRect);

    int titleBarHeight = GetSystemMetrics(SM_CYCAPTION);

    this->m_screenshot = Screenshot();

    Mat src = this->m_screenshot.getScreenshot(WindowRect.left + 3, WindowRect.top + titleBarHeight + 2, GameFunctions::GetInstance().Screen_get_width(nullptr), GameFunctions::GetInstance().Screen_get_height(nullptr));

    ////Sync save
    //this->m_timestamp_to_video_frame_map.emplace(std::to_string(timeStamp), src);
    
    // Async save
    ImageData data = ImageData(src, this->m_screenshot.getCurrentSCData(), GetCurrentSCFolderPath());
    m_mqueue.put(PolyM::DataMsg<ImageData>(timeStamp, data));
    this->m_screenshot.cleanUp();
}

void VideoRecorder::Write()
{
    //save video frame data
    std::string screenshotsDirectory = (ProcessHelper::GetCurrentPath() / "ScreenShots").string();
    int counter = 1;
    for (auto [k, v] : this->m_timestamp_to_video_frame_map) {
        //auto startTime = util::GetCurrentTimeMillisec();
        cv::imwrite(screenshotsDirectory + "/Screenshot_" + k + ".png", v);
        //auto writingTime = util::GetCurrentTimeMillisec() - startTime;
        //write to disk time will need 170-180ms per screenshot
        //LOG_DEBUG((std::to_string(writingTime) + " ms").c_str());
        auto percentage = (counter * 1.0) / this->m_timestamp_to_video_frame_map.size() * 100;
        //auto printString = "Writing frames to disk: (" + std::to_string(counter) + "/" + std::to_string(this->m_timestamp_to_video_frame_map.size()) + ")";
        printf("Writing frames to disk: ");
        printf("%.2f", percentage);
        printf("%%, total frames: ");
        printf(std::to_string(this->m_timestamp_to_video_frame_map.size()).c_str());
        printf("\r");
        counter++;
    }
    this->m_timestamp_to_video_frame_map.clear();
    printf("Frames wrote to files.\n");
}

void VideoRecorder::SetCurrentSCFolderPath(std::string path)
{
    this->m_current_sc_folder_path = path;
}

std::string VideoRecorder::GetCurrentSCFolderPath()
{
    return this->m_current_sc_folder_path;
}
