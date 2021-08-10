#include "DEFINITIONS.hpp"
#include "AppEngine.hpp"
#include <Windows.h>

/*****************************
 Written By - Jerico G. Despe
			aka ( OwllCraft )

 Originally published Since:
			August 6, 2021

 Last Update Since:
			August 10, 2021
******************************/

void hideConsole() {
	HWND myConsole = GetConsoleWindow();
	ShowWindow(myConsole, 0);
}

int main() {
	hideConsole();
    OwllCraft::AppEngine game(_SCREEN_WIDTH_, _SCREEN_HEIGHT_, "GoingMama");
    return 0;
}