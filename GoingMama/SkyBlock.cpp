#include "SkyBlock.hpp"
#include "DEFINITIONS.hpp"

namespace OwllCraft {
	SkyBlock::SkyBlock(AppDataRef data)
		: mData(data) {
		mSkyBlockTex.loadFromFile(_INVISIBLE_SKY_FILEPATH_);

		sf::Sprite frontSky(mSkyBlockTex);
		sf::Sprite backSky(mSkyBlockTex);

		frontSky.setPosition(0, frontSky.getLocalBounds().height);
		backSky.setPosition(frontSky.getLocalBounds().width, backSky.getLocalBounds().height);

		mSkyBlock.push_back(frontSky);
		mSkyBlock.push_back(backSky);
	}

	void SkyBlock::moveSkyBlock(float deltaTime) {
		for (size_t i = 0; i < mSkyBlock.size(); i++) {
			sf::Vector2f position = mSkyBlock.at(i).getPosition();
			float movement = _PILLAR_MOVEMENT_SPEED_ * deltaTime;

			mSkyBlock.at(i).move(-movement, 0.0f);

			if (mSkyBlock.at(i).getPosition().x < 0 - mSkyBlock.at(i).getLocalBounds().width) {
				sf::Vector2f pos(this->mData->window.getSize().x, mSkyBlock.at(i).getPosition().y);
				mSkyBlock.at(i).setPosition(pos);
			}
		}
	}

	const std::vector<sf::Sprite>& SkyBlock::getSprite() const {
		return mSkyBlock;
	}
}