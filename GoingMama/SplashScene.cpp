#include "SplashScene.hpp"
#include "DEFINITIONS.hpp"

#include <iostream> // Debugging purposes

namespace OwllCraft {
	void SplashScene::init() {
		// Initialize Background
		mSplashBackgroundTex.loadFromFile(_SPLASH_BACKGROUND_FILEPATH_);

		mSplashBackground.setTexture(mSplashBackgroundTex);
	}

	void SplashScene::handleInput() {
		sf::Event evnt;

		while (this->mData->window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				this->mData->window.close();
				break;
			}
		}
	}

	void SplashScene::update(float deltaTime) {

	}

	void SplashScene::draw(float deltaTime) {
		this->mData->window.clear();
		this->mData->window.draw(mSplashBackground);
		this->mData->window.display();
	}
}