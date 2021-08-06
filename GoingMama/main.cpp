#include "DEFINITIONS.hpp"
#include "AppEngine.hpp"
#include <Windows.h>

void hideConsole() {
	HWND myConsole = GetConsoleWindow();
	ShowWindow(myConsole, 0);
}

int main() {
	hideConsole();
    OwllCraft::AppEngine game(_SCREEN_WIDTH_, _SCREEN_HEIGHT_, "GoingMama");
    return 0;
}