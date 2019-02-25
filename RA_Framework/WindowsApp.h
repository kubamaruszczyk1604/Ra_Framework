#pragma once
#include <Windows.h>
#include <string>
#include "Stopwatch.h"
#include "SceneManager.h"
using namespace RA_FRAMEWORK;
class WindowsApp
{
private:
	static std::string s_AppTitle;
	static Stopwatch s_GlobalTimer;
	static Stopwatch s_FrameTimer;
	static RECT s_WindowedCoords;
	static DWORD s_WindowStyle_W;
	static DWORD s_WindowStyle_FS;
	static DWORD s_WindowStyle;
	static HWND s_Hwnd;
	static float s_TimeScale;
	static int s_ClientWidth;
	static int s_ClientHeight;
	static bool s_isInitialized;
	static bool s_ExitFlag;
	static bool s_isFullScreen;
private:
	static LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static void OnResize(HWND hWnd);
public:
	WindowsApp() = delete;
	WindowsApp(const WindowsApp&) = delete;
	WindowsApp& operator=(const WindowsApp&) = delete;
public:
	static bool Create(int width, int height, const std::string& title);
	static int Run();
	static void SetFullscreenMode(bool fullscreen);
	static bool IsFullscreen() { return s_isFullScreen; }
};
