#include "Music.h"

const int MAX_CHANNELS = 64;
FMOD::System* audio;
FMOD::ChannelGroup* bgmGroup;
FMOD::ChannelGroup* CEraser;
FMOD::ChannelGroup* CHighligther;
FMOD::Sound* BGSound;
FMOD::Sound* Eraser;
FMOD::Sound* Highlighter;

void SoundSystem_Init()
{
    FMOD_RESULT result = FMOD::System_Create(&audio);
    if (result != FMOD_OK)
    {
        std::cout << "FMOD Error: " << FMOD_ErrorString(result) << std::endl;
    }

    audio->init(MAX_CHANNELS, FMOD_INIT_NORMAL, NULL);

    audio->createChannelGroup("BGM", &bgmGroup);
    audio->createChannelGroup("BGM", &CEraser);
    audio->createChannelGroup("BGM", &CHighligther);

    audio->createSound("Resources/music/BGMusic.m4a", FMOD_DEFAULT, 0, &BGSound);
    audio->createSound("Resources/music/EraserSound.m4a", FMOD_DEFAULT, 0, &Eraser);
    audio->createSound("Resources/music/HighlighterSound.m4a", FMOD_DEFAULT, 0, &Highlighter);

    audio->update();

}

void SoundSystem_SFX()
{
    audio->playSound(BGSound, bgmGroup, false, 0);
    audio->playSound(BGSound, CEraser, false, 0);
    audio->playSound(BGSound, CHighligther, false, 0);
}

void SoundSystem_Destroy()
{
    std::cout << "i was triggered" << "\n";
    BGSound->release();
    Eraser->release();
    Highlighter->release();
}