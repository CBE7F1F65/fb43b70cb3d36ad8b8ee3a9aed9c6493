function Scene_CB(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag, dataindex)
	for i, it in pairs(LGlobal_SceneFunctions) do
		if it[1] == toptag then
			return it[3](itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag, dataindex);
		end
	end
end