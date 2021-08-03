#include "SceneMachine.hpp"

namespace OwllCraft {
	void SceneMachine::changeScene(SceneRef newScene, bool isReplacing) {
		this->mIsAdding = true;
		this->mIsReplacing = isReplacing;
		this->mNewScene = std::move(newScene);
	}

	void SceneMachine::removeScene() {
		this->mIsRemoving = true;
	}

	void SceneMachine::processSceneChanges() {
		if (this->mIsRemoving && !this->mScenes.empty()) {
			this->mScenes.pop();

			if (!this->mScenes.empty())
				this->mScenes.top()->resume();
			
			this->mIsRemoving = false;
		}

		if (this->mIsAdding) {
			if (!this->mScenes.empty()) {
				if (this->mIsReplacing) {
					this->mScenes.pop();
					this->mIsReplacing = false;
				}
					
				else
					this->mScenes.top()->pause();
			}

			this->mScenes.push(std::move(this->mNewScene));
			this->mScenes.top()->init();
			this->mIsAdding = false;
		}
	}

	SceneRef& SceneMachine::getActiveScene() {
		return this->mScenes.top();
	}
}