#pragma once

#include <SFML/Graphics.hpp>
#include "AppEngine.hpp"

namespace OwllCraft
{
	class Flash
	{
	public:
		Flash(AppDataRef data);
		~Flash() = default;

		void show(float deltaTime);
		void draw();

	private:
		AppDataRef mData;

		sf::RectangleShape mShape;

		bool mFlashOn;
	};
}