#pragma once

#include <memory>
#include <stack>

#include "Scene.hpp"

namespace OwllCraft {
	typedef std::unique_ptr<Scene> SceneRef;

	class SceneMachine {
	public:
		SceneMachine() {}
		~SceneMachine() {}

		void changeScene(SceneRef newScene, bool isReplacing = true);
		void removeScene();

		// Run at start of each loop in AppEngine.cpp
		void processSceneChanges();

		SceneRef& getActiveScene();

	private:
		std::stack<SceneRef> mScenes;
		SceneRef mNewScene;

		bool mIsRemoving = false, mIsAdding = false, mIsReplacing = false;
	};
}