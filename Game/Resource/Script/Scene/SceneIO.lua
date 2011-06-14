function Scene_IO(eventtype, toplayer, toptag)
	if eventtype == SceneIOFlag_OnInit then
		if _DEBUG then
			Debug_AddReloadMenu(toplayer, toptag);
		end
	end
	for i, it in pairs(LGlobal_SceneFunctions) do
		if it[1] == toptag then
			return it[2](eventtype, toplayer, toptag);
		end
	end
end