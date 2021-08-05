#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "AppEngine.hpp"
#include "Scene.hpp"
#include "Collision.hpp"

// Game Scene:
#include "GameOverScene.hpp"

// Game Objects:
#include "Land.hpp"
#include "Pillar.hpp"
#include "Player.hpp"

// Transition Effect
#include "Flash.hpp"

namespace OwllCraft {
	class GameScene : public Scene {
	public:
		GameScene(AppDataRef data)
			: mData(data) {}
		~GameScene() {
			delete mLand;
			delete mPillar;
			delete mPlayer;
			delete mFlash;
		}

		void init() override;
		void handleInput() override;
		void update(float deltaTime) override;
		void draw(float deltaTime) override;

	private:
		void gameObjectInit();
		void backgroundInit();
		void objectCollision();
		void scoreTextInit();
		void pressStartInit();
		void soundFXInit();

	private:
		// Show:
		void showScoreText();
		void showPressStartLabel();

		// Hide:
		void hideScoreText();
		void hidePressStartLabel();
	private:
		enum GameState {
			eReady,
			eGameplay,
			eGameOver
		};

	private:
		AppDataRef mData;
		sf::Clock mGameClock;
		sf::Clock mGameJuiceTime;

		// Sound Effects:
		sf::SoundBuffer mHitBufferSfx, mPointBufferSfx, mWingBufferSfx;
		sf::Sound mHitSfx, mPointSfx, mWingSfx;

		// Background Sprite:
		sf::Sprite mBackground;
		sf::Texture mBackgroundTex;

		// Game Objects:
		Land* mLand;
		Pillar* mPillar;
		Player* mPlayer;

		// HUD:
		sf::Font mGameFont;
		sf::Text mScoreText;
		sf::Text mPressStart;

		// Transition Effect:
		Flash* mFlash;

		// Game System:
		Collision mCollision;
		int mGameState;
		int mScore;
	};
}