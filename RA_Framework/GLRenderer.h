#pragma once
#include "GLTypeLUTs.h"
#include "RAUtils.h"
#include "Camera.h"
#include "RendererModes.h"
#include "ModelComponent.h"
#include "GLRenderTarget.h"
namespace RA_FRAMEWORK
{
	class Transform;
	class GLRenderer
	{
	private:
		static bool	s_IsRunning;
		static HWND	s_hWnd;
		static HGLRC s_hGLRC;
		static HDC s_hDevCtx;
		static GLuint s_CullMode;
		static Camera* s_CurrentCamera;
		static int s_ScreenWidth;
		static int s_ScreenHeight;
		static bool s_MakeCurrentCalled;
		static bool KLMSetPixelFormat(HDC hdc);
		static Vec4 VectorVariableTest;
		static float s_TotalTime;
	public:
		GLRenderer() = delete;
		GLRenderer(const GLRenderer&) = delete;
		GLRenderer& operator=(const GLRenderer&) = delete;
	public:
		static bool		Initialize(const int width, const int height, const HWND handle);
		static void		ResizeWindow(unsigned width, unsigned height);
		static void		RenderPass(ListOfEntities* entities, GLRenderTarget* target);
		static void		RenderEntity(Entity* entity);
		static void		Render(ModelComponent* model, Camera* camera, Transform* transform, const String& name);
		static void		Update(const float deltaTime, const float totalTime);
		static void		ShutDown();
		static void		ClearScreen(const ColorRGBA& colour);
		static void		SwapBuffers();
		static void		SetCullMode(const CullMode mode);
		static void		SetFillMode(const FillMode mode);
		static void		SetActiveCamera(Camera* camera);
		static void		EnableAlphaBlending(bool enabled = true);
		static void		EnableDepthTest(bool enabled = true, DepthQualifier qualifier = DepthQualifier::LESS);

	};
}
