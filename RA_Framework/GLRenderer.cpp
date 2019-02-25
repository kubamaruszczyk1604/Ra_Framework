#include "GLRenderer.h"
#include "Entity.h"
#include "RendererDirectives.h"
//#include "GLTexture.h"
//#include <msclr\marshal_cppstd.h>
//#include "ShaderVariableContainer.h"
//#include "VariableStrings.cs"
namespace RA_FRAMEWORK
{
	//using namespace msclr::interop;
	//using namespace ShaderCreationTool;
	bool GLRenderer::s_IsRunning{ false };
	HWND GLRenderer::s_hWnd{ 0 };
	HGLRC GLRenderer::s_hGLRC{ nullptr };
	HDC GLRenderer::s_hDevCtx{ nullptr };
	GLuint GLRenderer::s_CullMode{ GL_FRONT_AND_BACK };
	Camera* GLRenderer::s_CurrentCamera{ nullptr };
	int GLRenderer::s_ScreenWidth{ 800 };
	int GLRenderer::s_ScreenHeight{ 600 };
	bool GLRenderer::s_MakeCurrentCalled{ false };
	Vec4 GLRenderer::VectorVariableTest{ Vec4(1.0f) };
	float GLRenderer::s_TotalTime{ 0 };

	bool GLRenderer::KLMSetPixelFormat(HDC hdc)
	{
		PIXELFORMATDESCRIPTOR pfd;
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW |
			PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER |
			PFD_SUPPORT_COMPOSITION;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cRedBits = pfd.cRedShift = pfd.cGreenBits = pfd.cGreenShift =
			pfd.cBlueBits = pfd.cBlueShift = 0;
		pfd.cAlphaBits = pfd.cAlphaShift = 0;
		pfd.cAccumBits = pfd.cAccumRedBits = pfd.cAccumGreenBits =
			pfd.cAccumBlueBits = pfd.cAccumAlphaBits = 0;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		pfd.cAuxBuffers = 0;
		pfd.iLayerType = PFD_MAIN_PLANE;
		pfd.bReserved = 0;
		pfd.dwLayerMask = pfd.dwVisibleMask = pfd.dwDamageMask = 0;
		// choose pixel format returns the number most similar pixel format available
		int n = ChoosePixelFormat(hdc, &pfd);
		// set pixel format returns whether it sucessfully set the pixel format
		return SetPixelFormat(hdc, n, &pfd);
	}

	bool GLRenderer::Initialize(const int width, const int height, const HWND handle)
	{
		s_ScreenWidth = width;
		s_ScreenHeight = height;
		s_hWnd = handle;
		if ((s_hDevCtx = GetDC(s_hWnd)) == NULL) return false;
		// set the pixel format
		if (!KLMSetPixelFormat(s_hDevCtx)) return false;
		// Create context 
		if ((s_hGLRC = wglCreateContext(s_hDevCtx)) == NULL) return false;
		wglMakeCurrent(s_hDevCtx, s_hGLRC);
		// set defaults
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glCullFace(GL_FRONT_AND_BACK);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_MULTISAMPLE);
		glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
		glViewport(0, 0, width, height);
		s_IsRunning = true;
		glewInit();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return true;
	}
	
	void GLRenderer::Render(Entity* entity)
	{
		Component* c;
        if (!entity->TryGetCachedModel(c))  return;
		ModelComponent* mc = static_cast<ModelComponent*>(c);
		Render(mc, s_CurrentCamera, entity->GetTransform(),entity->GetName());
	}

	void GLRenderer::Render(ModelComponent* model, Camera* camera, Transform* transform, const String& name)
	{
		Material* material = model->GetMaterial();
		if (!camera) return;
		Mat4 worldView;
		//if (s_CurrentCamera->GetParent() == nullptr)
		//{
		//	worldView = s_CurrentCamera->GetViewMatrix() * transform->GetWorldMat();
		//}
		//else
		{
			Entity* parent = camera->GetParent();
			parent->CalculateTransform();
			camera->SetTransformMatrix(parent->GetTransform()->GetWorldMat());
			worldView = camera->GetViewMatrix() * transform->GetWorldMat();
		}
		Mat4 MVP = camera->GetProjectionMatrix(s_ScreenWidth, s_ScreenHeight) * worldView;
		material->Use();
#ifdef ENABLE__uWORLD
		material->GetShaderProgram()->SetMat4x4("uWORLD", transform->GetWorldMat());
#endif // ENABLE__uWORLD
#ifdef ENABLE__uWORLD_INVERSE
		material->GetShaderProgram()->SetMat4x4("uWORLD_INVERSE", glm::inverse(transform->GetWorldMat()));
#endif // ENABLE__uWORLD_INVERSE
#ifdef ENABLE__uVIEW
		material->GetShaderProgram()->SetMat4x4("uVIEW", s_CurrentCamera->GetViewMatrix());
#endif //ENABLE__uVIEW
#ifdef ENABLE__uMVP
		material->GetShaderProgram()->SetMat4x4("uMVP", MVP);
#endif //ENABLE__uMVP
#ifdef ENABLE__uCameraPosition
		material->GetShaderProgram()->SetVec3Float("uCameraPosition", Vec3(camera->GetWorldMatrix()*Vec4(0.0, 0.0, 0.0, 1.0)));
#endif //ENABLE__uCameraPosition
#ifdef ENABLE__uTime
		material->GetShaderProgram()->SetFloat("uTime", s_TotalTime);
#endif//ENABLE__uTime 
		model->GetMesh()->GetVBO()->Draw(PrimitiveType::TRIANGLES);
	}

	void GLRenderer::Update(const float deltaTime, const float totalTime)
	{
		s_TotalTime = totalTime;
	}

	void GLRenderer::ShutDown()
	{
		// release device context
		ReleaseDC(s_hWnd, s_hDevCtx);
		// default to no context
		wglMakeCurrent(0, 0);
		// delete GL context0
		wglDeleteContext(s_hGLRC);
		// delete device context
		DeleteDC(s_hDevCtx);
	}

	void GLRenderer::ClearScreen(const Colour & colour)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(colour.r, colour.g, colour.b, colour.a);
	}

	void GLRenderer::SwapBuffers()
	{
		::SwapBuffers(s_hDevCtx);
		//wglSwapLayerBuffers(s_hDevCtx,1);
	}

	void GLRenderer::SetCullMode(const CullMode mode)
	{
		switch (mode)
		{
		case(CullMode::FRONT_AND_BACK):
			s_CullMode = GL_FRONT_AND_BACK;
			break;
		case(CullMode::FRONT):
			s_CullMode = GL_FRONT;
			break;
		case(CullMode::BACK):
			s_CullMode = GL_BACK;
			break;
		default:
			break;
		}
		glCullFace(s_CullMode);
	}

	void GLRenderer::SetFillMode(const FillMode mode)
	{
		switch (mode)
		{
		case(FillMode::SOLID):
			glPolygonMode(s_CullMode, GL_FILL);
			break;
		case(FillMode::WIREFRAME):
			glPolygonMode(s_CullMode, GL_LINE);
			break;
		default:
			break;
		}
	}

	void GLRenderer::SetActiveCamera(Camera * camera)
	{
		s_CurrentCamera = camera;
	}
}