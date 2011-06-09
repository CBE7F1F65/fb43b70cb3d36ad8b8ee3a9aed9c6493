LGlobal_PlayData = 
{	
	btrasitioning = true;
	
	nowhp = 0;
	nowap = 0;
	nowsp = 0;
	
	pushedMenuData = {};
	
	itemCount = 0;
	
	planlines = {};
	plandots = {};
	plancircles = {};
	
	planbrush = {};
	
	plangroup = 0;
	
	bZoomed = false;
}


function LGlobal_PlayScene_InitGlobal(toplayer, toptag)
	LGlobal_PlayData.nowhp = 0;
	LGlobal_PlayData.nowap = 0;
	LGlobal_PlayData.nowsp = 0;
	LGlobal_PlayData.pushedMenuData = {};
	LGlobal_PlayData.itemCount = game.GetItemData();
	LGlobal_PlayData.btrasitioning = true;
	LGlobal_PlayData.planlines = {};
	LGlobal_PlayData.plandots = {};
	LGlobal_PlayData.plancircles = {};
	LGlobal_PlayData.planbrush.laser = game.CreateSprite(SI_Game_PlanBrush_Laser);
	LGlobal_PlayData.planbrush.bomb = game.CreateSprite(SI_Game_PlanBrush_Bomb);
	LGlobal_PlayData.planbrush.sniper = game.CreateSprite(SI_Game_PlanBrush_Sniper);
	LGlobal_PlayData.plangroup = 0;
	LGlobal_PlayData.bZoomed = false;
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