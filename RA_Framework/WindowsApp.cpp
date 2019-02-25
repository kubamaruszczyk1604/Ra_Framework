#include "WindowsApp.h"
#include "InputSystem.h"
#include "SceneManager.h"
#include "GLRenderer.h"

using namespace RA_FRAMEWORK;
int WindowsApp::s_ClientWidth{ 800 };
int WindowsApp::s_ClientHeight{ 600 };
bool WindowsApp::s_isFullScreen{ false };
DWORD WindowsApp::s_WindowStyle{ WS_OVERLAPPEDWINDOW };
DWORD WindowsApp::s_WindowStyle_FS{ WS_POPUP | WS_SYSMENU | WS_VISIBLE | CS_HREDRAW | CS_VREDRAW };
DWORD WindowsApp::s_WindowStyle_W{ WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW | WS_VISIBLE | CS_HREDRAW | CS_VREDRAW };
RECT WindowsApp::s_WindowedCoords{ 0, 0, 0, 0 };
std::string WindowsApp::s_AppTitle{ "no title" };
HWND WindowsApp::s_Hwnd{ nullptr };
bool WindowsApp::s_ExitFlag{ false };
float WindowsApp::s_TimeScale{ 1.0f };
Stopwatch WindowsApp::s_GlobalTimer;
Stopwatch WindowsApp::s_FrameTimer;

bool WindowsApp::Create(int const width, int const height, const std::string& title)
{
	s_ClientWidth = width;
	s_ClientHeight = height;
	s_AppTitle = title;

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MsgProc;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = "abc";

	if (!RegisterClassEx(&wc))
	{
		::MessageBox(NULL, "Failed to register window", "Registration fail", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	RECT rect;
	rect = { 0, 0, static_cast<LONG>(s_ClientWidth), static_cast<LONG>(s_ClientHeight) };
	AdjustWindowRect(&rect, s_WindowStyle, FALSE);

	const UINT wdth = rect.right - rect.left;
	const UINT hght = rect.bottom - rect.top;
	const UINT x = GetSystemMetrics(SM_CXSCREEN) / 2 - wdth / 2;
	const UINT y = GetSystemMetrics(SM_CYSCREEN) / 2 - hght / 2;

	s_Hwnd = CreateWindowEx(
		static_cast<DWORD>(0),
		wc.lpszClassName,
		s_AppTitle.c_str(),
		s_WindowStyle,
		x,
		y,
		width,
		height,
		nullptr,
		nullptr,
		::GetModuleHandle(nullptr),
		nullptr
	);
	if (!s_Hwnd)
	{
		::MessageBox(nullptr, "Failed to create Window", "Error", MB_OK);
		return false;
	}
	ShowWindow(s_Hwnd, SW_SHOW);

	PRINTL("WINDOW CREATED..");
	//SetFullscreenMode(true);
	SceneManager::Initialize();
	GLRenderer::Initialize(width, height, s_Hwnd);
	return true;
}

int WindowsApp::Run()
{
	MSG msg = { nullptr };
	s_GlobalTimer.Start();
	while (!s_ExitFlag && msg.message != WM_QUIT)
	{
		//Handle input from system
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			s_FrameTimer.Start();
			//Updates scene and then renderer
			SceneManager::Update(s_FrameTimer.ElapsedTime()* s_TimeScale, s_GlobalTimer.ElapsedTime() * s_TimeScale);
			s_FrameTimer.Stop();
		}
	}
	if (s_ExitFlag)
	{
		msg.wParam = 0;
	}
	// Shut down the scene manager
	SceneManager::ShutDown();
	return static_cast<int>(msg.wParam);
}

LRESULT WindowsApp::MsgProc(HWND const hWnd, UINT const msg, WPARAM const wParam, LPARAM const lParam)
{
	// Check for anttweakbar events
	/*if (TwEventWin(hWnd, msg, wParam, lParam))
	{
	return 0;
	}*/
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		InputSystem::PropagateOnKeyDown(wParam);
		break;
	case WM_KEYUP:
		InputSystem::PropagateOnKeyUp(wParam);
		break;
	case WM_MOUSEMOVE:
		InputSystem::PropagateOnMouseMove(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_LBUTTONDOWN:
		InputSystem::PropagateOnMouseDown(0);
		break;
	case WM_LBUTTONUP:
		InputSystem::PropagateOnMouseUp(0);
		break;
	case WM_RBUTTONDOWN:
		InputSystem::PropagateOnMouseDown(1);
		break;
	case WM_RBUTTONUP:
		InputSystem::PropagateOnMouseUp(1);
		break;
	case WM_ENTERSIZEMOVE:
		break;
	case WM_EXITSIZEMOVE:
		break;
	case WM_SIZE:
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return LRESULT();
}

void WindowsApp::OnResize(HWND const hWnd) {
	// Use braces to limit the scope of Rect, TmpW, etc
	RECT r{ 0 };
	// Store windowed coords as client data
	::GetClientRect(hWnd, &r);
	s_ClientWidth = r.right - r.left;
	s_ClientHeight = r.bottom - r.top;
	// store windowed coords loally (if not fullscreen)
	if (!IsFullscreen) ::GetWindowRect(s_Hwnd, &s_WindowedCoords);
	// Window size is different? true = SIZE (not a MOVE)
	//TODO: GLRenderer::Resize(hWnd, (r.right - r.left), (r.bottom - r.top));
}

void WindowsApp::SetFullscreenMode(bool fullscreen)
{
	// Get screen resolution for fullscreen
	const int FS_x = GetSystemMetrics(SM_CXSCREEN);
	const int FS_y = GetSystemMetrics(SM_CYSCREEN);

	// Check that we need to change screen mode from current mode
	if (fullscreen != s_isFullScreen) 
	{
		if (fullscreen) 
		{
			// go fullscreen (set the window style)
			::SetWindowLong(s_Hwnd, GWL_STYLE, s_WindowStyle_FS);
			::SetWindowPos(
				s_Hwnd,
				nullptr,
				0, 0,
				FS_x,
				FS_y,
				SWP_SHOWWINDOW
			);
			// flag = true
			s_isFullScreen = true;
			OnResize(s_Hwnd);
		}
		else 
		{
			// return back from fullscreen (set window style)
			::SetWindowLong(s_Hwnd, GWL_STYLE, s_WindowStyle_W);
			::SetWindowPos(
				s_Hwnd,
				nullptr,
				s_WindowedCoords.left,
				s_WindowedCoords.top,
				s_WindowedCoords.right - s_WindowedCoords.left,
				s_WindowedCoords.bottom - s_WindowedCoords.top,
				SWP_SHOWWINDOW
			);
			s_isFullScreen = false;
			OnResize(s_Hwnd);
		}
	}
}