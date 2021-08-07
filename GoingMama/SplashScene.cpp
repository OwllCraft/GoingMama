#include "SplashScene.hpp"
#include "MainMenuScene.hpp"
#include "DEFINITIONS.hpp"

#include <iostream> // Debugging purposes

namespace OwllCraft {
	void SplashScene::init() {
		// Initialize Background:
		mSplashBackgroundTex.loadFromFile(_SPLASH_BACKGROUND_FILEPATH_);
		mSplashBackground.setTexture(mSplashBackgroundTex);

		// Initialize Splash Icon:
		mSplashLogoTex.loadFromFile(_SPLASH_LOGO_);
		mSplashLogo.setTexture(mSplashLogoTex);
		mSplashLogo.setOrigin(mSplashLogo.getGlobalBounds().width / 2, mSplashLogo.getGlobalBounds().height / 2);
		mSplashLogo.setPosition(this->mData->window.getSize().x / 2, (this->mData->window.getSize().y / 2) * 0.8);

		// Initialize Splash Label:
		mSplashLabelTex.loadFromFile(_SPLASH_LABEL_);
		mSplashLabel.setTexture(mSplashLabelTex);
		mSplashLabel.setOrigin(mSplashLabel.getGlobalBounds().width / 2, mSplashLabel.getGlobalBounds().height / 2);
		mSplashLabel.setPosition(this->mData->window.getSize().x / 2, mSplashLogo.getPosition().y + mSplashLogo.getGlobalBounds().height + (mSplashLabel.getGlobalBounds().height / 2) * -4.2f);
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
		if (mClock.getElapsedTime().asSeconds() > _SPLASH_SHOW_TIME_) {
			this->mData->scene.changeScene(SceneRef(new MainMenuScene(this->mData)));
		}
	}

	void SplashScene::draw(float deltaTime) {
		this->mData->window.clear();
		this->mData->window.draw(mSplashBackground);
		this->mData->window.draw(mSplashLogo);
		this->mData->window.draw(mSplashLabel);
		this->mData->window.display();
	}
}