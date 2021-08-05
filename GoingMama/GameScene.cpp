#include "GameScene.hpp"
#include "DEFINITIONS.hpp"

#include <iostream> // Debugging purposes

namespace OwllCraft {
	void GameScene::init() {
		backgroundInit();
		gameObjectInit();

		mScore = 0;
		mGameState = GameState::eReady;
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
					player->tap();
				}
			}
		}
	}

	void GameScene::update(float deltaTime) {
		if (GameState::eGameOver != mGameState) {
			land->moveLand(deltaTime);
			player->animate(deltaTime);
		}

		if (GameState::eGameplay == mGameState) {
			pillar->movePillars(deltaTime);

			if (gameClock.getElapsedTime().asSeconds() > _PILLAR_SPAWN_FREQUENCY_) {
				pillar->randomizePillarOffset();

				pillar->spawnBottomPillar();
				pillar->spawnTopPillar();
				pillar->spawnScoringPillar();

				gameClock.restart();
			}

			player->update(deltaTime);

			objectCollision(); // Game Object Collision
		}

		if (GameState::eGameOver == mGameState) {
			flash->show(deltaTime);
			if (gameClock.getElapsedTime().asSeconds() > _GAME_OVER_SHOW_TIME_) {
				this->mData->scene.changeScene(SceneRef(new GameOverScene(this->mData)));
			}
		}
	}

	void GameScene::draw(float deltaTime) {
		this->mData->window.clear();
		this->mData->window.draw(mBackground);

		// Draw Game Objects:
		this->pillar->drawPillars();
		this->land->drawLand();
		this->player->draw();

		this->flash->draw();

		this->mData->window.display();
	}

	void GameScene::backgroundInit() {
		mBackgroundTex.loadFromFile(_GAMEPLAY_BACKGROUND_FILEPATH_);
		mBackground.setTexture(mBackgroundTex);
	}

	void GameScene::gameObjectInit() {
		land = new Land(this->mData);
		pillar = new Pillar(this->mData);
		player = new Player(this->mData);

		flash = new Flash(this->mData);
	}

	void GameScene::objectCollision() {

		// Land Collision:
		std::vector<sf::Sprite> landCollision = land->getSprites();
		for (size_t i = 0; i < landCollision.size(); i++) {
			if (collision.CheckSpriteCollision(player->getSprite(), 0.7f, landCollision.at(i), 1.0f)) {
				mGameState = GameState::eGameOver;
				gameClock.restart();
			}
		}

		// Pillar Collision:
		std::vector<sf::Sprite> pillarCollision = pillar->getSprites();
		for (size_t i = 0; i < pillarCollision.size(); i++) {
			if (collision.CheckSpriteCollision(player->getSprite(), 0.4f, pillarCollision.at(i), 1.0f)) {
				mGameState = GameState::eGameOver;
				gameClock.restart();
			}
		}

		// Scoring Collision:
		if (GameState::eGameplay == mGameState) {
			std::vector<sf::Sprite>& scoringCollision = pillar->getScoringSprites();
			for (size_t i = 0; i < scoringCollision.size(); i++) {
				if (collision.CheckSpriteCollision(player->getSprite(), 0.4f, scoringCollision.at(i), 1.0f)) {
					mScore++;
					scoringCollision.erase(scoringCollision.begin() + i);
					std::cout << mScore << std::endl;
				}
			}
		}
	}
}