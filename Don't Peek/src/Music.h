#pragma once

#include "fmod_studio.hpp"
#include "fmod.hpp"
#include "fmod_errors.h"
#include <string>
#include <map>
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

//creates a FMOD studio and Low-Level System
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
	void LoadSound(const string& SoundName, bool b3d = true, bool blooping = false, bool bStream = false);
	void UnLoadSound(const string& SoundName);
	
	int PlaySound(const string & SoundName, float fVolumedB = 0.0f);
	void PlayEvent(const string& EventName);

	void StopChannel(int ChannelID);
	void StopAllChannels();
	void SetChannelVolume(int ChannelID, float fVolumedB);
	bool IsPlaying(int ChannelID) const;
	bool IsEventPlaying(const string& EventName) const;
	float dbToVolume(float db);
	float VolumeToDB(float volume);
};