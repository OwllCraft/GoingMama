#pragma once

#include <SFML/Graphics.hpp>
#include "AppEngine.hpp"
#include "Scene.hpp"

// Scenes
#include "GameScene.hpp"

namespace OwllCraft {
	class GameOverScene : public Scene {
	public:
		GameOverScene(AppDataRef data)
			: mData(data) {}

		void init() override;
		void handleInput() override;
		void update(float deltaTime) override;
		void draw(float deltaTime) override;

	private:
		AppDataRef mData;

		// Background:
		sf::Texture mBackgroundTex;
		sf::Sprite mBackground;

		// Retry Button:
		sf::Texture mRetryButtonTex;
		sf::Sprite mRetryButton;
	};
}