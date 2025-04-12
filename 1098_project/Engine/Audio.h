#ifndef AUDIO_H
#define AUDIO_H

#include "raylib.h"

class Audio {
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
