function PS_SelfAction(toplayer, toptag, index)
	-- Check all self action done
	local nowstage, nowmission, nowturn = game.GetNowStageMissionTurn();
	local layertag = toptag+CCTag_Layer_11;
	local grouptag = layertag+CCTag_Menu_01;
	if index == 0 then
		grouptag = layertag+CCTag_Menu_04;
		local groupnode = game.GetNode({toplayer, grouptag});
		game.RemoveAllChildren(groupnode);
		grouptag = layertag+CCTag_Menu_05;
		local groupnode = game.GetNode({toplayer, grouptag});
		game.RemoveAllChildren(groupnode);
		grouptag = layertag+CCTag_Menu_06;
		local groupnode = game.GetNode({toplayer, grouptag});
		game.RemoveAllChildren(groupnode);
	end
	if true then
		grouptag = layertag+CCTag_Menu_01;
		for i=1, LConst_PlanGroupMax do
			local rendertextureitem = game.GetNode({toplayer, grouptag+i});
			game.RenderTextureBegin(rendertextureitem, true);
			game.RenderTextureEnd(rendertextureitem);
		end
		LGlobal_PlayData.planlines = {};
		LGlobal_PlayData.plandots = {};
		LGlobal_PlayData.plancircles = {};
		return true;
	end
	
	return false;
end