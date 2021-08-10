#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "AppEngine.hpp"
#include "Scene.hpp"

// Scenes
#include "GameScene.hpp"

namespace OwllCraft {
	class GameOverScene : public Scene {
	public:
		GameOverScene(AppDataRef data, const int score)
			: mData(data), mScore(score) {}

		void init() override;
		void handleInput() override;
		void update(float deltaTime) override;
		void draw(float deltaTime) override;

	private:
		void updateHighScore();
		void medalInit();
	private:
		AppDataRef mData;

		int mScore;
		int mHighScore;

		// Button SFX:
		sf::SoundBuffer mButtonBufferSfx;
		sf::Sound mButtonClickSfx;

		// Medal SFX:
		sf::SoundBuffer mMedalBufferSfx;
		sf::Sound mMedalSfx;

		// Font:
		sf::Font mGameFont;
		sf::Text mScoreText;
		sf::Text mHighScoreText;

		// Background:
		sf::Texture mBackgroundTex;
		sf::Sprite mBackground;

		// Game Over Title:
		sf::Texture mGameOverTitleTex;
		sf::Sprite mGameOverTitle;

		// Game Over Panel:
		sf::Texture mGameOverPanelTex;
		sf::Sprite mGameOverPanel;

		// Retry Button:
		sf::Texture mRetryButtonTex;
		sf::Sprite mRetryButton;

		// Medal sprites
		sf::Texture mMedalTex;
		sf::Sprite mMedal;
	};
}