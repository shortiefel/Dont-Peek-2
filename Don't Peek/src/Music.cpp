/* Start Header ************************************************************************/
/*!
\file Music.h
\team name Don't Peak
\software name I don't want to do homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief This file is done by felicia. In this file, it contains the functions for music. It
uses FMOD API to load and play the music.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

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
    //std::cout << "i was triggered" << "\n";
    static bool playing = false;
    bgmGroup->isPlaying(&playing);
        
    if(playing) 
        bgmGroup->stop();

    FMOD_RESULT result = BGSound->release();
    if (result != FMOD_OK)
        std::cout << "Release failed\n";
    printf("music DESTROY\n");
}


