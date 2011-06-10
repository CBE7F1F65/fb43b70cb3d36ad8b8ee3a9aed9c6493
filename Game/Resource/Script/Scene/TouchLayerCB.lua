function TouchLayer_CB(toplayer, eventtag, toptag, sublayertag, touchlayer, index, gesture)
	
	if toptag == ktag_PlaySceneLayer then
		if sublayertag == CCPSTL_Touch then
			local layertag = toptag + sublayertag;
			if eventtag == CCTI_Began then
				_PSCB_Touch_Began(toplayer, toptag, touchlayer, index, gesture);
			elseif eventtag == CCTI_Moved then
				_PSCB_Touch_Moved(toplayer, toptag, touchlayer, index, gesture);
			elseif eventtag == CCTI_Ended then
				_PSCB_Touch_Ended(toplayer, toptag, touchlayer, index, gesture);
			else
				_PSCB_Touch_Canceled(toplayer, toptag, touchlayer, index, gesture);
			end
		end
	
	elseif toptag == ktag_TitleSceneLayer then
		if sublayertag == CCTSTL_BGMTouch then
			local layertag = toptag + sublayertag;
			if eventtag == CCTI_Began then
				_TitleScene_CB_BGMTouch_Began(toplayer, toptag, touchlayer, index);
			elseif eventtag == CCTI_Moved then
				_TitleScene_CB_BGMTouch_Moved(toplayer, toptag, touchlayer, index);
			elseif eventtag == CCTI_Ended then
				_TitleScene_CB_BGMTouch_Ended(toplayer, toptag, touchlayer, index);
			else
				_TitleScene_CB_BGMTouch_Canceled(toplayer, toptag, touchlayer, index);
			end
		elseif sublayertag == CCTSTL_SETouch then
			local layertag = toptag + sublayertag;
			if eventtag == CCTI_Began then
				_TitleScene_CB_SETouch_Began(toplayer, toptag, touchlayer, index);
			elseif eventtag == CCTI_Moved then
				_TitleScene_CB_SETouch_Moved(toplayer, toptag, touchlayer, index);
			elseif eventtag == CCTI_Ended then
				_TitleScene_CB_SETouch_Ended(toplayer, toptag, touchlayer, index);
			else
				_TitleScene_CB_SETouch_Canceled(toplayer, toptag, touchlayer, index);
			end
		end
	end
end