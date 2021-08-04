#pragma once

#include "AppEngine.hpp"
#include "Scene.hpp"
#include <SFML/Graphics.hpp>

// Game Objects:
#include "Land.hpp"

namespace OwllCraft {
	enum GameState {
		eReady,
		eGameplay,
		eGameOver
	};

	class GameScene : public Scene {
	public:
		GameScene(AppDataRef data)
			: mData(data) {}

		void init() override;
		void handleInput() override;
		void update(float deltaTime) override;
		void draw(float deltaTime) override;

	private:
		void gameObjectInit();
		void backgroundInit();

	private:
		AppDataRef mData;

		// Background Sprite:
		sf::Sprite mBackground;
		sf::Texture mBackgroundTex;

		// Game Objects:
		Land* land;
	};
}