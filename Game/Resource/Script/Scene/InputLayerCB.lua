function InputLayer_CB(itemtag, toptag, sublayertag, text)
	if toptag == ktag_TitleSceneLayer then
		if sublayertag == CCTag_Layer_13 then
			game.SetUsername(text);
		end
	end
end