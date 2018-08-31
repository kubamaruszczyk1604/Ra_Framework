#include <iostream>
#include "WindowsApp.h"

struct AtExit
{
	~AtExit()
	{
		_CrtDumpMemoryLeaks();
	}
} doAtExit;

using namespace RA_FRAMEWORK;

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
		//PRINTL("Mouse Move: " + ToString(x) + ", " + ToString(y));
	}
	void OnMouseButtonUp(MouseButton const button)
	{
		PRINTL("Mouse Button Up: " + ToString(static_cast<int>(button)));
	}
	void OnMouseButtonDown(MouseButton const button)
	{
		PRINTL("Mouse Button Down: " + ToString(static_cast<int>(button)));
	}

};



int main()
{
	// Create application in 1280x720 window
	WindowsApp::Create(1280, 720, "EMPTY WINDOW");
	SceneManager::Load(new ExampleScene());
	const int appState = WindowsApp::Run();
	//int* i = new int(10);
	//std::unique_ptr<int> p(i);
	
	WaitForKeypress();

	return 0;
}