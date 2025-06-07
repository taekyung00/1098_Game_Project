#pragma once
#ifndef AUDIO_H
#define AUDIO_H

#include <raylib.h>
#include "Component.h"

class Audio : public CS230::Component{
public:
    Audio(const char* filePath);
    ~Audio();

    void Play();
    void Stop();
    void Update();
    void SetLooping(bool loop);

private:
    Music music;
};

#endif
