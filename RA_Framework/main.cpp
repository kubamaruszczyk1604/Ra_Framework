#include <iostream>
#include "WindowsApp.h"
#include "BehaviourComponent.h"
#include "ModelComponent.h"
#include "GLShaderProgram.h"
#include "GLRenderer.h"
#include "ImageLoader.h"
#include "GeometryGenerator.h"
#include "GLSkyBox.h"
using namespace RA_FRAMEWORK;

struct AtExit
{
	~AtExit()
	{ 
		_CrtDumpMemoryLeaks(); 
	}
} doAtExit;

class TestBehaviour : public BehaviourComponent
{
public:
	TestBehaviour():BehaviourComponent("testB") {}
	~TestBehaviour() {}
	void OnStart()
	{
		std::cout << "Behaviour wystartowal" << std::endl;
	}
	void Update(float deltaTime, float totalTime)
	{
		GetParent()->GetTransform()->SetRotationZ(totalTime*0.2f);
	}
	void OnExit()
	{
		std::cout << "Behaviour konczy" << std::endl;
	}
};
void OnCameraRender(Camera* camera, RenderTarget* target, Texture* destination)
{
	std::cout << "On Camera Render" << std::endl;
	//GLRenderer::Blit((GLTexture*)target->GetColorAttachment(0), (GLTexture*)destination, m_pBlitMat);
}
class ExampleScene :public Scene
{
public:
	ExampleScene() :Scene() {}

	~ExampleScene() 
	{
		delete m_pQuadMesh;
		delete m_pMaterial1;
		delete m_pMaterial2;
		delete m_pVertexShader;
		delete m_pFragmentShader;
		delete m_pShaderProg;		
		delete m_pImageLoader;
		delete m_pTexture1;
		delete m_pRenderTexture1;
		delete m_pRenderTexture2;
		delete m_pRenderTarget;
	}

	Mesh*				m_pQuadMesh;
	Material*			m_pMaterial1;
	Material*			m_pMaterial2;
	ModelComponent*		m_pModel1;
	GLShader*			m_pVertexShader;
	GLShader*			m_pFragmentShader;
	GLShaderProgram*	m_pShaderProg;
	Entity*				e1;
	ImageLoader*        m_pImageLoader;
	Texture*			m_pTexture1;
	Texture*			m_pRenderTexture1;
	Texture*			m_pRenderTexture2;
	GLRenderTarget*		m_pRenderTarget;

	

