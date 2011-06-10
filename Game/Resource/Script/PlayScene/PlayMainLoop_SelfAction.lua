function PS_SelfAction(toplayer, toptag, index)
	-- Check all self action done
	local nowstage, nowmission, nowturn = game.GetNowStageMissionTurn();
	local layertag = toptag+CCPSTL_Plan;
	local grouptag = layertag+CCPSTM_Plan_RenderTexture;
	if index == 0 then
		grouptag = layertag+CCPSTM_Plan_LinesFeather;
		local groupnode = game.GetNode({toplayer, grouptag});
		game.RemoveAllChildren(groupnode);
		grouptag = layertag+CCPSTM_Plan_CirclesFeather;
		local groupnode = game.GetNode({toplayer, grouptag});
		game.RemoveAllChildren(groupnode);
		grouptag = layertag+CCPSTM_Plan_DotsFeather;
		local groupnode = game.GetNode({toplayer, grouptag});
		game.RemoveAllChildren(groupnode);
	end
	if true then
		grouptag = layertag+CCPSTM_Plan_RenderTexture;
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