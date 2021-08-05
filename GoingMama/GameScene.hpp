#pragma once

#include "AppEngine.hpp"
#include "Scene.hpp"
#include <SFML/Graphics.hpp>
#include "Collision.hpp"

// Game Scene:
#include "GameOverScene.hpp"

// Game Objects:
#include "Land.hpp"
#include "Pillar.hpp"
#include "Player.hpp"

// HUD:

// Transition Effect
#include "Flash.hpp"

namespace OwllCraft {
	class GameScene : public Scene {
	public:
		GameScene(AppDataRef data)
			: mData(data) {}
		~GameScene() {
			delete land;
			delete pillar;
			delete player;
			delete flash;
		}

		void init() override;
		void handleInput() override;
		void update(float deltaTime) override;
		void draw(float deltaTime) override;

	private:
		void gameObjectInit();
		void backgroundInit();
		void objectCollision();

	private:
		enum GameState {
			eReady,
			eGameplay,
			eGameOver
		};

	private:
		AppDataRef mData;
		sf::Clock gameClock;
		
		// Background Sprite:
		sf::Sprite mBackground;
		sf::Texture mBackgroundTex;

		// Game Objects:
		Land* land;
		Pillar* pillar;
		Player* player;

		// Transition Effect:
		Flash* flash;

		// Game System:
		Collision collision;
		int mGameState;
		int mScore;
	};
}