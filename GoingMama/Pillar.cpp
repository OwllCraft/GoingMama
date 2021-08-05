#include "Pillar.hpp"
#include "DEFINITIONS.hpp"

#include <iostream> // Debugging Purposes

namespace OwllCraft {
	Pillar::Pillar(AppDataRef data)
		: mData(data) {
		mPillarBottomTex.loadFromFile(_PILLAR_BOTTOM_);
		mPillarTopTex.loadFromFile(_PILLAR_TOP_);
		mInvisiblePillarTex.loadFromFile(_INVISIBLE_PILLAR_FILEPATH_);

		sf::Texture landTexture;
		landTexture.loadFromFile(_LAND_FILEPATH_);

		mLandHeight = landTexture.getSize().y;
		mPillarSpawnYOffset = 0;
	}

	void Pillar::spawnBottomPillar() {
		sf::Sprite pillar(mPillarBottomTex);
		pillar.setPosition(this->mData->window.getSize().x, this->mData->window.getSize().y - pillar.getLocalBounds().height - mPillarSpawnYOffset);
		mPillarSprites.push_back(pillar);
	}

	void Pillar::spawnTopPillar() {
		sf::Sprite pillar(mPillarTopTex);
		pillar.setPosition(this->mData->window.getSize().x, -mPillarSpawnYOffset);
		mPillarSprites.push_back(pillar);
	}

	void Pillar::spawnScoringPillar() {
		sf::Sprite pillar(mInvisiblePillarTex);
		pillar.setPosition(this->mData->window.getSize().x, 0);
		mScoringPillars.push_back(pillar);
	}

	void Pillar::movePillars(float deltaTime) {
		// Pillars:
		for (size_t i = 0; i < mPillarSprites.size(); i++) {
			if (mPillarSprites.at(i).getPosition().x < 0 - mPillarSprites.at(i).getLocalBounds().width) {
				mPillarSprites.erase(mPillarSprites.begin() + i);
			}
			else {
				sf::Vector2f position = mPillarSprites.at(i).getPosition();
				float movement = _PILLAR_MOVEMENT_SPEED_ * deltaTime;

				mPillarSprites.at(i).move(-movement, 0);
			}
		}

		// Invisible Scoring Pillars:
		for (size_t i = 0; i < mScoringPillars.size(); i++) {
			if (mScoringPillars.at(i).getPosition().x < 0 - mScoringPillars.at(i).getLocalBounds().width) {
				mScoringPillars.erase(mScoringPillars.begin() + i);
			}
			else {
				sf::Vector2f position = mScoringPillars.at(i).getPosition();
				float movement = _PILLAR_MOVEMENT_SPEED_ * deltaTime;

				mScoringPillars.at(i).move(-movement, 0);
			}
		}
	}

	void Pillar::drawPillars() {
		for (size_t i = 0; i < mPillarSprites.size(); i++) {
			this->mData->window.draw(mPillarSprites.at(i));
		}
	}

	void Pillar::randomizePillarOffset() {
		mPillarSpawnYOffset = rand() % (mLandHeight + 1);
	}

	const std::vector<sf::Sprite>& Pillar::getSprites() const {
		return mPillarSprites;
	}

	std::vector<sf::Sprite>& Pillar::getScoringSprites() {
		return mScoringPillars;
	}
}