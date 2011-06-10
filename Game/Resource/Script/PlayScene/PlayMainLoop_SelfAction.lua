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
	
	if PS_DoSelfAction(toplayer, toptag, index, nowstage, nowmission, nowturn) then
		LGlobal_PlayData.planlines = {};
		LGlobal_PlayData.plandots = {};
		LGlobal_PlayData.plancircles = {};
		return true;
	end
	
	return false;
end

function PS_DoSelfAction(toplayer, toptag, index, nowstage, nowmission, nowturn)
	local plangroup = LGlobal_PlayData.plangroup;
	if index > plangroup then
		return true;
	end
	local layertag = toptag+CCPSTL_Plan;
	local grouptag = layertag+CCPSTM_Plan_RenderTexture;
	local rendertextureitem = game.GetNode({toplayer, grouptag+index+1});
	game.RenderTextureBegin(rendertextureitem, true);
	game.RenderTextureEnd(rendertextureitem);
	
	local dataindex = LGlobal_SaveData(STATE_SelfAction);
	local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_EnemyEnterDelayTime, dataindex);
	local callnodegrouptag = layertag + CCPSTM_Plan_CallNode;
	local callnode = game.AddNullChild({toplayer, grouptag+index+1}, {0, 0, 0, callnodegrouptag+index+1});
	game.RunAction(callnode, callfuncaction);
	return false;
end