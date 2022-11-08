#pragma once
#include <Windows.h>
#include <opencv2/opencv.hpp>

#pragma comment(lib, "ade.lib")
#pragma comment(lib, "IlmImf.lib")
#pragma comment(lib, "ippicvmt.lib")
#pragma comment(lib, "libjpeg-turbo.lib")
#pragma comment(lib, "libopenjp2.lib")
#pragma comment(lib, "libpng.lib")
#pragma comment(lib, "libprotobuf.lib")
#pragma comment(lib, "libtiff.lib")
#pragma comment(lib, "libwebp.lib")
#pragma comment(lib, "opencv_core460.lib")
#pragma comment(lib, "opencv_imgcodecs460.lib")
#pragma comment(lib, "opencv_imgproc460.lib")
#pragma comment(lib, "quirc.lib")
#pragma comment(lib, "zlib.lib")
#pragma comment(lib, "ippiw.lib")
#pragma comment(lib, "ittnotify.lib")

using namespace cv;
class Screenshot
{
public:
    Screenshot();
    Screenshot(HWND hWnd);
    double static getZoom();
    double static getZoom(HWND hWnd);
    LPVOID getCurrentSCData();
    HDC getCurrentScreenDCData();
    void cleanUp();
    cv::Mat getScreenshot();
    cv::Mat getScreenshot(int x, int y, int width, int height);
private:
    int m_width;
    int m_height;
    HDC m_screenDC;
    HDC m_compatibleDC;
    HBITMAP m_hBitmap;
    LPVOID m_screenshotData = nullptr;
};
