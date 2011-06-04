function _PlayScene_CB_Touch_Began(toplayer, toptag, touchlayer, index, gesture)
end

function _PlayScene_CB_Touch_Moved(toplayer, toptag, touchlayer, index, gesture)
end

function _PlayScene_CB_Touch_Ended(toplayer, toptag, touchlayer, index, gesture)

	if gesture == GESTURE_OneMoved then
		local xb, yb, timeb = game.GetTouchInfo(touchlayer, index, CCTI_Began);
		local xe, ye, timee = game.GetTouchInfo(touchlayer, index, CCTI_Moved);
		local dist = math.ceil(global.DIST(xb, yb, xe, ye));
		if dist > 0 then
			local nLines = table.getn(LGlobal_PlayData.planlines);
			nLines = nLines+1;
			LGlobal_PlayData.planlines[nLines] = {};
			LGlobal_PlayData.planlines[nLines].xb = xb;
			LGlobal_PlayData.planlines[nLines].yb = yb;
			LGlobal_PlayData.planlines[nLines].xe = xe;
			LGlobal_PlayData.planlines[nLines].ye = ye;
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
	end

end

function _PlayScene_CB_Touch_Canceled(toplayer, toptag, touchlayer, index, gesture)
end