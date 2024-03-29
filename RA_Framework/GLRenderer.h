#pragma once
#include "GLTypeLUTs.h"
#include "RAUtils.h"
#include "Camera.h"
#include "RendererModes.h"
#include "ModelComponent.h"
#include "GLRenderTarget.h"
#include "RenderPass.h"
#include "GLShaderProgram.h"
#include "GLBuiltInShaders.h"
#include "GLSkyBox.h"
namespace RA_FRAMEWORK
{
	class Transform;
	class GLRenderer
	{
	private:
		static bool										s_IsRunning;
		static bool										s_DepthTextEnabled;
		static HWND										s_hWnd;
		static HGLRC									s_hGLRC;
		static HDC										s_hDevCtx;
		static GLuint									s_CullMode;
		static Camera*									s_CurrentCamera;
		static int										s_ScreenWidth;
		static int										s_ScreenHeight;
		static bool										s_MakeCurrentCalled;
		static float									s_TotalTime;
		//static KLMList<std::unique_ptr<RARenderPass>>	s_RenderPassList;
		static KLMList<Camera*>							s_CameraList;
		static GLuint									s_BlitFrameBuffer;
		static GLTexture*								s_TempTexture;
	private:
		static Mesh*									s_QuadMesh;
		static Mesh*									s_SkyboxCubeMesh;
		static GLShaderProgram*							s_TextureShaderProgram;
		static GLShaderProgram*							s_ColGradientShaderProgram;
		static GLShaderProgram*							s_SkyboxShaderProgram;
		static Material*								s_TextureBlitMat;
		static Material*								s_ColGradientMat;
		static Material*								s_SkyboxMat;
	private:
		static bool KLMSetPixelFormat(HDC hdc);
		static bool SetUpShaders();
	public:
		GLRenderer()								= delete;
		GLRenderer(const GLRenderer&)				= delete;
		GLRenderer& operator=(const GLRenderer&)	= delete;
	public:
		static bool		Initialize(const int width, const int height, const HWND handle);
		static void		ResizeWindow(unsigned width, unsigned height);
		//static void		Render(ListOfEntities* entities, GLRenderTarget* target);
		static void		RenderAllPasses(ListOfEntities* entities);
		static void		RenderPass(RARenderPass* pass, ListOfEntities* entities);
		static void		RenderPass(Camera* camera, ListOfEntities* entities);
		static void		RenderEntity(Entity* entity, Camera* camera);
		static void		Render(ModelComponent* model, Camera* camera, Transform* transform, const String& name);
		static void		Update(const float deltaTime, const float totalTime);
		static void		ShutDown();
		static void		ClearScreen(const ColorRGB& colour, bool clearDepth = true);
		static void		ClearScreenWithGradient(const ColorRGB& col1, const ColorRGB& col2, bool clearDepth = true, const Vec2& dir = Vec2(1.0, 0.0), float exp = 1.0f);
		static void		ClearScreenWithGradient(GLTexture* tex1, GLTexture* tex2, float exp);
		static void		ClearScreenWithGradient(const ColorRGBA& col1, const ColorRGBA& col2, GLTexture* tex1, GLTexture* tex2, float exp);
		static bool		RenderSkybox(Camera* camera);
		static void		SwapBuffers();
		static void		SetCullMode(const CullMode mode);
		static void		SetFillMode(const FillMode mode);
		static void		SetActiveCamera(Camera* camera);
		static void		EnableAlphaBlending(bool enabled = true);
		static void		EnableDepthTest(bool enabled = true, DepthQualifier qualifier = DepthQualifier::LESS);
		static void		AddRenderPass(std::unique_ptr<RARenderPass> pass);
		static void		ClearRenderPassList();
		static void		AddRenderPass(Camera* camera) { s_CameraList.Add(camera); }
		static void		Blit(GLTexture* src, GLTexture* dest);
		static void		Blit(GLTexture* src, GLTexture* dest, Material* mat);
		static void		BlitToScreen(GLTexture* src);
		static void		BlitToScreen(GLTexture* src, int x, int y, uint w, uint h);
		static void		BlitToScreen(GLTexture* src, int x, int y, uint w, uint h, float alpha);
		static void		BlitToScreen(GLTexture* src, int x, int y, uint w, uint h, Material* mat);
	};
}
