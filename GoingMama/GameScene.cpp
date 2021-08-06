#include "GameScene.hpp"
#include "DEFINITIONS.hpp"

#include <sstream>
#include <iostream> // Debugging purposes

namespace OwllCraft {
	void GameScene::init() {
		// Sprites Initialization:
		backgroundInit();
		gameObjectInit();
		soundFXInit();

		mScore = 0;
		mGameState = GameState::eReady;

		// Font Initialization:
		scoreTextInit();
		pressStartInit();
	}

	void GameScene::handleInput() {
		sf::Event evnt;

		while (this->mData->window.pollEvent(evnt)) {
			if (sf::Event::Closed == evnt.type) {
				this->mData->window.close();
			}
			if (this->mData->input.isSpriteClicked(mBackground, sf::Mouse::Left, this->mData->window)) {
				if (GameState::eGameOver != mGameState) {
					mGameState = GameState::eGameplay;
					mPlayer->tap();
					mWingSfx.play();
				}
			}
		}
	}

	void GameScene::update(float deltaTime) {
		if (mScore > 9) 
			mScoreText.setOrigin(sf::Vector2f((mScoreText.getGlobalBounds().width / 2) - 3.f , mScoreText.getGlobalBounds().height / 2));

		if (GameState::eGameOver != mGameState) {
			mLand->moveLand(deltaTime);
			mSky->moveSkyBlock(deltaTime);
			mPlayer->animate(deltaTime);

			// Game Juice
			if (mGameJuiceTime.getElapsedTime().asSeconds() > _PRESS_START_FREQUENCY_) {
				hidePressStartLabel();

				if (mGameJuiceTime.getElapsedTime().asSeconds() > _PRESS_START_FREQUENCY_ + 0.5f) {
					mGameJuiceTime.restart();
				}
			}
			else {
				showPressStartLabel();
			}
				
			hideScoreText();
		}

		if (GameState::eGameplay == mGameState) {
			showScoreText();
			hidePressStartLabel();

			mPillar->movePillars(deltaTime);

			if (mGameClock.getElapsedTime().asSeconds() > _PILLAR_SPAWN_FREQUENCY_) {
				mPillar->randomizePillarOffset();

				mPillar->spawnBottomPillar();
				mPillar->spawnTopPillar();
				mPillar->spawnScoringPillar();

				mGameClock.restart();
			}

			mPlayer->update(deltaTime);

			objectCollision(); // Game Object Collision
		}

		if (GameState::eGameOver == mGameState) {
			mFlash->show(deltaTime);
			if (mGameClock.getElapsedTime().asSeconds() > _GAME_OVER_SHOW_TIME_) {
				this->mData->scene.changeScene(SceneRef(new GameOverScene(this->mData, mScore)));
			}
		}
	}

	void GameScene::draw(float deltaTime) {
		this->mData->window.clear();
		this->mData->window.draw(mBackground);

		// Draw Game Objects:
		this->mPillar->drawPillars();
		this->mLand->drawLand();
		this->mPlayer->draw();

		this->mData->window.draw(mPressStart);
		this->mData->window.draw(mScoreText);
		this->mFlash->draw();

		this->mData->window.display();
	}

	void GameScene::backgroundInit() {
		mBackgroundTex.loadFromFile(_GAMEPLAY_BACKGROUND_FILEPATH_);
		mBackground.setTexture(mBackgroundTex);
	}

	void GameScene::gameObjectInit() {
		mLand = new Land(this->mData);
		mPillar = new Pillar(this->mData);
		mPlayer = new Player(this->mData);
		mSky = new SkyBlock(this->mData);
		mFlash = new Flash(this->mData);
	}

	void GameScene::soundFXInit() {
		mHitBufferSfx.loadFromFile(_HIT_SFX_FILEPATH_);
		mHitSfx.setBuffer(mHitBufferSfx);

		mPointBufferSfx.loadFromFile(_POINT_SFX_FILEPATH_);
		mPointSfx.setBuffer(mPointBufferSfx);

		mWingBufferSfx.loadFromFile(_WING_SFX_FILEPATH_);
		mWingSfx.setBuffer(mWingBufferSfx);
	}

