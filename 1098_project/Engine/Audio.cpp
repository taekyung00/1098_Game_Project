#include "Audio.h"

Audio::Audio(const char* filePath) {
    music = LoadMusicStream(filePath);
}

Audio::~Audio() {
    UnloadMusicStream(music);
    CloseAudioDevice();
}

void Audio::Play() {
    PlayMusicStream(music);
}

void Audio::Stop() {
    StopMusicStream(music);
}

void Audio::Update() {
    UpdateMusicStream(music);
}

void Audio::SetLooping(bool loop) {
    music.looping = loop;
}