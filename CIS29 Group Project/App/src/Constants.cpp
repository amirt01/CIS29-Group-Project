#include "stdafx.h"
#include "Constants.h"

const std::string LEADERBOARD_PATH = "Config/leaderboard.txt";
const std::string SFML_WINDOW_SETTINGS_PATH = "Config/render_window_settings.txt";
const int MAX_NUM_OF_SCORES = 10;
const std::map<const std::string, const std::string> TEXTRUE_PATHS =
{
	{"MAIN_MENU_BACKGROUND", "Resources/Images/MainMenu.png"},
	{"DEFAULT_PLAYER", "Resources/Images/motorbiker.png"},
	{"BLUE_PLAYER", "Resources/Images/motorbiker-blue.png"},
	{"RED_CAR", "Resources/Images/CarFramesRed.png"},
	{"YELLOW_CAR", "Resources/Images/CarFramesYellow.png"},
	{"ORANGE_CAR", "Resources/Images/CarFramesOrange.png"},
	{"GAME_BACKGROUND", "Resources/Images/GameBackground.png"},
	{"HEART", "Resources/Images/Heart.png"},
	{"COLLISION", "Resources/Images/CrashCartoon.png"},
};
const std::map<const std::string, const std::string> AUDIO_PATHS =
{
	{"CRASH", "Resources/Audio/crash2.wav"},
	{"COIN", "Resources/Audio/coin.wav"},
	{"WOOSH", "Resources/Audio/woosh.wav"}
};