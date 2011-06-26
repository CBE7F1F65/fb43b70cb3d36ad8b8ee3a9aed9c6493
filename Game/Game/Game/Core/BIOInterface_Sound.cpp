#include "../Header/BIOInterface.h"

#include "../Header/MainDependency.h"

#include "../Header/SimpleAudioEngineExpand.h"
#include "cocos2d.h"
using namespace cocos2d;
using namespace CocosDenshion;


const char * BIOInterface::_FindSoundFileKeyByID(DWORD soundID)
{
	if (_listSoundFileKey.size() < soundID)
	{
		return NULL;
	}

	int i=0;
	for (list<_SoundFileKey>::iterator it=_listSoundFileKey.begin(); it!=_listSoundFileKey.end(); it++)
	{
		i++;
		if (i == soundID)
		{
			return it->filename;
		}
	}
	return NULL;
}

DWORD BIOInterface::_FindSoundFileKeyByName(const char * filename)
{
	int i=0;
	for (list<_SoundFileKey>::iterator it=_listSoundFileKey.begin(); it!=_listSoundFileKey.end(); it++)
	{
		i++;
		if (!strcmp(filename, it->filename))
		{
			return i;
		}
	}
	return NULL;
}

DWORD BIOInterface::_PushSoundFileKey(const char * filename)
{
	_SoundFileKey _sfk;
	ZeroMemory(&_sfk, sizeof(_SoundFileKey));
	strcpy(_sfk.filename, Resource_MakePath(filename));

	HEFFECT retval = (HEFFECT)_FindSoundFileKeyByName(_sfk.filename);
	if (retval)
	{
		return retval;
	}

	if (!Resource_AccessFile(_sfk.filename))
	{
		return NULL;
	}

	_listSoundFileKey.push_back(_sfk);
	retval = _listSoundFileKey.size();

	return retval;
}

bool BIOInterface::_RemoveSoundFileKey(DWORD soundID)
{
	if (_listSoundFileKey.size() < soundID)
	{
		return false;
	}

	int i=0;
	for (list<_SoundFileKey>::iterator it=_listSoundFileKey.begin(); it!=_listSoundFileKey.end(); it++)
	{
		i++;
		if (i == soundID)
		{
			_listSoundFileKey.erase(it);
			return true;
		}
	}

	return false;
}

HEFFECT BIOInterface::Effect_Load(const char *filename, DWORD size/* =0 */)
{
	HEFFECT eff = (HEFFECT)_PushSoundFileKey(filename);

	if (eff)
	{
		const char * fullfilename = _FindSoundFileKeyByID(eff);
		SimpleAudioEngineExpand::sharedEngine()->preloadEffect(fullfilename);
	}
	return eff;
}

void BIOInterface::Effect_Free(HEFFECT eff)
{
	const char * filename = _FindSoundFileKeyByID(eff);
	if (filename)
	{
		SimpleAudioEngineExpand::sharedEngine()->unloadEffect(filename);
		_RemoveSoundFileKey(eff);
	}
}

HCHANNEL BIOInterface::Effect_Play(HEFFECT eff)
{
	const char * filename = _FindSoundFileKeyByID(eff);
	if (filename)
	{
		unsigned int sid = SimpleAudioEngineExpand::sharedEngine()->playEffect(filename);
		return (HCHANNEL)sid;
	}
	return NULL;
}

HCHANNEL BIOInterface::Effect_PlayEx(HEFFECT eff, int volume/* =100 */, int pan/* =0 */, float pitch/* =1.0f */, bool loop/* =false */)
{
	const char * filename = _FindSoundFileKeyByID(eff);
	if (filename)
	{
		unsigned int sid = SimpleAudioEngineExpand::sharedEngine()->playEffect(filename);
		return (HCHANNEL)sid;
	}
	return NULL;
}

HSTREAM BIOInterface::Stream_Load(const char *filename, DWORD size/* =0 */, bool bLoad/* =true */)
{
	HSTREAM stream = (HSTREAM)_PushSoundFileKey(filename);

	if (stream)
	{
		const char * fullfilename = _FindSoundFileKeyByID(stream);
		SimpleAudioEngineExpand::sharedEngine()->preloadBackgroundMusic(fullfilename);
	}
	return stream;
}

