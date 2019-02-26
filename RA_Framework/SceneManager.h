#pragma once
#include "Scene.h"
namespace RA_FRAMEWORK
{
	class SceneManager
	{
	private:
		static SceneUniquePtr m_upCurrentScene;
	public:
		SceneManager() = delete;
		SceneManager(const SceneManager&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;
	public:
		//InputCallbacks
		static void		OnKeyPressed(const int key, const KeyState state);
		static void		OnMouseMove(const int x, const int y);
		static void		OnMouseButtonUp(const MouseButton button);
		static void		OnMouseButtonDown(const MouseButton button);
		static void		Update(const float deltaTime, const float totalTime = 0);
	public:
		static void		Initialize();
		static void		Load(Scene* scene);
		static void		ShutDown();
	};
}