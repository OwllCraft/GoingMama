#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "AppEngine.hpp"


namespace OwllCraft {
	class Land
	{
	public:
		Land(AppDataRef data);

		void moveLand(float deltaTime);
		void drawLand();

		const std::vector<sf::Sprite>& getSprites() const;
	private:
		AppDataRef mData;

		sf::Texture mLandTex;

		std::vector<sf::Sprite> mLandSprites;
	};
}