	void GameScene::objectCollision() {

		// Land Collision:
		std::vector<sf::Sprite> landCollision = mLand->getSprites();
		for (size_t i = 0; i < landCollision.size(); i++) {
			if (mCollision.CheckSpriteCollision(mPlayer->getSprite(), 0.8f, landCollision.at(i), 1.0f)) {
				mGameState = GameState::eGameOver;
				mHitSfx.play();
				mGameClock.restart();
			}
		}

		// Sky Collision
		std::vector<sf::Sprite> skyCollision = mSky->getSprite();
		for (size_t i = 0; i < skyCollision.size(); i++) {
			if (mCollision.CheckSpriteCollision(mPlayer->getSprite(), 0.8f, skyCollision.at(i), 1.0f)) {
				mGameState = GameState::eGameOver;
				mHitSfx.play();
				mGameClock.restart();
			}
		}

		// Pillar Collision:
		std::vector<sf::Sprite> pillarCollision = mPillar->getSprites();
		for (size_t i = 0; i < pillarCollision.size(); i++) {
			if (mCollision.CheckSpriteCollision(mPlayer->getSprite(), 0.4f, pillarCollision.at(i), 1.0f)) {
				mGameState = GameState::eGameOver;
				mHitSfx.play();
				mGameClock.restart();
			}
		}

		// Scoring Collision:
		if (GameState::eGameplay == mGameState) {
			std::vector<sf::Sprite>& scoringCollision = mPillar->getScoringSprites();
			for (size_t i = 0; i < scoringCollision.size(); i++) {
				if (mCollision.CheckSpriteCollision(mPlayer->getSprite(), 0.4f, scoringCollision.at(i), 1.0f)) {
					mScore++;
					scoringCollision.erase(scoringCollision.begin() + i);
					mPointSfx.play();
					mScoreText.setString(std::to_string(mScore));
				}
			}
		}
	}

	void GameScene::scoreTextInit() {
		mGameFont.loadFromFile(_GAME_FONT_FILEPATH_);
		mScoreText.setFont(mGameFont);
		mScoreText.setString("0");
		mScoreText.setCharacterSize(128);
		mScoreText.setOutlineThickness(10.f);
		mScoreText.setOrigin(sf::Vector2f(mScoreText.getGlobalBounds().width / 2, mScoreText.getGlobalBounds().height / 2));
		mScoreText.setPosition(sf::Vector2f(this->mData->window.getSize().x / 2, (this->mData->window.getSize().y / 2) - 150.0f));
	}

	void GameScene::pressStartInit() {
		mPressStart.setFont(mGameFont);
		mPressStart.setString("Press left mouse button\n to play!");
		mPressStart.setCharacterSize(24);
		mPressStart.setOutlineThickness(5.f);
		mPressStart.setOrigin(sf::Vector2f(mPressStart.getGlobalBounds().width / 2, mPressStart.getGlobalBounds().height / 2));
		mPressStart.setPosition((sf::Vector2f((this->mData->window.getSize().x / 2), (this->mData->window.getSize().y / 2) - 150.0f)));
	}

	void GameScene::showScoreText() {
		mScoreText.setFillColor(sf::Color(255, 204, 213));
		mScoreText.setOutlineColor(sf::Color(0, 5, 91));
	}

	void GameScene::showPressStartLabel() {
		mPressStart.setFillColor(sf::Color(255, 204, 213));
		mPressStart.setOutlineColor(sf::Color(0, 5, 91));
	}

	void GameScene::hideScoreText() {
		mScoreText.setFillColor(sf::Color(0, 0, 0, 0));
		mScoreText.setOutlineColor(sf::Color(0, 0, 0, 0));
	}

	void GameScene::hidePressStartLabel() {
		mPressStart.setFillColor(sf::Color(0, 0, 0, 0));
		mPressStart.setOutlineColor(sf::Color(0, 0, 0, 0));
	}
}