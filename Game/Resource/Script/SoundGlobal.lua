LGlobal_BGMmusid = 0;
LGlobal_BGMStream = NULL;
LGlobal_BGMChannel = NULL;

LGlobal_SEInfos = {};

function LGlobal_LoadBGM(musid, bForce)
	
	if bForce == nil then
		bForce = false;
	end
	
	if LGlobal_BGMmusid == musid and not bForce then
		return;
	end
		
	if LGlobal_BGMChannel ~= NULL then
	
		if LGlobal_BGMStream ~= NULL then
			game.FreeMusic(LGlobal_BGMStream);
			LGlobal_BGMStream = NULL;
		end
		LGlobal_StopBGM();
		LGlobal_BGMStream = NULL;
		
	end
	
	local stream = game.LoadMusic(musid);
	LGlobal_BGMStream = stream;
	
	LGlobal_BGMmusid = musid;
	
	return stream;
end

function LGlobal_PlayBGM(bLoop, bForce)
	
	if bForce == nil then
		bForce = false;
	end
	
	if LGlobal_BGMChannel ~= NULL and bForce then
		LGlobal_StopBGM();
	end
	
	local channel = LGlobal_BGMChannel;
	if channel == NULL then
		channel = game.PlayMusic(LGlobal_BGMStream, bLoop);
		LGlobal_BGMChannel = channel;
	end
	
	LGlobal_SetBGMVol();
	
	return channel;
	
end

function LGlobal_StopBGM()
	game.StopChannel(LGlobal_BGMChannel);
	LGlobal_BGMChannel = NULL;
end

function LGlobal_PauseBGM()
	game.PauseChannel(LGlobal_BGMChannel);
end

function LGlobal_ResumeBGM()
	game.ResumeChannel(LGlobal_BGMChannel);
end

function LGlobal_LoadSE(seid)
	local nSE = table.getn(LGlobal_SEInfos);
	for i=1, nSE do
		if LGlobal_SEInfos[i].seid == seid then
			return LGlobal_SEInfos[i].effect;
		end
	end
	
	local effect = game.LoadSE(seid);
	if effect ~= NULL then
		LGlobal_SEInfos[nSE+1].seid = seid;
		LGlobal_SEInfos[nSE+1].effect = effect;
		LGlobal_SEInfos[nSE+1].channel = NULL;
	end
	
	return effect;
	
end

function LGlobal_FreeSE(seid)
	
	local nSE = table.getn(LGlobal_SEInfos);
	
	if seid == nil then
		for i=1, nSE do
			LGlobal_FreeSE(i);
		end
		return;
	end
	
	for i=1, nSE do
		if LGlobal_SEInfos[i].seid == seid then
			game.StopChannel(LGlobal_SEInfos[i].channel);
			game.FreeSE(LGlobal_SEInfos[i].effect);
			
			for j=i, nSE-1 do
				LGlobal_SEInfos[j].seid = LGlobal_SEInfos[j+1].seid;
				LGlobal_SEInfos[j].effect = LGlobal_SEInfos[j+1].effect;
				LGlobal_SEInfos[j].channel = LGlobal_SEInfos[j+1].channel;
			end
			LGlobal_SEInfos[nSE] = nil;
			
		end
	end
	
end

function LGlobal_PlaySE(seid)
	
	local nSE = table.getn(LGlobal_SEInfos);
	
	for i=1, nSE do
		if LGlobal_SEInfos[i].seid == seid then
			game.StopChannel(LGlobal_SEInfos[i].channel);
			local channel = game.PlaySE(LGlobal_SEInfos[i].effect);
			LGlobal_SEInfos[i].channel = channel;
			LGlobal_SetSEVol();
			return channel;
		end
	end
	
	return NULL;
	
end

function LGlobal_SetBGMVol()
	
	if LGlobal_BGMChannel ~= NULL then
		local bgmvol = game.GetBGMSEVol();
		game.SetChannelInfo(LGlobal_BGMChannel, bgmvol);
	end
	
end

function LGlobal_SetSEVol()
	
	local nSE = table.getn(LGlobal_SEInfos);
	local bgmvol, sevol = game.GetBGMSEVol();
	
	for i=1, nSE do
		if LGlobal_SEInfos[i].channel ~= NULL then
			game.SetChannelInfo(LGlobal_SEInfos[i].channel, sevol);
		end
	end
			
end