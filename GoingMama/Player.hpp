#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "AppEngine.hpp"

namespace OwllCraft {
	class Player {
	public:
		Player(AppDataRef data);

		void draw();
		void animate(float deltaTime);
		void update(float deltaTime);
		void tap();
		const sf::Sprite& getSprite() const;

	private:
		enum PlayerState {
			eStill = 1,
			eFlying = 2,
			eFalling = 3
		};
	private:
		AppDataRef mData;
		sf::Sprite mPlayerSprite;
		std::vector<sf::Texture> mAnimationFrames;

		size_t mAnimationIterator;

		sf::Clock mPlayerClock;
		sf::Clock mMovementClock;

		int mPlayerState;
		float mRotation;
	};
}