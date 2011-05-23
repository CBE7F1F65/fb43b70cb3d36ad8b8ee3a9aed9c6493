function TouchLayer_CB(itemtag, toplayer, eventtag, toptag, sublayertag, touchlayer, index)
	if toptag == ktag_TitleSceneLayer then
		if sublayertag == CCTag_Layer_06 then
			local layertag = toptag + sublayertag;
			if eventtag == CCTI_Began then
				_TitleScene_CB_OptionTouch_Began(toplayer, toptag, touchlayer, index);
			elseif eventtag == CCTI_Moved then
				_TitleScene_CB_OptionTouch_Moved(toplayer, toptag, touchlayer, index);
			elseif eventtag == CCTI_Ended then
				_TitleScene_CB_OptionTouch_Ended(toplayer, toptag, touchlayer, index);
			else
				_TitleScene_CB_OptionTouch_Canceled(toplayer, toptag, touchlayer, index);
			end
		end
	end
end