#pragma once

#include "fmod_studio.hpp"
#include "fmod.hpp"
#include "fmod_errors.h"
#include <string>
#include <map>
#include <math.h>
#include <iostream>

using namespace std;

struct fmodapi
{
	fmodapi(); //ctor
	~fmodapi(); //dtor

	void Update(); //function for update

	FMOD::Studio::System* mpStudioSystem; 
	FMOD::System* mpSystem;

	int mnNextChannelID;

	typedef map<string, FMOD::Sound*> SoundMap;
	typedef map<int, FMOD::Channel*> ChannelMap;
	typedef map<string, FMOD::Studio::EventInstance*> EventMap;
	typedef map<string, FMOD::Studio::Bank*> BankMap;

	BankMap mBanks;
	EventMap mEvents;
	SoundMap mSounds;
	ChannelMap mChannel;
};

class AudioEngine
{
public:
	static void Init();
	static void Update();
	static void Shutdown();
	static int ErrorCheck(FMOD_RESULT result); //memory checking

	//flags passed into studio loadbank commands to control bank load behaviour
	void LoadBank(const string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags); 
	void LoadEvent(const string& strEventName);
	void LoadSound(const string& strSoundName, bool b)
};



