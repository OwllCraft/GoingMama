#include "AppEngine.hpp"
#include "SplashScene.hpp"

#include <stdlib.h>
#include <time.h>

namespace OwllCraft {
	AppEngine::AppEngine(unsigned int screen_width, unsigned int screen_height, std::string app_title) {
		srand(time(NULL));

		mData->window.create(sf::VideoMode(screen_width, screen_height), app_title, sf::Style::Close | sf::Style::Titlebar);
		mData->scene.changeScene(SceneRef(new SplashScene(this->mData)));

		this->run();
	}

	void AppEngine::run() {
		float newTime, frameTime, interpolation;

		float currentTime = this->mAppTimer.getElapsedTime().asSeconds();
		float accumulator = 0.f;

		while (this->mData->window.isOpen()) {
			this->mData->scene.processSceneChanges();

			newTime = this->mAppTimer.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
				frameTime = 0.25f;

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= mDeltaTime) {
				this->mData->scene.getActiveScene()->handleInput();
				this->mData->scene.getActiveScene()->update(mDeltaTime);

				accumulator -= mDeltaTime;
			}

			interpolation = accumulator / mDeltaTime;
			this->mData->scene.getActiveScene()->draw(interpolation);
		}
	}
}