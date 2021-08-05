#pragma once


/*****************************
		Main Options
******************************/
// Window Size:
#define _SCREEN_WIDTH_ 384
#define _SCREEN_HEIGHT_ 768

/*****************************
		Game System
******************************/
// Scene Timer:
#define _SPLASH_SHOW_TIME_ 0.f
#define _GAME_OVER_SHOW_TIME_ 1.5f

#define _PILLAR_MOVEMENT_SPEED_ 200.0f
#define _PILLAR_SPAWN_FREQUENCY_ 1.5f

#define _GRAVITY_ 350.f

// Player:
#define _PLAYER_ANIMATION_DURATION_ 0.4f
#define _FLYING_SPEED_ 350.f
#define _FLYING_DURATION_ 0.25f
#define _ROTATION_SPEED_ 100.f

// Transition Effects:
#define _FLASH_SPEED_ 1500.0f

/*****************************
		Sprite Assets
******************************/

// Background:
#define _SPLASH_BACKGROUND_FILEPATH_ "Resources/Sprites/background.png"
#define _MAINMENU_BACKGROUND_FILEPATH_ "Resources/Sprites/background.png"
#define _GAMEPLAY_BACKGROUND_FILEPATH_ "Resources/Sprites/background.png"
#define _GAMEOVER_BACKGROUND_FILEPATH_ "Resources/Sprites/background.png"

// Player Sprite:
#define _PLAYER_FRAME_1_ "Resources/Sprites/player1.png"
#define _PLAYER_FRAME_2_ "Resources/Sprites/player2.png"
#define _PLAYER_FRAME_3_ "Resources/Sprites/player3.png"
#define _PLAYER_FRAME_4_ "Resources/Sprites/player4.png"
#define _PLAYER_FRAME_5_ "Resources/Sprites/player5.png"

// Title Sprite:
#define _GAME_TITLE_ "Resources/Sprites/gameTitle.png"
#define _GAME_OVER_TITLE_ "Resources/Sprites/gameOverTitle.png"

// Game Objects:
#define _LAND_FILEPATH_ "Resources/Sprites/land.png"
#define _PILLAR_BOTTOM_ "Resources/Sprites/pillarBottom.png"
#define _PILLAR_TOP_ "Resources/Sprites/pillarTop.png"

// UI Panel:
#define _PLAY_BUTTON_FILEPATH_ "Resources/Sprites/playButton.png"
#define _RETRY_BUTTON_FILEPATH_ "Resources/Sprites/retryButton.png"

// Collision Sprite:
#define _INVISIBLE_PILLAR_FILEPATH_ "Resources/Sprites/invisiblePillar.png"