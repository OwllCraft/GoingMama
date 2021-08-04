#pragma once

#include "AppEngine.hpp"
#include "Scene.hpp"
#include <SFML/Graphics.hpp>

namespace OwllCraft {
	class MainMenuScene : public Scene {
	public:
		MainMenuScene(AppDataRef data)
			: mData(data) {}

		void init() override;
		void handleInput() override;
		void update(float deltaTime) override;
		void draw(float deltaTime) override;

	private:
		AppDataRef mData;

		// Background Sprite:
		sf::Sprite mBackground;
		sf::Texture mBackgroundTex;

		// Game Title:
		sf::Sprite mGameTitle;
		sf::Texture mGameTitleTex;

		// Play Button:
		sf::Sprite mPlayButton;
		sf::Texture mPlayButtonTex;
	};
}