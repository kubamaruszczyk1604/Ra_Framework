#include <iostream>
#include "WindowsApp.h"
#include "BehaviourComponent.h"
#include "ModelComponent.h"
#include "GLShaderProgram.h"
#include "GLRenderer.h"
#include "ImageLoader.h"

struct AtExit
{
	~AtExit()
	{
		_CrtDumpMemoryLeaks();
	}
} doAtExit;

using namespace RA_FRAMEWORK;

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
		GetParent()->GetTransform()->SetRotationX(totalTime*3.0f);
	}
	void OnExit()
	{
		std::cout << "Behaviour konczy" << std::endl;
	}
};


class ExampleScene :public Scene
{

public:
	ExampleScene() :Scene()
	{

	}
	~ExampleScene() {}


	void OnStart()
	{
		PRINTL("OnStart()");
		Entity* e1 = new Entity("Test 1");
		e1->AddComponent(std::unique_ptr<TestBehaviour>(new TestBehaviour()));
		e1->GetTransform()->SetPositionY(10.0f);

		Entity* e2 = new Entity("Test 2");
		e2->GetTransform()->SetPositionY(10.0f);
		e1->AddChild(e2);

		Entity* e3 = new Entity("Test 3");
		e3->GetTransform()->SetPositionY(10.0f);
		e2->AddChild(e3);

		AddEntity(e1);
		AddEntity(e2);
		AddEntity(e3);

	}
	void Update(float deltaTime, float totalTime = 0)
	{
		//PRINTL("Update(" + ToString(deltaTime) + ", " + ToString(totalTime) + ")");
	}
	void OnExit()
	{
		PRINTL("OnExit()");
	}

	void PostUpdate() {}

	//InputCallbacks
	void OnKeyPressed(const int key, const KeyState state)
	{
		PRINTL("Key Pressed: " + ToString(key));

		GetEntityManager()->RemoveEntity("Test 3");

		Entity* entity = FindEntity("Test 1");
		if (entity)
		{
			PRINTL("ENTITY: " + entity->GetName());
			Entity* child = entity->FindInChildreen("Test 2");

			if (child)
			{
				PRINTL("CHILD: " + child->GetName());
			}
		}

	}
	void OnMouseMove(const int x, const int y)
	{
	//	//PRINTL("Mouse Move: " + ToString(x) + ", " + ToString(y));
	}
	void OnMouseButtonUp(MouseButton const button)
	{
		PRINTL("Mouse Button Up: " + ToString(static_cast<int>(button)));
	}
	void OnMouseButtonDown(MouseButton const button)
	{
		PRINTL("Mouse Button Down: " + ToString(static_cast<int>(button)));
		WindowsApp::SetFullscreenMode(false);
	}

};


class ExampleScene2 :public Scene
{
public:
	ExampleScene2() :Scene() {}

	~ExampleScene2() 
	{
		delete m_pQuadMesh;
		delete m_pMaterial;
		delete m_pVertexShader;
		delete m_pFragmentShader;
		delete m_pShaderProg;
		
		delete m_pImageLoader;
		delete m_pTexture1;
		delete m_pTexture2;
	}

	Mesh*				m_pQuadMesh;
	Material*			m_pMaterial;
	ModelComponent*		m_pModel;
	GLShader*			m_pVertexShader;
	GLShader*			m_pFragmentShader;
	GLShaderProgram*	m_pShaderProg;
	Camera*				m_pCamera;
	Entity*				e1;
	ImageLoader*        m_pImageLoader;
	GLTexture*          m_pTexture1;
	GLTexture*          m_pTexture2;
	void OnStart()
	{
		PRINTL("OnStart()");
		m_pImageLoader = new ImageLoader();

		Image image;
		std::cout << "Loading image1: " << m_pImageLoader->Load("C:/Zapas/text2.png", image) << std::endl;
		m_pTexture1 = new GLTexture(image.GetWidth(), image.GetHeight(), TextureFormat::UBYTE, (void*)image.GetPixels());
		m_pImageLoader->Free(image);
		std::cout << "Loading image2: " << m_pImageLoader->Load("C:/Zapas/text.png", image) << std::endl;
		m_pTexture2 = new GLTexture(image.GetWidth(), image.GetHeight(), TextureFormat::UBYTE, (void*)image.GetPixels());
		m_pTexture2->SetSlot(1);
		m_pImageLoader->Free(image);
		// MESH
		m_pQuadMesh = new Mesh();
		float size{ 5.5f };
		float fbDist = 0.01f;
		//front
		m_pQuadMesh->AddVertex(Vertex(-size, -size, -fbDist, 0, 0, -1, 0, 0));
		m_pQuadMesh->AddVertex(Vertex(size, -size, -fbDist, 0, 0, -1, 1, 0));
		m_pQuadMesh->AddVertex(Vertex(size, size, -fbDist, 0, 0, -1, 1, 1));
		m_pQuadMesh->AddVertex(Vertex(-size, size, -fbDist, 0, 0, -1, 0, 1));

		std::vector<unsigned> indices;
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);

