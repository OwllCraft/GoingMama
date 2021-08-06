#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "AppEngine.hpp"


namespace OwllCraft {
	class SkyBlock {
	public:
		SkyBlock(AppDataRef data);

		void moveSkyBlock(float deltaTime);

		const std::vector<sf::Sprite>& getSprite() const;

	private:
		AppDataRef mData;

		sf::Texture mSkyBlockTex;
		std::vector<sf::Sprite> mSkyBlock;
	};
}