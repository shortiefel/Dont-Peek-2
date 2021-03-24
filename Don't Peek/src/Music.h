#pragma once


#include "fmod.h"
#include "fmod.hpp"
#include "fmod_codec.h"
#include "fmod_common.h"
#include "fmod_dsp.h"
#include "fmod_dsp_effects.h"
#include "fmod_errors.h"
#include "fmod_output.h"
#include <iostream>

void SoundSystem_Init(void);
void SoundSystem_SFX(void);
void Tutorial_SFX(void);
void SoundSystem_Destroy(void);
void SoundEraser_SFX(void);
void SoundHighlighter_SFX(void);

