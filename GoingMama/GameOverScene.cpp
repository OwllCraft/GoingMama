#include "GameOverScene.hpp"
#include "DEFINITIONS.hpp"

#include <sstream>
#include <fstream>

// #include <iostream> // Debugging purposes

namespace OwllCraft {
	void GameOverScene::init() {
		updateHighScore();
		medalInit();
		
		// Button SFX Init:
		mButtonBufferSfx.loadFromFile(_BUTTON_SFX_FILEPATH_);
		mButtonClickSfx.setBuffer(mButtonBufferSfx);

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
		mScoreText.setOutlineColor(sf::Color(0, 5, 91));
		mScoreText.setOutlineThickness(5.f);
		mScoreText.setOrigin(mScoreText.getGlobalBounds().width / 2, mScoreText.getGlobalBounds().height / 2);
		mScoreText.setPosition((mGameOverPanel.getPosition().x + mGameOverPanel.getGlobalBounds().width) - 81.f, mGameOverPanel.getPosition().y + 43.f);

		// Highscore Text:
		mHighScoreText.setFont(mGameFont);
		mHighScoreText.setString(std::to_string(mHighScore));
		mHighScoreText.setFillColor(sf::Color::White);
		mHighScoreText.setCharacterSize(48);
		mHighScoreText.setOutlineColor(sf::Color(0, 5, 91));
		mHighScoreText.setOutlineThickness(5.f);
		mHighScoreText.setOrigin(mHighScoreText.getGlobalBounds().width / 2, mHighScoreText.getGlobalBounds().height / 2);
		mHighScoreText.setPosition((mGameOverPanel.getPosition().x + mGameOverPanel.getGlobalBounds().width) - 81.f, mGameOverPanel.getPosition().y + 43.f * 3.11f);

		// Medal Position:
		mMedal.setOrigin(mMedal.getGlobalBounds().width / 2, mMedal.getGlobalBounds().height / 2);
		mMedal.setPosition((mGameOverPanel.getPosition().x + mGameOverPanel.getGlobalBounds().width) - 81.f, mGameOverPanel.getPosition().y + 60.f * 3.8f);
	}

	void GameOverScene::handleInput() {
		sf::Event evnt;

		while (this->mData->window.pollEvent(evnt)) {
			if (sf::Event::Closed == evnt.type) {
				this->mData->window.close();
			}
			if (this->mData->input.isSpriteClicked(mRetryButton, sf::Mouse::Left, this->mData->window)) {
				mButtonClickSfx.play();
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
		this->mData->window.draw(mMedal);
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

	void GameOverScene::medalInit() {
		// Init SFX:
		mMedalBufferSfx.loadFromFile(_MEDAL_SFX_FILEPATH_);
		mMedalSfx.setBuffer(mMedalBufferSfx);
		mMedalSfx.play();

		// Gold Medal:
		if (mScore > 50) {
			mMedalTex.loadFromFile(_GOLD_MEDAL_FILEPATH_);
			mMedal.setTexture(mMedalTex);
		} 

		// Silver Medal:
		else if (mScore > 20) {
			mMedalTex.loadFromFile(_SILVER_MEDAL_FILEPATH_);
			mMedal.setTexture(mMedalTex);
		}

		// Bronze Medal:
		else if (mScore >= 0) { 
			mMedalTex.loadFromFile(_BRONZE_MEDAL_FILEPATH_);
			mMedal.setTexture(mMedalTex);
		}	
	}
}