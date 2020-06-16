#include "stdafx.h"
#include "Constants.h"

const std::string LEADERBOARD_PATH = "Config/leaderboard.txt";
const std::string GAME_STATS_PATH = "Config/gamestats.txt";
const std::string SFML_WINDOW_SETTINGS_PATH = "Config/render_window_settings.txt";
const int MAX_NUM_OF_SCORES = 10;
const std::map<const std::string, const std::string> TEXTRUE_PATHS =
{
	{"DEFAULT_PLAYER", "Resources/Images/motorbiker.png"},
	{"BLUE_PLAYER", "Resources/Images/motorbiker-blue.png"},
	{"DELOREAN_PLAYER", "Resources/Images/delorean.png"},
	{"RED_CAR", "Resources/Images/CarFramesRed.png"},
	{"YELLOW_CAR", "Resources/Images/CarFramesYellow.png"},
	{"ORANGE_CAR", "Resources/Images/CarFramesOrange.png"},
	{"GAME_BACKGROUND", "Resources/Images/GameBackground.png"},
	{"GAME_BACKGROUND_PINK", "Resources/Images/GameBackgroundPink.png"},
	{"GAME_BACKGROUND_DESERT", "Resources/Images/GameBackgroundDesert.png"},
	{"HEART", "Resources/Images/Heart.png"},
	{"COLLISION", "Resources/Images/CrashCartoon.png"},
	{"SHOP_BACKGROUND", "Resources/Images/shopbackground.jpg"},
	{"COIN", "Resources/Images/coin.png"},
	{"COINS", "Resources/Images/coins.png"},
	{"POTHOLE", "Resources/Images/pothole2.png"}
};
const std::map<const std::string, const std::string> AUDIO_PATHS =
{
	{"CRASH", "Resources/Audio/crash2.wav"},
	{"COIN", "Resources/Audio/coin.wav"},
	{"WOOSH", "Resources/Audio/woosh.wav"},
	{"CLICK", "Resources/Audio/click.wav"},
	{"TECHNO_BACKGROUND", "Resources/Audio/music-loop.wav"},
	{"CAR_PASSING", "Resources/Audio/car-passing.wav"},
	{"REVING", "Resources/Audio/engine_reving.wav"},
	{"SKID", "Resources/Audio/skid.wav"}
};
const std::map<const std::string, const std::string> FONT_PATHS =
{
	{"DOSIS-BOLD", "Resources/Fonts/Dosis-Bold.ttf"},
	{"DOSIS-BOOK", "Resources/Fonts/Dosis-Book.ttf"},
	{"DOSIS-EXTRABOLD", "Resources/Fonts/Dosis-ExtraBold.ttf"},
	{"DOSIS-EXTRALIGHT", "Resources/Fonts/Dosis-ExtraLight.ttf"},
	{"DOSIS-LIGHT", "Resources/Fonts/Dosis-Light.ttf"},
	{"DOSIS-MEDIUM", "Resources/Fonts/Dosis-Medium.ttf"},
	{"DOSIS-SEMIBOLD", "Resources/Fonts/Dosis-ExtraLight.ttf"}
};