/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written  consent is prohibited
File Name:   Engine.cpp
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    March 11, 2025
*/

#include "Engine.h"

Engine::Engine() :
    last_tick(std::chrono::system_clock::now()),
#ifdef _DEBUG
    logger(CS230::Logger::Severity::Debug, true,last_tick)
#else
    logger(CS230::Logger::Severity::Event, false, last_tick )
#endif
{}

void Engine::Start(std::string window_title) {
    logger.LogEvent("Engine Started"); //why use logevent? --> we can use this either severity is debug or severity is event, and it is just important event..
    window.Start(window_title);
    //Start other services
    last_test = last_tick;
}

void Engine::Stop() {
    //Stop all services
    logger.LogEvent("Engine Stopped");
}

void Engine::Update() {   

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    double dt = std::chrono::duration<double>(now - last_tick).count();

    if (dt >(1 / TargetFPS)) {
        logger.LogVerbose("Engine Update");
        last_tick = now;

        frame_count++;

        if (frame_count >= FPSTargetFrames) {
            double actual_time = std::chrono::duration<double>(now - last_test).count();
            logger.LogDebug("FPS: " + std::to_string(frame_count/actual_time));
            frame_count = 0;
            last_test = now;
        }
        gamestatemanager.Update(dt);
        input.Update();
        window.Update();        
    }
    
    //Update other services
    

}

bool Engine::HasGameEnded()
{
    if (gamestatemanager.HasGameEnded() == true || window.IsClosed() == true) {
        return true;
    }
    else {
        return false;
    }
    
}