		m_pQuadMesh->CreateVertexBuffer(indices);

		m_pVertexShader = new GLShader(ShaderType::VERTEX);
		m_pVertexShader->LoadFromFile("C:/Zapas/glVert.txt");
		//m_pVertexShader->LoadFromString(RA_BUILT_IN_SHADERS::GL_Vert_MVPStandard);
		std::string status;
		std::cout << "Compile Vertex Shader: " << m_pVertexShader->Compile(status);
		std::cout << "  Status: "<< status << std::endl;

		m_pFragmentShader = new GLShader(ShaderType::FRAGMENT);
		m_pFragmentShader->LoadFromFile("C:/Zapas/glFrag.txt");
		std::cout << "Compile Fragment Shader: " << m_pFragmentShader->Compile(status);
		std::cout << "  Status: " << status << std::endl;

		m_pShaderProg = new GLShaderProgram(m_pVertexShader, m_pFragmentShader);
		std::cout << "Shader Program linking status: " << m_pShaderProg->Created() << std::endl;

		m_pMaterial = new Material(m_pShaderProg);
		m_pMaterial->AddShaderVariable("aa", Vec3(0.0, 0.0, 1.0));
		m_pMaterial->AddShaderVariable("tex1", m_pTexture1);
		m_pMaterial->AddShaderVariable("tex2", m_pTexture2);
		
        m_pModel = new ModelComponent("model", m_pQuadMesh, m_pMaterial);
	    e1 = new Entity("Test 1");
	    e1->AddComponent(std::unique_ptr<ModelComponent>(m_pModel));
		AddEntity(e1);

		ModelComponent* m_pModel2 = new ModelComponent("model2", m_pQuadMesh, m_pMaterial);
		Entity* e2 = new Entity("Test 2");
		e2->AddComponent(std::unique_ptr<TestBehaviour>(new TestBehaviour()));
		e2->AddComponent(std::unique_ptr<ModelComponent>(m_pModel2));
		e2->GetTransform()->SetScale(0.3f, 0.3f, 1.0f);
		e2->GetTransform()->SetPosition(-8.0f, 0.0f, 0.0f);
		AddEntity(e2);
		e1->AddChild(e2);

		Entity* eCam = new Entity("Camera");
		m_pCamera = new Camera(ProjectionType::PERSPECTIVE, 60.0f, 0.1f, 1000.0f);
		GLRenderer::SetActiveCamera(m_pCamera);
		eCam->AddComponent(std::unique_ptr<Camera>(m_pCamera));
		eCam->GetTransform()->SetPosition(Vec3(-6.8f, 0.0f, -24.98f));
		eCam->CalculateTransform();
		AddEntity(eCam);
		//GLRenderer::SetFillMode(FillMode::WIREFRAME);
	}

	void Update(float deltaTime, float totalTime = 0)
	{
		e1->GetTransform()->SetRotationY(totalTime);
		//m_pTexture->Bind("tex", m_pShaderProg->GetID(), 0);
	}

	void OnExit()
	{
		PRINTL("OnExit()");
	}

	void PostUpdate() {}

	//InputCallbacks
	void OnKeyPressed(const int key, const KeyState state)
	{
	}
	void OnMouseMove(const int x, const int y)
	{
	}
	void OnMouseButtonUp(MouseButton const button)
	{
	}
	void OnMouseButtonDown(MouseButton const button)
	{
	}
};

int main()
{
	WindowsApp::Create(1280, 720, "RA WINDOW");
	//WindowsApp::SetFullscreenMode(true);
	SceneManager::Load(new ExampleScene2());
	const int appState = WindowsApp::Run();

   // WaitForKeypress();
	return appState;
}