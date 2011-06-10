function InputLayer_CB(itemtag, toplayer, eventtag, toptag, sublayertag, text)
	if toptag == ktag_TitleSceneLayer then
		if sublayertag == CCTSTL_Input then
			local layertag = toptag + sublayertag;
			if eventtag == CCET_Enter then
				_TitleScene_PauseMenuLayer(toplayer, toptag);
				_TitleScene_StopInputHintAction(toplayer, layertag)
			elseif eventtag == CCET_Leave then
				_TitleScene_ResumeMenuLayer(toplayer, toptag);
				game.SetUsername(text);
				if text == "" then
					_TitleScene_RunInputHintAction(toplayer, layertag);
				end
			end
		end
	end
end