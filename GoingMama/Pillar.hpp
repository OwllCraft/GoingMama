#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "AppEngine.hpp"

namespace OwllCraft {
	class Pillar {
	public:
		Pillar(AppDataRef data);

		void spawnBottomPillar();
		void spawnTopPillar();
		void spawnScoringPillar();
		void movePillars(float deltaTime);
		void drawPillars();
		void randomizePillarOffset();

		const std::vector<sf::Sprite>& getSprites() const;
		std::vector<sf::Sprite>& getScoringSprites();

	private:
		AppDataRef mData;

		sf::Texture mPillarBottomTex;
		sf::Texture mPillarTopTex;
		sf::Texture mInvisiblePillarTex;

		std::vector<sf::Sprite> mPillarSprites;
		std::vector<sf::Sprite> mScoringPillars;

		int mLandHeight;
		int mPillarSpawnYOffset;
	};
}