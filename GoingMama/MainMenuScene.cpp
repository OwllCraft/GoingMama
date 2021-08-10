#include "MainMenuScene.hpp"
#include "GameScene.hpp"
#include "DEFINITIONS.hpp"
#include <cmath>

// #include <iostream> // Debugging Purposes

namespace OwllCraft {
	void MainMenuScene::init() {
		// Button Sfx Init:
		mButtonBufferSfx.loadFromFile(_BUTTON_SFX_FILEPATH_);
		mButtonClickSfx.setBuffer(mButtonBufferSfx);

		// Background Initialize:
		mBackgroundTex.loadFromFile(_MAINMENU_BACKGROUND_FILEPATH_);
		mBackground.setTexture(mBackgroundTex);

		// Game Title:
		mGameTitleTex.loadFromFile(_GAME_TITLE_);
		mGameTitle.setTexture(mGameTitleTex);
		mGameTitle.setPosition((_SCREEN_WIDTH_ / 2) - (mGameTitle.getGlobalBounds().width / 2), mGameTitle.getGlobalBounds().height / 3);
		
		// Play Button:
		mPlayButtonTex.loadFromFile(_PLAY_BUTTON_FILEPATH_);
		mPlayButton.setTexture(mPlayButtonTex);
		mPlayButton.setPosition((_SCREEN_WIDTH_ / 2) - (mPlayButton.getGlobalBounds().width / 2), (_SCREEN_HEIGHT_ / 2) - (mPlayButton.getGlobalBounds().height / 2) * 0.09f);
	}

	void MainMenuScene::handleInput() {
		sf::Event evnt;

		while (this->mData->window.pollEvent(evnt)) {
			if (sf::Event::Closed == evnt.type) {
				this->mData->window.close();
			}
			if (this->mData->input.isSpriteClicked(mPlayButton, sf::Mouse::Left, this->mData->window)) {
				mButtonClickSfx.play();
				this->mData->scene.changeScene(SceneRef(new GameScene(this->mData)));
			}
		}
	}

	void MainMenuScene::update(float deltaTime) {

	}

	void MainMenuScene::draw(float deltaTime) {
		this->mData->window.clear();
		this->mData->window.draw(mBackground);
		this->mData->window.draw(mGameTitle);
		this->mData->window.draw(mPlayButton);
		this->mData->window.display();
	}
}