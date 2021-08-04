#include "GameScene.hpp"
#include "DEFINITIONS.hpp"

namespace OwllCraft {
	void GameScene::init() {
		backgroundInit();
		gameObjectInit();
	}

	void GameScene::handleInput() {
		sf::Event evnt;

		while (this->mData->window.pollEvent(evnt)) {
			if (sf::Event::Closed == evnt.type) {
				this->mData->window.close();
			}
		}
	}

	void GameScene::update(float deltaTime) {
		land->moveLand(deltaTime);
	}

	void GameScene::draw(float deltaTime) {
		this->mData->window.clear();
		this->mData->window.draw(mBackground);
		this->land->drawLand();
		this->mData->window.display();
	}

	void GameScene::backgroundInit() {
		mBackgroundTex.loadFromFile(_GAMEPLAY_BACKGROUND_FILEPATH_);
		mBackground.setTexture(mBackgroundTex);
	}

	void GameScene::gameObjectInit() {
		land = new Land(this->mData);
	}
}