	void OnStart()
	{
		GLSkyBox box;
		String skyStat;
		if (!box.Load("Skyboxes/TestSkybox/skybox.rasky", skyStat))
		{
			std::cout << "Skybox ERROR: " << skyStat << std::endl;
		}
		//m_pBlitMat = new Material()
		PRINTL("OnStart()");
		m_pImageLoader = new ImageLoader();
		// Generate empty image 
		Image image; 
		// Load from file
		std::cout << "Loading image1: " << m_pImageLoader->Load("Textures/test_texture1.png", image) << std::endl;
		// Push to GPU
		m_pTexture1 = new GLTexture(image);
		// Delete from RAM - we won't need it since the GPU has its own copy now
		m_pImageLoader->Free(image);

		// Create render textures for cameras
		TextureFormatDescriptor desc;
		m_pRenderTexture1 = new GLTexture(1280, 720, desc);
		m_pRenderTexture2 = new GLTexture(1280, 720, desc);

		// MESH generation
		//m_pQuadMesh = GeometryGenerator::GenerateSphere(1.0, 15, 15);
		m_pQuadMesh = GeometryGenerator::GenerateQuad(2.0, 2.0, true);
		// Create and compile shaders
		m_pVertexShader = new GLShader(ShaderType::VERTEX);
		m_pVertexShader->LoadFromFile("GLShaders/glVert.txt");
		std::string status;
		std::cout << "Compile Vertex Shader: " << m_pVertexShader->Compile(status);
		std::cout << "  Status: "<< status << std::endl;
		m_pFragmentShader = new GLShader(ShaderType::FRAGMENT);
		m_pFragmentShader->LoadFromFile("GLShaders/glFrag.txt");
		std::cout << "Compile Fragment Shader: " << m_pFragmentShader->Compile(status);
		std::cout << "  Status: " << status << std::endl;
		m_pShaderProg = new GLShaderProgram(m_pVertexShader, m_pFragmentShader);
		std::cout << "Shader Program linking status: " << m_pShaderProg->Created() << std::endl;

	
		m_pMaterial1 = new Material(m_pShaderProg);
		m_pMaterial1->AddShaderVariable("tex1", m_pTexture1);
		
        m_pModel1 = new ModelComponent("model", m_pQuadMesh, m_pMaterial1);
	    e1 = new Entity("Test 1");
	    e1->AddComponent(std::unique_ptr<ModelComponent>(m_pModel1));
		e1->GetTransform()->SetScale(7.5f, 7.5f, 6.0f);
		AddEntity(e1);

		m_pMaterial2 = new Material(m_pShaderProg);
		m_pMaterial2->AddShaderVariable("tex1", m_pRenderTexture1);
		m_pMaterial2->AddShaderVariable("tex2", m_pTexture1);
		//m_pMaterial2->AddShaderVariable("tex1", m_pTexture1);
		ModelComponent* m_pModel2 = new ModelComponent("model2", m_pQuadMesh, m_pMaterial2);
		Entity* e2 = new Entity("Test 2");
		e2->AddComponent(std::unique_ptr<TestBehaviour>(new TestBehaviour()));
		e2->AddComponent(std::unique_ptr<ModelComponent>(m_pModel2));
		e2->GetTransform()->SetPosition(-2.5f, 0.0f, 1.0f);
		AddEntity(e2);
		e1->AddChild(e2);

		Entity* EntityCamera1 = new Entity("Camera1");
		Camera* camera1 = new Camera(ProjectionType::PERSPECTIVE, 80.0f, 0.1f, 1000.0f);
		camera1->SetClearColor(ColorRGB(0.3, 0.3, 0.3));
		//camera1->SetRenderCallback(OnCameraRender);
		std::vector<GLTexture*> ve{ (GLTexture*)m_pRenderTexture1,(GLTexture*)m_pRenderTexture2 };
		m_pRenderTarget = new GLRenderTarget(ve, DeptAttachmentType::DEPTH_TEXTURE, true);
		std::cout << "Render Target status: " << m_pRenderTarget->IsOK() << std::endl;
		//m_pMaterial2->AddShaderVariable("depthSampler", m_pRenderTarget->GetDepthTexture());
		camera1->SetRenderTarget(m_pRenderTarget);
		EntityCamera1->AddComponent(std::unique_ptr<Camera>(camera1));
		EntityCamera1->GetTransform()->SetPosition(Vec3(-3.8f, 0.0f, -14.98f));
		AddEntity(EntityCamera1);

		//m_pMaterial2->AddShaderVariable("tex1", m_pRenderTarget->GetPostProcessTexture());

		Entity* EntityCamera2 = new Entity("Camera2");
		Camera* camera2 = new Camera(ProjectionType::PERSPECTIVE, 80.0f, 0.91f, 1000.0f);
		//camera2->SetClearColor(ColorRGB(0.15, 0.19, 0.94));
		camera2->SetClearMode(ClearMode::COLOR_GRADIENT);
		EntityCamera2->AddComponent(std::unique_ptr<Camera>(camera2));
		EntityCamera2->GetTransform()->SetPosition(Vec3(2.8f, 0.0f, -24.98f));
		AddEntity(EntityCamera2);

		GLRenderer::AddRenderPass(camera1);
		GLRenderer::AddRenderPass(camera2);//renders to screen because camera2 has no render target

		//GLRenderer::SetFillMode(FillMode::WIREFRAME);
		
		/*RARenderPass* pass1 = new RARenderPass(m_pRenderTarget, 0);
		pass1->SetClearColor(ColorRGB(0.3, 0.3, 0.3));
		GLRenderer::AddRenderPass(std::unique_ptr<RARenderPass>(pass1));
		RARenderPass* pass2 = new RARenderPass(nullptr, 1);
		pass2->SetClearColor(ColorRGB(0.15, 0.19, 0.4));
		GLRenderer::AddRenderPass(std::unique_ptr<RARenderPass>(pass2));*/
	}

	void Update(float deltaTime, float totalTime = 0)
	{
		e1->GetTransform()->SetRotationY(totalTime);
	
		//GLRenderer::SwapBuffers();
			//m_pTexture->Bind("tex", m_pShaderProg->GetID(), 0);
	}

	void OnExit()
	{
		PRINTL("OnExit()");
	}

	void PostUpdate() 
	{
		//GLRenderer::ClearScreen(ColorRGB(1.0, 1.0, 1.0));
		
		//GLRenderer::Blit((GLTexture*)m_pRenderTarget->GetColorAttachment(0), (GLTexture*)m_pRenderTarget->GetColorAttachment(1));
		GLRenderer::BlitToScreen((GLTexture*)m_pRenderTarget->GetPostProcessTexture(), 100, 380, 255, 255,1.0);
		GLRenderer::BlitToScreen((GLTexture*)m_pRenderTarget->GetColorAttachment(0),100, 100, 255, 255, 0.5);
		
	}

	//InputCallbacks
	void OnKeyPressed(const int key, const KeyState state)
	{
		if (state == KeyState::PRESSED) SceneManager::Load(new ExampleScene());
	}

	void OnMouseMove(const int x, const int y)
	{
	}

	void OnMouseButtonUp(MouseButton const button)
	{
		WindowsApp::SetFullscreenMode(false);
	}

	void OnMouseButtonDown(MouseButton const button)
	{
		WindowsApp::SetFullscreenMode(true);
	}
};

int main()
{
	WindowsApp::Create(1280, 720, "RA_DEV_WINDOW");
	SceneManager::Load(new ExampleScene());
	const int appState = WindowsApp::Run();
	return appState;
}