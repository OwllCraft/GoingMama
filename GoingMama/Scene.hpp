#pragma once

namespace OwllCraft {
	class Scene {
	public:
		virtual void init() = 0;
		virtual void handleInput() = 0;
		virtual void update(float deltaTime) = 0;
		virtual void draw(float deltaTime) = 0;

		virtual void pause() {}
		virtual void resume() {}
	};
}