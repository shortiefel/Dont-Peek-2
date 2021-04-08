/* Start Header ************************************************************************/
/*!
\file Music.h
\team name Don't Peek
\software name I Don't Wanna Do My Homework
\authors
Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
Margaret Teo Boon See	Teo.b@digipen.edu
Loh Yun Yi Tessa	tessa.loh@digipen.edu
Tan Jiajia, Amelia	t.jiajiaamelia@digipen.edu

\date 22/01/2021
\brief 
This file is done by felicia. 
In this file,  it contains the declaration of 
functions found in music.cpp


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

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

