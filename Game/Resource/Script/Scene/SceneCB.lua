function Scene_CB(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	for i, it in pairs(g_SceneFunctions) do
		if it[1] == toptag then
			return it[3](itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		end
	end
end