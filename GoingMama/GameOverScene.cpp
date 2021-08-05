#include "GameOverScene.hpp"
#include "DEFINITIONS.hpp"

namespace OwllCraft {
	void GameOverScene::init() {
		// Background Init:
		mBackgroundTex.loadFromFile(_GAMEOVER_BACKGROUND_FILEPATH_);
		mBackground.setTexture(mBackgroundTex);

		// Retry Button Init:
		mRetryButtonTex.loadFromFile(_RETRY_BUTTON_FILEPATH_);
		mRetryButton.setTexture(mRetryButtonTex);
		mRetryButton.setPosition((this->mData->window.getSize().x / 2) - (mRetryButton.getGlobalBounds().width / 2), (this->mData->window.getSize().y / 2) - (mRetryButton.getGlobalBounds().height / 2));
	}

	void GameOverScene::handleInput() {
		sf::Event evnt;

		while (this->mData->window.pollEvent(evnt)) {
			if (sf::Event::Closed == evnt.type) {
				this->mData->window.close();
			}
			if (this->mData->input.isSpriteClicked(mRetryButton, sf::Mouse::Left, this->mData->window)) {
				this->mData->scene.changeScene(SceneRef(new GameScene(this->mData)));
			}
		}
	}

	void GameOverScene::update(float deltaTime) {

	}

	void GameOverScene::draw(float deltaTime) {
		this->mData->window.clear();
		this->mData->window.draw(mBackground);
		this->mData->window.draw(mRetryButton);
		this->mData->window.display();
	}
}