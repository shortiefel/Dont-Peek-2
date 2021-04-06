#include "Music.h"

const int MAX_CHANNELS = 64;
FMOD::System* audio;
FMOD::ChannelGroup* bgmGroup;
FMOD::Sound* BGSound;


void SoundSystem_Init()
{
    FMOD_RESULT result = FMOD::System_Create(&audio);
    if (result != FMOD_OK)
    {
        std::cout << "FMOD Error: " << FMOD_ErrorString(result) << std::endl;
    }

    audio->init(MAX_CHANNELS, FMOD_INIT_NORMAL, NULL);

    audio->createChannelGroup("BGM", &bgmGroup);

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
    static bool playing = false;
    bgmGroup->isPlaying(&playing);
        
    if(playing) 
        bgmGroup->stop();

    FMOD_RESULT result = BGSound->release();
    if (result != FMOD_OK)
        std::cout << "Release failed\n";

}


