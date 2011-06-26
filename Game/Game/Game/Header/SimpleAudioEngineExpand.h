#ifndef __SIMPLEAUDIOENGINEEXPAND_H__
#define __SIMPLEAUDIOENGINEEXPAND_H__

#include "SimpleAudioEngine.h"

namespace CocosDenshion {

	class SimpleAudioEngineExpand : public SimpleAudioEngine
	{
	public:
		SimpleAudioEngineExpand();
		~SimpleAudioEngineExpand();

		static SimpleAudioEngineExpand * sharedEngine();
		static void end();

		void rewindEffect(unsigned int nSoundId);
	};
}

#endif