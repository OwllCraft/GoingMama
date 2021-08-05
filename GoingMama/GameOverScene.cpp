#include "GameOverScene.hpp"
#include "DEFINITIONS.hpp"

#include <sstream>
#include <fstream>

namespace OwllCraft {
	void GameOverScene::init() {
		updateHighScore();

		// Background Init:
		mBackgroundTex.loadFromFile(_GAMEOVER_BACKGROUND_FILEPATH_);
		mBackground.setTexture(mBackgroundTex);

		// Game Over Panel:
		mGameOverPanelTex.loadFromFile(_GAME_OVER_PANEL_);
		mGameOverPanel.setTexture(mGameOverPanelTex);
		mGameOverPanel.setPosition((this->mData->window.getSize().x / 2) - (mGameOverPanel.getGlobalBounds().width / 2), (this->mData->window.getSize().y / 2) - (mGameOverPanel.getGlobalBounds().height / 2));

		// Game Over Title:
		mGameOverTitleTex.loadFromFile(_GAME_OVER_TITLE_);
		mGameOverTitle.setTexture(mGameOverTitleTex);
		mGameOverTitle.setPosition((this->mData->window.getSize().x / 2) - (mGameOverTitle.getGlobalBounds().width / 2), mGameOverPanel.getPosition().y - (mGameOverTitle.getGlobalBounds().height * 1.2f));

		// Retry Button Init:
		mRetryButtonTex.loadFromFile(_RETRY_BUTTON_FILEPATH_);
		mRetryButton.setTexture(mRetryButtonTex);
		mRetryButton.setPosition((this->mData->window.getSize().x / 2) - (mRetryButton.getGlobalBounds().width / 2), mGameOverPanel.getPosition().y + mGameOverPanel.getGlobalBounds().height + (mRetryButton.getGlobalBounds().height * 0.2));

		// Score Text:
		mGameFont.loadFromFile(_GAME_FONT_FILEPATH_);
		mScoreText.setFont(mGameFont);
		mScoreText.setString(std::to_string(mScore));
		mScoreText.setFillColor(sf::Color::White);
		mScoreText.setCharacterSize(48);
		mScoreText.setOrigin(mScoreText.getGlobalBounds().width / 2, mScoreText.getGlobalBounds().height / 2);
		mScoreText.setPosition((mGameOverPanel.getPosition().x + mGameOverPanel.getGlobalBounds().width) - 85.f, mGameOverPanel.getPosition().y + 40.f);

		// Highscore Text:
		mHighScoreText.setFont(mGameFont);
		mHighScoreText.setString(std::to_string(mHighScore));
		mHighScoreText.setFillColor(sf::Color::White);
		mHighScoreText.setCharacterSize(48);
		mHighScoreText.setOrigin(mHighScoreText.getGlobalBounds().width / 2, mHighScoreText.getGlobalBounds().height / 2);
		mHighScoreText.setPosition((mGameOverPanel.getPosition().x + mGameOverPanel.getGlobalBounds().width) - 85.f, mGameOverPanel.getPosition().y + 40.f * 3.2f);
	}

	void GameOverScene::handleInput() {
		sf::Event evnt;

		while (this->mData->window.pollEvent(evnt)) {
			if (sf::Event::Closed == evnt.type) {
				this->mData->window.close();
			}
			if (this->mData->input.isSpriteClicked(mRetryButton, sf::Mouse::Left, this->mData->window)) {
				this->mData->scene.changeScene(SceneRef(new GameScene(this->mData)));
			}
		}
	}

	void GameOverScene::update(float deltaTime) {

	}

	void GameOverScene::draw(float deltaTime) {
		this->mData->window.clear();
		this->mData->window.draw(mBackground);
		this->mData->window.draw(mGameOverTitle);
		this->mData->window.draw(mGameOverPanel);
		this->mData->window.draw(mScoreText);
		this->mData->window.draw(mHighScoreText);
		this->mData->window.draw(mRetryButton);
		this->mData->window.display();
	}

	void GameOverScene::updateHighScore() {
		std::ifstream readFile;
		readFile.open("Player Data/Player_CurrentHighScore.txt");
		if (readFile.is_open()){
			while (!readFile.eof()) {
				readFile >> mHighScore;
			}
		}
		readFile.close();

		std::ofstream writeFile;
		writeFile.open("Player Data/Player_CurrentHighScore.txt");
		if (writeFile.is_open()) {
			if (mScore > mHighScore) {
				mHighScore = mScore;
			}
			writeFile << mHighScore;
		}
		writeFile.close();
	}
}