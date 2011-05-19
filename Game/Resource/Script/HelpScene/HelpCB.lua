function HelpScene_CB(itemtag, eventtag, toptag, sublayertag, selgrouptag, selitemtag)
	if selgrouptag == CCTag_Debug_ReloadMenu then
		return Debug_AddReloadMenu_Callback(selitemtag, eventtag, toptag);
		
	elseif selgrouptag == CCTag_Menu_00 then
		return HelpScene_MainMenu(itemtag, eventtag, toptag, sublayertag, selgrouptag, selitemtag);
	elseif selgrouptag == CCTag_Menu_14 then
		return HelpScene_PopScene(itemtag, eventtag, toptag, sublayertag, selgrouptag, selitemtag);
	end
end

function HelpScene_MainMenu(itemtag, eventtag, toptag, sublayertag, selgrouptag, selitemtag)
	if selitemtag == 3 then
		
		local layertag = toptag+sublayertag;
		local grouptag = layertag+selgrouptag;
		local menus = {};
		local spTitleMenus = {};
		local spTitleMenusSelected = {};
		local xmove = 400;
		for i=0, 2 do
			local spritealphaaction = {};
	
			menus[i+1] = game.GetNode({layertag, grouptag, grouptag+i+1});
			spTitleMenus[i+1] = game.GetNode({layertag, grouptag, grouptag+i+1, grouptag+CCTag_MenuSub_00+i+1});
			spTitleMenusSelected[i+1] = game.GetNode({layertag, grouptag, grouptag+i+1, grouptag+CCTag_MenuSub_01+i+1});
		
			local fadetime = 0.3+(4-i)*0.05;
			if i+1 ~= selitemtag then
				local menumoveaction = game.ActionMove(xmove, 0, fadetime, true);
				menumoveaction = game.ActionEase(CCAF_Out, menumoveaction, 0.25);
				game.RunAction(menus[i+1], menumoveaction);
			
				for j=0, 1 do
					spritealphaaction[j+1] = game.ActionFade(CCAF_To, 0, fadetime);
				end
				game.RunAction(spTitleMenus[i+1], spritealphaaction[1]);
				game.RunAction(spTitleMenusSelected[i+1], spritealphaaction[2]);
			
			else
			
				local selectedalphaaction = {};
				local scaleval = 1.05;
				local selectedscaleactionpre = game.ActionScale(scaleval, scaleval, 0.1);
				local selectedscaleactionpost = game.ActionScale(1, 1, 0.1);
				local selectedscaleaction = game.ActionSequence({selectedscaleactionpre, selectedscaleactionpost});
			
				for j=0, 1 do
					selectedalphaaction[j+1] = game.ActionFade(CCAF_To, 0xff, 0.3);
				end
			
				game.RunAction(spTitleMenus[i+1], selectedalphaaction[1]);
				game.RunAction(spTitleMenusSelected[i+1], selectedalphaaction[2]);
			
				game.RunAction(menus[i+1], selectedscaleaction);
			
				local delayaction = game.ActionDelay(0.3);
				local callfuncaction = game.ActionCallFunc({layertag, grouptag, grouptag+i+1});
				local delayreplacesceneaction = game.ActionSequence({delayaction, callfuncaction});
				local callnode = game.AddNullChild({layertag}, {0, 0, 0, layertag+CCTag_Menu_14+i+1});
				game.RunAction(callnode, delayreplacesceneaction);
			
			end
		end
	end
	
end

function HelpScene_PopScene(itemtag, eventtag, toptag, sublayertag, selgrouptag, selitemtag)
	game.PopScene();
end