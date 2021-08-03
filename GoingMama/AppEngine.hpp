#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "SceneMachine.hpp"
#include "InputManager.hpp"

namespace OwllCraft {
	struct AppData {
		SceneMachine scene;
		sf::RenderWindow window;
		InputManager input;
	};

	typedef std::shared_ptr<AppData> AppDataRef;

	class AppEngine	{
	public:
		AppEngine(unsigned int screen_width, unsigned int screen_height, std::string app_title);
	private:
		// Updates run at 60 per second.
		const float mDeltaTime = 1.f / 60.f;
		sf::Clock mAppTimer;

		AppDataRef mData = std::make_shared<AppData>();

		void run();
	};
}