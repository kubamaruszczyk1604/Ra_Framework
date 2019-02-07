#pragma once
#include "RAUtils.h"
#include "Camera.h"
#include "RendererModes.h"
#include "ModelComponent.h"



namespace RA_FRAMEWORK
{

	class GLRenderer
	{
	private:
		static bool	s_IsRunning;
		static HWND	s_hWnd;
		static HGLRC s_hGLRC;
		static HDC s_hDevCtx;

		static Camera* s_CurrentCamera;

		static int s_ScreenWidth;
		static int s_ScreenHeight;
		static bool s_MakeCurrentCalled;
		static bool KLMSetPixelFormat(HDC hdc);

		static Vec4 VectorVariableTest;
		static float dummyTime;

	public:
		GLRenderer() = delete;
		GLRenderer(const GLRenderer&) = delete;
		GLRenderer& operator=(const GLRenderer&) = delete;

		static bool Initialize(const int width, const int height, const HWND handle);
		static void Render(Entity* entity);
		static void Render(ModelComponent* model, Camera* camera);

		static void Update(const float deltaTime, const float totalTime);
		static void ShutDown();
		static void ClearScreen(const Colour& colour);
		static void SwapBuffers();
		static void SetCullMode(const CullMode mode);
		static void SetFillMode(const FillMode mode);
		static void SetActiveCamera(Camera* camera);

	};

}
