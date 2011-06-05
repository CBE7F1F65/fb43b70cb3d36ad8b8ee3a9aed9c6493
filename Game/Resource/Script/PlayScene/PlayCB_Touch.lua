function _PlayScene_CB_Touch_Began(toplayer, toptag, touchlayer, index, gesture)
end

function _PlayScene_CB_Touch_Moved(toplayer, toptag, touchlayer, index, gesture)
	
	if gesture == GESTURE_OneMoved or gesture == GESTURE_TwoMoved then
		
		local xb, yb = game.GetTouchInfo(touchlayer, index, CCTI_Began);
		local xe, ye, timee, touchtype = game.GetTouchInfo(touchlayer, index, CCTI_Moved);
		
		if gesture == GESTURE_TwoMoved then
			local oxb, oyb = game.GetTouchInfo(touchlayer, 1-index, CCTI_Began);
			_PlayScene_CB_Touch_DoToggleZoom(toplayer, toptag, (xb+oxb)/2, (yb+oyb)/2);
			game.TerminateTouch();
			
		else
			if LGlobal_PlayData.bZoomed then
				local xl, yl = game.GetTouchInfo(touchlayer, index, CCTI_LastMoved);
				_PlayScene_CB_Touch_MoveInZoom(toplayer, toptag, xe-xl, ye-yl);
			end
			
		end
		
	end
	
end

function _PlayScene_CB_Touch_MoveInZoom(toplayer, toptag, x, y, bAction)
	if LGlobal_PlayData.bZoomed == false then
		return;
	end
	local nowx, nowy = game.GetPosition(toplayer);
	nowx = nowx + x;
	nowy = nowy + y;
	if nowx > 832 then
		nowx = 832;
	elseif nowx < -832 then
		nowx = -832;
	end
	if nowy > 448 then
		nowy = 448;
	elseif nowy < -512 then
		nowy = -512;
	end
	if bAction~= nil and bAction then
		local moveaction = game.ActionMove(CCAF_To, nowx, nowy, LConst_ZoomActionTime);
		game.RunAction(toplayer, moveaction);
	else
		game.SetPosition(toplayer, nowx, nowy);
	end
end


