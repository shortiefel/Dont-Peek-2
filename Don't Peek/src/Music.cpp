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