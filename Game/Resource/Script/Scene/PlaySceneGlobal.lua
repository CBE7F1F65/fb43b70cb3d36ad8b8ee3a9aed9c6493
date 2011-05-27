LGlobal_PlayData = 
{
	PlayScene_EnterHelpFlag = 0;
	
	nowhp = 0;
	nowap = 0;
	nowsp = 0;
	
	pushedMenuData = {};
	
	itemCount = 0;
}


function LGlobal_PlayScene_InitGlobal(toplayer, toptag)
	LGlobal_PlayData.PlayScene_EnterHelpFlag = 0;
	LGlobal_PlayData.nowhp = 0;
	LGlobal_PlayData.nowap = 0;
	LGlobal_PlayData.nowsp = 0;
	LGlobal_PlayData.pushedMenuData = {};
	LGlobal_PlayData.itemCount = game.GetItemData();
end

function LGobal_PushPlaySceneMenuData(itemtag, posdata)
	
	local nowcount = table.getn(LGlobal_PlayData.pushedMenuData);
	LGlobal_PlayData.pushedMenuData[nowcount+1] = {};
	LGlobal_PlayData.pushedMenuData[nowcount+1].itemtag = itemtag;
	LGlobal_PlayData.pushedMenuData[nowcount+1].posdata = posdata;
	
end

function LGobal_PopPlaySceneMenuData(itemtag, posdata)
	
	local nowcount = table.getn(LGlobal_PlayData.pushedMenuData);
	
	if nowcount > 0 then
		local itemtag = LGlobal_PlayData.pushedMenuData[nowcount].itemtag;
		local posdata = LGlobal_PlayData.pushedMenuData[nowcount].posdata;
		LGlobal_PlayData.pushedMenuData[nowcount] = nil;
		return itemtag, posdata;
	end
	
end