function _PlayScene_CB_Touch_DoToggleZoom(toplayer, toptag, x, y)

	local overlaylayer = game.GetOverlayLayer(toplayer);
	local layertag = ktag_OverlayLayer+CCTag_Layer_01;
	local grouptag = layertag+CCTag_Menu_01;
	
	if LGlobal_PlayData.bZoomed == false then
		
		LGlobal_PlayData.bZoomed = true;
		_PlayScene_ToggleMenuEnable(toplayer, toptag, false);
		_PlayScene_ChangeTouchLayerRect(toplayer, toptag);
		local scaleaction = game.ActionScale(CCAF_By, 2, 2, LConst_ZoomActionTime);
		game.RunAction(toplayer, scaleaction);
		_PlayScene_CB_Touch_MoveInZoom(toplayer, toptag, 2*(480-x), 2*(320-y), true);
		
		local spScope = game.CreateSprite(SI_Game_Sniper_Scope, {480, 320, 0, LConst_SniperScopeScale, LConst_SniperScopeScale}, grouptag+1);
		local spFrontSight = game.CreateSprite(SI_Game_Sniper_FrontSight, {480, 320}, grouptag+2);
		
		local spTop = game.CreateSprite(SI_White, {480, -96, 0, 960, 192}, grouptag+3);
		local spBottom = game.CreateSprite(SI_White, {480, 736, 0, 960, 192}, grouptag+4);
		local spLeft = game.CreateSprite(SI_White, {-176, 320, 0, 352, 640}, grouptag+5);
		local spRight = game.CreateSprite(SI_White, {1136, 320, 0, 352, 640}, grouptag+6);
		local topnode = game.AddSpriteChild(spTop, {overlaylayer, grouptag});
		local bottomnode = game.AddSpriteChild(spBottom, {overlaylayer, grouptag});
		local leftnode = game.AddSpriteChild(spLeft, {overlaylayer, grouptag});
		local rightnode = game.AddSpriteChild(spRight, {overlaylayer, grouptag});
		local blackcol = global.ARGB(0xff, 0);
		game.SetColor(topnode, blackcol);
		game.SetColor(bottomnode, blackcol);
		game.SetColor(leftnode, blackcol);
		game.SetColor(rightnode, blackcol);
		local topaction = game.ActionMove(CCAF_By, 0, 192, LConst_ZoomActionTime);
		local bottomaction = game.ActionMove(CCAF_By, 0, -192, LConst_ZoomActionTime);
		local leftaction = game.ActionMove(CCAF_By, 352, 0, LConst_ZoomActionTime);
		local rightaction = game.ActionMove(CCAF_By, -352, 0, LConst_ZoomActionTime);
		game.RunAction(topnode, topaction);
		game.RunAction(bottomnode, bottomaction);
		game.RunAction(leftnode, leftaction);
		game.RunAction(rightnode, rightaction);
		
		game.SetColor(spFrontSight, global.ARGB(0x0, 0xffffff));

		local scopenode = game.AddSpriteChild(spScope, {overlaylayer, grouptag});
		local frontsightnode = game.AddSpriteChild(spFrontSight, {overlaylayer, grouptag});
		
		local scopescaleaction = game.ActionScale(CCAF_By, 1/LConst_SniperScopeScale, 1/LConst_SniperScopeScale, LConst_ZoomActionTime);
		local frontsightalphaaction = game.ActionFade(CCAF_To, 0xff, LConst_ZoomActionTime);
		game.RunAction(scopenode, scopescaleaction);
		game.RunAction(frontsightnode, frontsightalphaaction);
		
	else
		
		_PlayScene_ToggleMenuEnable(toplayer, toptag, true);
		local scaleaction = game.ActionScale(CCAF_By, 0.5, 0.5, LConst_ZoomActionTime);
		game.RunAction(toplayer, scaleaction);
		local nowx, nowy = game.GetPosition(toplayer);
		_PlayScene_CB_Touch_MoveInZoom(toplayer, toptag, -nowx, -nowy, true);
		LGlobal_PlayData.bZoomed = false;
		_PlayScene_ChangeTouchLayerRect(toplayer, toptag);
		
		local menunode = game.GetNode({overlaylayer, grouptag});
		
		local scopenode = game.GetNode({overlaylayer, grouptag+1});
		local frontsightnode = game.GetNode({overlaylayer, grouptag+2});
		
		local topnode = game.GetNode({overlaylayer, grouptag+3});
		local bottomnode = game.GetNode({overlaylayer, grouptag+4});
		local leftnode = game.GetNode({overlaylayer, grouptag+5});
		local rightnode = game.GetNode({overlaylayer, grouptag+6});
		local topaction = game.ActionMove(CCAF_By, 0, -352, LConst_ZoomActionTime);
		local bottomaction = game.ActionMove(CCAF_By, 0, 352, LConst_ZoomActionTime);
		local leftaction = game.ActionMove(CCAF_By, -176, 0, LConst_ZoomActionTime);
		local rightaction = game.ActionMove(CCAF_By, 176, 0, LConst_ZoomActionTime);
		game.RunAction(topnode, topaction);
		game.RunAction(bottomnode, bottomaction);
		game.RunAction(leftnode, leftaction);
		game.RunAction(rightnode, rightaction);
		
		local scopescaleaction = game.ActionScale(CCAF_By, LConst_SniperScopeScale, LConst_SniperScopeScale, LConst_ZoomActionTime);
		local frontsightalphaaction = game.ActionFade(CCAF_To, 0x0, LConst_ZoomActionTime);
		
		game.RunAction(scopenode, scopescaleaction);
		game.RunAction(frontsightnode, frontsightalphaaction);
		
		local deletechildrenaction = game.ActionDeleteChildren(LConst_ZoomActionTime);
		game.RunAction(menunode, deletechildrenaction);
		
	end
	
end

