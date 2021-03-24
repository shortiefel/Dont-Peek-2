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
    audio->createChannelGroup("CE", &CEraser);
    audio->createChannelGroup("CH", &CHighligther);

    audio->createSound("Resources/BGMusic.wav", FMOD_LOOP_NORMAL, 0, &BGSound);


    audio->update();

}

void SoundSystem_SFX()
{
    audio->playSound(BGSound, bgmGroup, false, 0);

}

void Tutorial_SFX()
{
    audio->playSound(BGSound, bgmGroup, false, 0);

}



void SoundSystem_Destroy()
{
    std::cout << "i was triggered" << "\n";
    BGSound->release();

}


