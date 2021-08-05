#include "Player.hpp"
#include "DEFINITIONS.hpp"

namespace OwllCraft {
	Player::Player(AppDataRef data) 
		: mData(data) {
		mAnimationIterator = 0;

		sf::Texture currentFrame;
		currentFrame.loadFromFile(_PLAYER_FRAME_1_);
		mAnimationFrames.push_back(currentFrame);
		currentFrame.loadFromFile(_PLAYER_FRAME_2_);
		mAnimationFrames.push_back(currentFrame);
		currentFrame.loadFromFile(_PLAYER_FRAME_3_);
		mAnimationFrames.push_back(currentFrame);
		currentFrame.loadFromFile(_PLAYER_FRAME_4_);
		mAnimationFrames.push_back(currentFrame);
		currentFrame.loadFromFile(_PLAYER_FRAME_5_);
		mAnimationFrames.push_back(currentFrame);

		mPlayerSprite.setTexture(mAnimationFrames.at(mAnimationIterator));
		mPlayerSprite.setPosition((mData->window.getSize().x / 4) - (mPlayerSprite.getGlobalBounds().width / 2), (mData->window.getSize().y / 2) - (mPlayerSprite.getGlobalBounds().height / 2));
		mPlayerState = PlayerState::eStill;

		sf::Vector2f origin = sf::Vector2f(mPlayerSprite.getGlobalBounds().width / 2, mPlayerSprite.getGlobalBounds().height / 2);

		mPlayerSprite.setOrigin(origin);
		mRotation = 0;
	}

	void Player::draw() {
		this->mData->window.draw(mPlayerSprite);
	}

	void Player::animate(float deltaTime) {
		if (mPlayerClock.getElapsedTime().asSeconds() > _PLAYER_ANIMATION_DURATION_ / mAnimationFrames.size()) {
			if (mAnimationIterator < mAnimationFrames.size() - 1) {
				mAnimationIterator++;
			}
			else {
				mAnimationIterator = 0;
			}

			mPlayerSprite.setTexture(mAnimationFrames.at(mAnimationIterator));
			mPlayerClock.restart();
		}
	}

	void Player::update(float deltaTime) {
		if (PlayerState::eFalling == mPlayerState) {
			mPlayerSprite.move(0, _GRAVITY_ * deltaTime);
			mRotation += _ROTATION_SPEED_ * deltaTime;

			if (mRotation > 25.0f) {
				mRotation = 25.0f;
			}

			mPlayerSprite.setRotation(mRotation);
		}
		else if (PlayerState::eFlying == mPlayerState) {
			mPlayerSprite.move(0, -_FLYING_SPEED_ * deltaTime);
			mRotation -= _ROTATION_SPEED_ * deltaTime;

			if (mRotation < -25.0f) {
				mRotation = -25.0f;
			}

			mPlayerSprite.setRotation(mRotation);
		}

		if (mMovementClock.getElapsedTime().asSeconds() > _FLYING_DURATION_) {
			mMovementClock.restart();
			mPlayerState = PlayerState::eFalling;
		}
	}

	void Player::tap() {
		mMovementClock.restart();
		mPlayerState = PlayerState::eFlying;
	}

	const sf::Sprite& Player::getSprite() const {
		return mPlayerSprite;
	}
}