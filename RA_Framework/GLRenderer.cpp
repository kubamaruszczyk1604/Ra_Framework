#include "GLRenderer.h"
#include "Entity.h"
#include "RendererDirectives.h"
#include "GeometryGenerator.h"
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
	GLuint GLRenderer::s_CullMode{ GL_BACK };
	Camera* GLRenderer::s_CurrentCamera{ nullptr };
	int GLRenderer::s_ScreenWidth{ 800 };
	int GLRenderer::s_ScreenHeight{ 600 };
	bool GLRenderer::s_MakeCurrentCalled{ false };
	float GLRenderer::s_TotalTime{ 0 };
	//KLMList<std::unique_ptr<RARenderPass>> GLRenderer::s_RenderPassList;
	KLMList<Camera*> GLRenderer::s_CameraList;
	GLuint GLRenderer::s_BlitFrameBuffer;
	Mesh* GLRenderer::s_QuadMesh;
	//vector<B> A::vector_of_B;
	GLShader* GLRenderer::s_TextureVertFrag[2] = { nullptr,nullptr };
	GLShaderProgram* GLRenderer::s_TextureShaderProgram{ nullptr };
	Material* GLRenderer::s_TextureBlitMat{nullptr};
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
		const int n = ChoosePixelFormat(hdc, &pfd);
		// set pixel format returns whether it sucessfully set the pixel format
		return SetPixelFormat(hdc, n, &pfd);
	}

	bool GLRenderer::SetUpShaders()
	{
		
		String vertShaderString = "#version 330\n";
		vertShaderString += "layout(location = 0) in vec3 vertex_position;\n";
		vertShaderString += "layout(location = 1) in vec3 vertex_normal;\n";
		vertShaderString += "layout(location = 2) in vec3 tangent;\n";
		vertShaderString += "layout(location = 3) in vec2 uvs;\n";
		vertShaderString += "out vec2 oUVs;\n";
		vertShaderString += "void main() { oUVs = uvs; gl_Position = vec4(vertex_position, 1.0);}";


		String fragShaderString = "#version 330\n in vec2 oUVs;\n uniform sampler2D _sourceTex;\n";
		fragShaderString += "out vec4 colorOut;\n";
		fragShaderString += "void main() { colorOut = texture(_sourceTex,oUVs)*vec4(1.0,0.0,0.0,1.0);}\n";


		std::string status;
		std::cout << "\nRENDERER DEBUG - BUILT-IN SHADER STATUS" << std::endl;
		s_TextureVertFrag[0]= new GLShader(ShaderType::VERTEX);
		s_TextureVertFrag[0]->LoadFromString(vertShaderString);
		bool vertOK = s_TextureVertFrag[0]->Compile(status);
		std::cout << "Compile Vertex Shader: " << vertOK;
		std::cout << "  Status: " << status << std::endl;
		if (!vertOK) return false;

		s_TextureVertFrag[1] = new GLShader(ShaderType::FRAGMENT);
		s_TextureVertFrag[1]->LoadFromString(fragShaderString);
		bool fragOK = s_TextureVertFrag[1]->Compile(status);
		std::cout << "Compile Fragment Shader: " << fragOK;
		std::cout << "  Status: " << status << std::endl;
		if (!fragOK) return false;

		s_TextureShaderProgram = new GLShaderProgram(s_TextureVertFrag[0], s_TextureVertFrag[1]);
		bool progOK = s_TextureShaderProgram->Created();
		std::cout << "Shader Program linking status: " << progOK << std::endl;
		if (!progOK) return false;
		s_TextureBlitMat = new Material(s_TextureShaderProgram);
		return  true;
	}

	bool GLRenderer::Initialize(const int width, const int height, const HWND handle)
	{
		// WINDOWS-SPECIFIC PART
		s_hWnd = handle;
		if ((s_hDevCtx = GetDC(s_hWnd)) == NULL) return false;
		if (!KLMSetPixelFormat(s_hDevCtx)) return false;
		if ((s_hGLRC = wglCreateContext(s_hDevCtx)) == NULL) return false;
		wglMakeCurrent(s_hDevCtx, s_hGLRC);
		// \WINDOWS SPECIFIC PART

		glewInit();
		
		s_ScreenWidth = width;
		s_ScreenHeight = height;
		// set defaults
		EnableDepthTest();
		SetCullMode(CullMode::NONE);
		//SetFillMode(FillMode::WIREFRAME);
		EnableAlphaBlending();
	//	glEnable(GL_MULTISAMPLE);
	//	glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
		glViewport(0, 0, width, height);
		s_QuadMesh = GeometryGenerator::GenerateQuad(2.0, 2.0);
		SetUpShaders();
		glGenFramebuffers(1, &s_BlitFrameBuffer) ;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		s_IsRunning = true;
		return true;
	}

	void GLRenderer::ResizeWindow(unsigned width, unsigned height)
	{
		
		if (height < 10) height = 100;
		if (width < 10) width = 100;
		s_ScreenWidth = width;
		s_ScreenHeight = height;
		glViewport(0, 0, width, height);
	}

	void GLRenderer::RenderAllPasses(ListOfEntities* entities)
	{
	/*	for (int i = 0; i < s_RenderPassList.Count(); ++i)
		{
			RenderPass(s_RenderPassList[i].get(), entities);
		}*/

		for (int i = 0; i < s_CameraList.Count(); ++i)
		{
			RenderPass(s_CameraList[i], entities);
		}

		GLRenderer::SwapBuffers();
	}

	void GLRenderer::RenderPass(RARenderPass* pass, ListOfEntities* entities)
	{
		/*if (pass->GetRenderTarget()) { pass->GetRenderTarget()->Bind(); }
		else { GLRenderTarget::SetScreen(s_ScreenWidth, s_ScreenHeight); }

		if (pass->GetClearMode() == ClearMode::COLOR) { ClearScreen(pass->GetClearColor(), pass->GetClearDepthFlag()); }

		for (int i = 0; i < entities->size(); ++i)
		{
			Entity* e = (*entities)[i].get();
			GLRenderer::RenderEntity(e,s_CurrentCamera);
		}*/
		//glFlush();
	}

	void GLRenderer::RenderPass(Camera* camera, ListOfEntities* entities)
	{
#ifdef ENABLE__CAMERAS_WITH_NO_RENDER_TARGET_RENDERS_DIRECTLY_TO_SCREEN
		if (camera->GetRenderTarget() == nullptr)
		{ 
			
			GLRenderTarget::SetScreen(s_ScreenWidth, s_ScreenHeight);
			if (camera->GetClearMode() == ClearMode::COLOR)
			{
				ClearScreen(camera->GetClearColor(), camera->GetClearDepthFlag());
			}

			for (int i = 0; i < entities->size(); ++i)
			{
				Entity* e = (*entities)[i].get();
				GLRenderer::RenderEntity(e,camera);
			}
			camera->OnRender();
			return;
		}	
#endif // ENABLE__CAMERAS_WITH_NO_RENDER_TARGET_RENDERS_DIRECTLY_TO_SCREEN

	
		auto rt = camera->GetRenderTarget();
		if (rt->IsScreen()) { GLRenderTarget::SetScreen(s_ScreenWidth, s_ScreenHeight); }
		else { rt->Bind(); }
		if (camera->GetClearMode() == ClearMode::COLOR)
		{
			ClearScreen(camera->GetClearColor(), camera->GetClearDepthFlag());
		}
		for (int i = 0; i < entities->size(); ++i)
		{
			Entity* e = (*entities)[i].get();
			GLRenderer::RenderEntity(e, camera);
		}

#ifdef ENABLE__AUTOBLIT_TO_POSTPROCESS_TEXTURE
		// if has camera has a postprocess texture but there was no copy callback...
		if (camera->GetRenderTarget()->HasPostprocessTexture() && !camera->OnRender())
		{	
			// do automatic blit
			Blit((GLTexture*)camera->GetRenderTarget()->GetColorAttachment(0),//src: render target (attachement 0)
				(GLTexture*)camera->GetRenderTarget()->GetPostProcessTexture());//dest: postprocess texture	
		}
#else
		camera->OnRender()
#endif
		GLRenderTarget::SetScreen(s_ScreenWidth, s_ScreenHeight);
	}
	
	void GLRenderer::RenderEntity(Entity* entity, Camera* camera)
	{
		Component* c;
        if (!entity->TryGetCachedModel(c))  return;
		ModelComponent* mc = static_cast<ModelComponent*>(c);
		Render(mc, camera, entity->GetTransform(),entity->GetName());
	}

	void GLRenderer::Render(ModelComponent* model, Camera* camera, Transform* transform, const String& name)
	{
		Material* material = model->GetMaterial();
		if (!camera) return;
		Mat4 worldView;
		if (camera->GetParent() == nullptr)
		{
			worldView = camera->GetViewMatrix() * transform->GetWorldMat();
		}
		else
		{
			Entity* parent = camera->GetParent();
			parent->CalculateTransform();
			camera->SetTransformMatrix(parent->GetTransform()->GetWorldMat());
			worldView = camera->GetViewMatrix() * transform->GetWorldMat();
		}
		const Mat4 MVP = camera->GetProjectionMatrix(s_ScreenWidth, s_ScreenHeight) * worldView;
		material->Use();
#ifdef ENABLE__uWORLD
		material->GetShaderProgram()->SetMat4x4("uWORLD", transform->GetWorldMat());
#endif // ENABLE__uWORLD
#ifdef ENABLE__uWORLD_INVERSE
		material->GetShaderProgram()->SetMat4x4("uWORLD_INVERSE", glm::inverse(transform->GetWorldMat()));
#endif // ENABLE__uWORLD_INVERSE
#ifdef ENABLE__uVIEW
		material->GetShaderProgram()->SetMat4x4("uVIEW", camera->GetViewMatrix());
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
		material->UnbindTextures();
	}

	void GLRenderer::Update(const float deltaTime, const float totalTime)
	{
		s_TotalTime = totalTime;
	}

	void GLRenderer::ShutDown()
	{
		//s_RenderPassList.Free();
		//s_RenderPassList.Clear();
		// release device context
		delete s_TextureBlitMat;
		delete s_TextureShaderProgram;
		delete s_TextureVertFrag[0];
		delete s_TextureVertFrag[1];
		s_CameraList.Free();
		s_CameraList.Clear();
		glDeleteFramebuffers(1, &s_BlitFrameBuffer);
		ReleaseDC(s_hWnd, s_hDevCtx);
		// default to no context
		wglMakeCurrent(0, 0);
		// delete GL context0
		wglDeleteContext(s_hGLRC);
		// delete device context
		DeleteDC(s_hDevCtx);
	}

	void GLRenderer::ClearScreen(const ColorRGB& colour, bool clearDepth)
	{
		glClearColor(colour.r, colour.g, colour.b, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | (GL_DEPTH_BUFFER_BIT*(int)clearDepth));	
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
			glEnable(GL_CULL_FACE);
			s_CullMode = GL_FRONT_AND_BACK;
			glCullFace(s_CullMode);
			break;
		case(CullMode::FRONT):
			glEnable(GL_CULL_FACE);
			s_CullMode = GL_FRONT;
			glCullFace(s_CullMode);
			break;
		case(CullMode::BACK):
			glEnable(GL_CULL_FACE);
			s_CullMode = GL_BACK;
			glCullFace(s_CullMode);
			break;
		case(CullMode::NONE):
			glDisable(GL_CULL_FACE);
			break;
		default:
			break;
		}		
	}

	void GLRenderer::SetFillMode(const FillMode mode)
	{
		switch (mode)
		{
		case(FillMode::SOLID):
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case(FillMode::WIREFRAME):
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		default:
			break;
		}
	}

	void GLRenderer::SetActiveCamera(Camera * camera)
	{
		s_CurrentCamera = camera;
	}

	void GLRenderer::EnableAlphaBlending(bool enabled)
	{
		if (enabled) 
		{ 
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			return;
		}
		glDisable(GL_BLEND);
	}

	void GLRenderer::EnableDepthTest(bool enabled, DepthQualifier qualifier)
	{
		if (enabled)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(DEPTH_QALIF_LUT_GL[static_cast<int>(qualifier)]);
			std::cout << static_cast<unsigned>(qualifier);
			return;
		}
		glDisable(GL_DEPTH_TEST);
	}
	void GLRenderer::AddRenderPass(std::unique_ptr<RARenderPass> pass)
	{
		//s_RenderPassList.GetStdVectorRef().push_back(std::move(pass));
	}
	void GLRenderer::ClearRenderPassList()
	{
		//s_RenderPassList.Clear();
		s_CameraList.Clear();
	}
	void GLRenderer::Blit(GLTexture* src, GLTexture* dest)
	{
		//bind buffer
		glBindFramebuffer(GL_FRAMEBUFFER, s_BlitFrameBuffer);
		//set destination
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, dest->GetID(), 0);
		//set source
		s_TextureBlitMat->Use();
		s_TextureBlitMat->GetShaderProgram()->SetTexture("_sourceTex", src);
		//quad model draw
		s_QuadMesh->GetVBO()->Draw(PrimitiveType::TRIANGLES);
		//clean up
		s_TextureBlitMat->UnbindTextures();
	}
	void GLRenderer::Blit(GLTexture* src, GLTexture* dest, Material* mat)
	{
		//bind buffer
		glBindFramebuffer(GL_FRAMEBUFFER, s_BlitFrameBuffer);
		//set destination
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, dest->GetID(), 0);
		//set source
		mat->Use();
		mat->GetShaderProgram()->SetTexture("_sourceTex", src);
		//quad model draw
		s_QuadMesh->GetVBO()->Draw(PrimitiveType::TRIANGLES);
		//clean up
		mat->UnbindTextures();
	}
}