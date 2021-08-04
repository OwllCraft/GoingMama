#include "Land.hpp"
#include "DEFINITIONS.hpp"

namespace OwllCraft {
	Land::Land(AppDataRef data)
		: mData(data) {
		mLandTex.loadFromFile(_LAND_FILEPATH_);

		sf::Sprite frontLand(mLandTex);
		sf::Sprite backLand(mLandTex);

		frontLand.setPosition(0, this->mData->window.getSize().y - frontLand.getLocalBounds().height);
		backLand.setPosition(frontLand.getLocalBounds().width, this->mData->window.getSize().y - backLand.getLocalBounds().height);

		mLandSprites.push_back(frontLand);
		mLandSprites.push_back(backLand);
	}

	void Land::moveLand(float deltaTime) {
		for (size_t i = 0; i < mLandSprites.size(); i++) {
			sf::Vector2f position = mLandSprites.at(i).getPosition();
			float movement = _PILLAR_MOVEMENT_SPEED_ * deltaTime;

			mLandSprites.at(i).move(-movement, 0.0f);

			if (mLandSprites.at(i).getPosition().x < 0 - mLandSprites.at(i).getLocalBounds().width + 2) {
				sf::Vector2f pos(this->mData->window.getSize().x, mLandSprites.at(i).getPosition().y);
				mLandSprites.at(i).setPosition(pos);
			}
		}
	}

	void Land::drawLand() {
		for (size_t i = 0; i < mLandSprites.size(); i++) {
			this->mData->window.draw(mLandSprites.at(i));
		}
	}

	const std::vector<sf::Sprite>& Land::getSprites() const {
		return mLandSprites;
	}
}