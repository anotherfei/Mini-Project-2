// [main.cpp]
// This is the entry point of your game.
// You can register your scenes here, and start the game.
#include "Engine/GameEngine.hpp"
#include "Engine/LOG.hpp"
#include "Scene/LoseScene.hpp"
#include "Scene/PlayScene.hpp"
#include "Scene/StageSelectScene.hpp"
#include "Scene/WinScene.hpp"
#include "Scene/StartScene.h"
#include "Scene/SettingsScene.hpp"
#include "Scene/LeaderboardScene.hpp"
#include "Scene/ScoreboardScene.hpp"

int main(int argc, char **argv) {
	Engine::LOG::SetConfig(true);
	Engine::GameEngine& game = Engine::GameEngine::GetInstance();

    // TODO HACKATHON-2 (2/3): Register Scenes here
	game.AddNewScene("start", new StartScene());	//ADDED
    game.AddNewScene("stage-select", new StageSelectScene());
	game.AddNewScene("play", new PlayScene());
	game.AddNewScene("lose", new LoseScene());
	game.AddNewScene("win", new WinScene());
	game.AddNewScene("settings", new SettingsScene());	//ADDED
	game.AddNewScene("leaderboard", new LeaderboardScene());	//ADDED
	game.AddNewScene("scoreboard", new ScoreboardScene());	//ADDED

    // TODO HACKATHON-1 (1/1): Change the start scene
	game.Start("start", 90, 1600, 832);
	return 0;
}
