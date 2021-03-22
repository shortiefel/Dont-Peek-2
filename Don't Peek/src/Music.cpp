	//#include "Music.h"
	//
	//
	////ctor
	//fmodapi::fmodapi()
	//{
	//	mpStudioSystem = NULL;
	//
	//	//ErrorCheck is to check that all FMOD calls are successful
	//	AudioEngine::ErrorCheck(FMOD::Studio::System::create(&mpStudioSystem));
	//
	//	//FMOD_STUDIO_INIT_LIVEUPDATE: connect the game to FMOD Studio and live mix the audio
	//	AudioEngine::ErrorCheck(mpStudioSystem->initialize(32, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL));
	//
	//	mpSystem = NULL;
	//	//getCoreSystem give the low-level system
	//	AudioEngine::ErrorCheck(mpStudioSystem->getCoreSystem(&mpSystem));
	//}
	//
	////dtor
	//fmodapi::~fmodapi()
	//{
	//	AudioEngine::ErrorCheck(mpStudioSystem->unloadAll());
	//	AudioEngine::ErrorCheck(mpStudioSystem->release());
	//}
	//
	////checking if a channel has stop playing, if yes. Destroy to clear channel to use 
	//void fmodapi::Update()
	//{
	//	vector<ChannelMap::iterator> pStoppedChannels;
	//	for (auto start = mChannel.begin(), End = mChannel.end(); start != End; ++start)
	//	{
	//		bool bIsPlaying = false;
	//		start->second->isPlaying(&bIsPlaying);
	//		if (!bIsPlaying)
	//			pStoppedChannels.push_back(start);
	//	}
	//
	//	for (auto& start : pStoppedChannels)
	//		mChannel.erase(start);
	//
	//	AudioEngine::ErrorCheck(mpStudioSystem->update());
	//}
	//
	//fmodapi* sfmodapi = nullptr;
	//
	//void AudioEngine::Init()
	//{
	//	sfmodapi = new fmodapi;
	//}
	//
	//void AudioEngine::Update()
	//{
	//	sfmodapi->Update();
	//}
	//
	//void AudioEngine::LoadSound(const string& SoundName, bool b3d, bool blooping, bool bStream)
	//{
	//	auto Searching = sfmodapi->mSounds.find(SoundName);
	//	if (Searching != sfmodapi->mSounds.end())
	//		return;
	//
	//	//loading of sounds be it if its 3D or not.
	//	FMOD_MODE eMode = FMOD_DEFAULT;
	//	eMode |= b3d ? FMOD_3D : FMOD_2D;
	//	eMode |= blooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	//	eMode |= bStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;
	//
	//	FMOD::Sound* pSound = nullptr;
	//	AudioEngine::ErrorCheck(sfmodapi->mpSystem->createSound(SoundName.c_str(), eMode, nullptr, &pSound));
	//	if (pSound)
	//		sfmodapi->mSounds[SoundName] = pSound;
	//
	//}
	//
	//void AudioEngine::UnLoadSound(const string& SoundName)
	//{
	//
	//	//takes the fie name and look it up in the sound map to release the sound
	//	auto Searching = sfmodapi->mSounds.find(SoundName);
	//	if (Searching == sfmodapi->mSounds.end())
	//		return;
	//
	//	AudioEngine::ErrorCheck(Searching->second->release());
	//	sfmodapi->mSounds.erase(Searching);
	//}
	//
	//int AudioEngine::PlaySound(const string& SoundName, float fVolumedB)
	//{
	//	int ChannelID = sfmodapi->mnNextChannelID++; //increasing the channel
	//	auto Searching = sfmodapi->mSounds.find(SoundName);
	//	if (Searching == sfmodapi->mSounds.end())
	//	{
	//		LoadSound(SoundName);
	//		Searching = sfmodapi->mSounds.find(SoundName);
	//		if (Searching == sfmodapi->mSounds.end())
	//			return ChannelID;
	//	}
	//
	//	FMOD::Channel* pChannel = nullptr;
	//	AudioEngine::ErrorCheck(sfmodapi->mpSystem->playSound(Searching->second, nullptr, true, &pChannel));
	//	if (pChannel)
	//	{
	//		FMOD_MODE currMode;
	//		Searching->second->getMode(&currMode);
	//		AudioEngine::ErrorCheck(pChannel->setVolume(dbToVolume(fVolumedB)));
	//		AudioEngine::ErrorCheck(pChannel->setPaused(false));
	//		sfmodapi->mChannel[ChannelID] = pChannel;
	//	}
	//
	//	return ChannelID;
	//}
	//
	////set the volume of the sound
	//void AudioEngine::SetChannelVolume(int ChannelID, float fVolumedB)
	//{
	//	auto Searching = sfmodapi->mChannel.find(ChannelID);
	//	if (Searching == sfmodapi->mChannel.end())
	//		return;
	//
	//	AudioEngine::ErrorCheck(Searching->second->setVolume(dbToVolume(fVolumedB)));
	//}
	//
	//bool AudioEngine::IsEventPlaying(const string& EventName) const
	//{
	//	auto Searching = sfmodapi->mEvents.find(EventName);
	//	if (Searching == sfmodapi->mEvents.end())
	//		return false;
	//
	//	FMOD_STUDIO_PLAYBACK_STATE* state = NULL;
	//	if (Searching->second->getPlaybackState(state) == FMOD_STUDIO_PLAYBACK_PLAYING)
	//		return true;
	//
	//	return false;
	//}
	//
	//float AudioEngine::dbToVolume(float dB)
	//{
	//	return powf(10.f, 0.05f * dB);
	//}
	//
	//float AudioEngine::VolumeToDB(float volume)
	//{
	//	return 20.f * log10f(volume);
	//}
	//
	//int AudioEngine::ErrorCheck(FMOD_RESULT result)
	//{
	//	if (result != FMOD_OK)
	//	{
	//		cout << "FMOD ERROR " << result << endl;
	//		return 1;
	//	}
	//	return 0;
	//}
	//
	//void AudioEngine::Shutdown()
	//{
	//	delete sfmodapi;
	//}

