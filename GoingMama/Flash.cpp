#include "Flash.hpp"
#include "DEFINITIONS.hpp"

namespace OwllCraft {
	Flash::Flash(AppDataRef data)
		: mData(data) {
		mShape = sf::RectangleShape(sf::Vector2f(mData->window.getSize().x, mData->window.getSize().y));
		mShape.setFillColor(sf::Color(255, 255, 255, 0));

		mFlashOn = true;
	}

	void Flash::show(float deltaTime)
	{
		if (mFlashOn)
		{
			int alpha = (int)mShape.getFillColor().a + (_FLASH_SPEED_ * deltaTime);

			if (alpha >= 255.0f)
			{
				alpha = 255.0f;
				mFlashOn = false;
			}

			mShape.setFillColor(sf::Color(255, 255, 255, alpha));
		}
		else
		{
			int alpha = (int)mShape.getFillColor().a - (_FLASH_SPEED_ * deltaTime);

			if (alpha <= 0.0f)
			{
				alpha = 0.0f;
			}

			mShape.setFillColor(sf::Color(255, 255, 255, alpha));
		}
	}

	void Flash::draw()
	{
		mData->window.draw(mShape);
	}
}