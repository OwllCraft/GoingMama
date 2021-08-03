#pragma once

#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "AppEngine.hpp"

namespace OwllCraft {
	class SplashScene : public Scene {
	public:
		SplashScene(AppDataRef data)
			: mData(data) {}
		
		void init() override;
		void handleInput() override;
		void update(float deltaTime) override;
		void draw(float deltaTime) override;

	private:
		// Game data:
		AppDataRef mData;

		// Splash Background:
		sf::Sprite mSplashBackground;
		sf::Texture mSplashBackgroundTex;

		// Splash Icon:
	};
}