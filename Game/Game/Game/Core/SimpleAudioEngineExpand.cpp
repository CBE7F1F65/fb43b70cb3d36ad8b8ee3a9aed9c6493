#include "../Header/SimpleAudioEngineExpand.h"

namespace CocosDenshion {

	SimpleAudioEngineExpand::SimpleAudioEngineExpand()
	{

	}

	SimpleAudioEngineExpand::~SimpleAudioEngineExpand()
	{

	}

	SimpleAudioEngineExpand * SimpleAudioEngineExpand::sharedEngine()
	{
		static SimpleAudioEngineExpand s_SharedEngine;
		return &s_SharedEngine;
	}

	void SimpleAudioEngineExpand::end()
	{
		SimpleAudioEngine::end();
	}

	void SimpleAudioEngineExpand::rewindEffect(unsigned int nSoundId)
	{

	}

}