void BIOInterface::Stream_Free(HSTREAM stream)
{
	const char * filename = _FindSoundFileKeyByID(stream);
	if (filename)
	{
		_RemoveSoundFileKey(stream);
	}
}

HCHANNEL BIOInterface::Stream_Play(HSTREAM stream, bool loop, int volume /* = 100 */)
{
	const char * filename = _FindSoundFileKeyByID(stream);
	if (filename)
	{
		SimpleAudioEngineExpand::sharedEngine()->playBackgroundMusic(filename, loop);
		return _SOUNDID_BGM;
	}
	return NULL;
}

void BIOInterface::Channel_SetPanning(HCHANNEL chn, int pan)
{

}

void BIOInterface::Channel_SetVolume(HCHANNEL chn, int volume)
{
	float fvol = volume/100.0f;
	if (chn == _SOUNDID_BGM)
	{
		SimpleAudioEngineExpand::sharedEngine()->setBackgroundMusicVolume(fvol);
	}
	else
	{
		SimpleAudioEngineExpand::sharedEngine()->setEffectsVolume(fvol);
	}
}

void BIOInterface::Channel_SetPitch(HCHANNEL chn, float pitch)
{

}

void BIOInterface::Channel_Pause(HCHANNEL chn)
{
	if (!chn)
	{
		Channel_PauseAll();
		return;
	}
	if (chn == _SOUNDID_BGM)
	{
		SimpleAudioEngineExpand::sharedEngine()->pauseBackgroundMusic();
	}
	else
	{
		SimpleAudioEngineExpand::sharedEngine()->stopEffect(chn);
	}
}

void BIOInterface::Channel_Resume(HCHANNEL chn)
{
	if (!chn)
	{
		Channel_ResumeAll();
		return;
	}
	if (chn == _SOUNDID_BGM)
	{
		SimpleAudioEngineExpand::sharedEngine()->resumeBackgroundMusic();
	}
}

void BIOInterface::Channel_Stop(HCHANNEL chn)
{
	if (!chn)
	{
		Channel_StopAll();
		return;
	}
	if (chn == _SOUNDID_BGM)
	{
		SimpleAudioEngineExpand::sharedEngine()->stopBackgroundMusic(false);
	}
}

void BIOInterface::Channel_PauseAll()
{
	SimpleAudioEngineExpand::sharedEngine()->pauseBackgroundMusic();
}

void BIOInterface::Channel_ResumeAll()
{
	SimpleAudioEngineExpand::sharedEngine()->resumeBackgroundMusic();
}

void BIOInterface::Channel_StopAll()
{
	SimpleAudioEngineExpand::sharedEngine()->stopBackgroundMusic(false);
}

bool BIOInterface::Channel_IsPlaying(HCHANNEL chn)
{
	if (chn == _SOUNDID_BGM)
	{
		return SimpleAudioEngineExpand::sharedEngine()->isBackgroundMusicPlaying();
	}
	return false;
}

QWORD BIOInterface::Channel_GetLength(HCHANNEL chn)
{
	return 0;
}

QWORD BIOInterface::Channel_GetPos(HCHANNEL chn)
{
	return 0;
}

void BIOInterface::Channel_SetPos(HCHANNEL chn, QWORD pos)
{
	if (chn == _SOUNDID_BGM)
	{
		if (!pos)
		{
			SimpleAudioEngineExpand::sharedEngine()->rewindBackgroundMusic();
		}
	}
	else
	{
		if (!pos)
		{
			SimpleAudioEngineExpand::sharedEngine()->rewindEffect(chn);
		}
	}
}

void BIOInterface::Channel_SetStartPos(HCHANNEL chn, bioChannelSyncInfo * pcsi)
{

}

void BIOInterface::Channel_SlideTo(HCHANNEL channel, float time, int volume, int pan /* = -101 */, float pitch /* = -1 */)
{
	Channel_SetVolume(channel, volume);
}

bool BIOInterface::Channel_IsSliding(HCHANNEL channel)
{
	return false;
}

void BIOInterface::Channel_SetLoop(HCHANNEL channel, bioChannelSyncInfo * pcsi)
{

}

void BIOInterface::Channel_RemoveLoop(HCHANNEL channel, bioChannelSyncInfo * pcsi)
{

}