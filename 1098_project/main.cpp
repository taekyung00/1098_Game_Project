
#include "raylib.h"
#include "Engine/Engine.h"
#include "Game/InGame.h"
#include "Game/Splash.h"


int main(void) {

    Engine& engine = Engine::Instance();
    engine.Start("10..9..8..");

    Splash splash;
    engine.GetGameStateManager().AddGameState(splash);
    InGame ingame;
    engine.GetGameStateManager().AddGameState(ingame);
    

    while (engine.HasGameEnded() == false) {
        engine.Update();
    }

    engine.Stop();

	return 0;
}