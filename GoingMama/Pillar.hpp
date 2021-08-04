#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "AppEngine.hpp"

namespace OwllCraft {
	class Pillar {
	public:
		Pillar(AppDataRef data);

		void SpawnBottomPillar();
		void SpawnTopPillar();
		void SpawnInvisiblePillar();
	};
}