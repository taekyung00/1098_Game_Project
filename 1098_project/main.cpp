
#include "raylib.h"
#include "Engine/Engine.h"
#include "Game/Mode1.h"
#include "Game/Splash.h"


int main(void) {

    Engine& engine = Engine::Instance();
    engine.Start("10..9..8..");

    Splash splash;
    engine.GetGameStateManager().AddGameState(splash);
    Mode1 mode1;
    engine.GetGameStateManager().AddGameState(mode1);
    Mode1 mode2;
    engine.GetGameStateManager().AddGameState(mode2);
    

    while (engine.HasGameEnded() == false) {
        engine.Update();
    }

    engine.Stop();

	return 0;
}