function _PlayScene_CB_Touch_Ended(toplayer, toptag, touchlayer, index, gesture)

	if gesture == GESTURE_TwoNoMove then
		return
	end
	
	local xb, yb = game.GetTouchInfo(touchlayer, index, CCTI_Began);
	local xe, ye, timee, touchtype = game.GetTouchInfo(touchlayer, index, CCTI_Moved);
	
	--WIN
	if gesture == GESTURE_OneNoMove and touchtype == TOUCH_Hold then
		_PlayScene_CB_Touch_DoToggleZoom(toplayer, toptag, xb, yb);
		return;
	end
	--
	
	if LGlobal_PlayData.bZoomed then
		if gesture == GESTURE_OneNoMove and touchtype == TOUCH_Tap then
			-- Plan Dots
			-- TODO: detect ap
			local atk, ap, r = game.GetWeaponData(WEAPON_Sniper);
			local nDots = table.getn(LGlobal_PlayData.plandots);
			nDots = nDots+1;
			LGlobal_PlayData.plandots[nDots] = {};
			LGlobal_PlayData.plandots[nDots].x = xb;
			LGlobal_PlayData.plandots[nDots].y = yb;	
			LGlobal_PlayData.plandots[nDots].startangle = RANDT();
			LGlobal_PlayData.plandots[nDots].time = 0;
			LGlobal_PlayData.plandots[nDots].atk = atk;
			LGlobal_PlayData.plandots[nDots].ap = ap;
			LGlobal_PlayData.plandots[nDots].r = r;
		end
		return false;
	end
	
	if gesture == GESTURE_OneMoved then
		-- Plan lines
		local dist = math.ceil(global.DIST(xb, yb, xe, ye));
		-- TODO: detect ap
		local atk, ap, leastap = game.GetWeaponData(WEAPON_Laser);
		if dist > 0 then
			local nLines = table.getn(LGlobal_PlayData.planlines);
			nLines = nLines+1;
			LGlobal_PlayData.planlines[nLines] = {};
			LGlobal_PlayData.planlines[nLines].xb = xb;
			LGlobal_PlayData.planlines[nLines].yb = yb;
			LGlobal_PlayData.planlines[nLines].xe = xe;
			LGlobal_PlayData.planlines[nLines].ye = ye;
			LGlobal_PlayData.planlines[nLines].atk = atk;
			LGlobal_PlayData.planlines[nLines].ap = ap;	--TODO: ap
			LGlobal_PlayData.planlines[nLines].time = 0;
			LGlobal_PlayData.planlines[nLines].dist = dist;
			local steps = math.ceil(dist/LConst_PlanBrushSpace);
			local space = dist/steps;
			LGlobal_PlayData.planlines[nLines].space = space;
			LGlobal_PlayData.planlines[nLines].stepstogo = {};
			steps = steps + 1;
			LGlobal_PlayData.planlines[nLines].steps = steps;
				
			local nowsteps = steps;
			for i=1, LConst_PlanBrushFrame do
				LGlobal_PlayData.planlines[nLines].stepstogo[i] = {};
				local nowstepstogo = math.floor(nowsteps/(LConst_PlanBrushFrame-i+1));
				if i ~= LConst_PlanBrushFrame then
					nowsteps = nowsteps-nowstepstogo;
					LGlobal_PlayData.planlines[nLines].stepstogo[i].now = nowstepstogo;
				else
					LGlobal_PlayData.planlines[nLines].stepstogo[LConst_PlanBrushFrame].now = nowsteps;
				end
				if i == 1 then
					LGlobal_PlayData.planlines[nLines].stepstogo[i].acc = 0;
				else
					LGlobal_PlayData.planlines[nLines].stepstogo[i].acc = LGlobal_PlayData.planlines[nLines].stepstogo[i-1].now+LGlobal_PlayData.planlines[nLines].stepstogo[i-1].acc;
				end
			
			end
		end
	elseif gesture == GESTURE_OneNoMove then
		-- Plan Circles
		local atk, ap, r = game.GetWeaponData(WEAPON_Bomb);
		-- TODO: detect ap
		local nCircles = table.getn(LGlobal_PlayData.plancircles);
		nCircles = nCircles + 1;
		LGlobal_PlayData.plancircles[nCircles] = {};
		LGlobal_PlayData.plancircles[nCircles].x = xb;
		LGlobal_PlayData.plancircles[nCircles].y = yb;
		LGlobal_PlayData.plancircles[nCircles].startangle = RANDT();
		LGlobal_PlayData.plancircles[nCircles].time = 0;
		LGlobal_PlayData.plancircles[nCircles].atk = atk;
		LGlobal_PlayData.plancircles[nCircles].ap = ap;
		LGlobal_PlayData.plancircles[nCircles].r = r;
		local totalsteps = math.ceil(2*M_PI*r/LConst_PlanBrushSpace);
		LGlobal_PlayData.plancircles[nCircles].anglestep = math.ceil(36000/totalsteps);
		LGlobal_PlayData.plancircles[nCircles].stepstogo = math.ceil(totalsteps/LConst_PlanBrushFrame)+1;
	end

end

function _PlayScene_CB_Touch_Canceled(toplayer, toptag, touchlayer, index, gesture)
end