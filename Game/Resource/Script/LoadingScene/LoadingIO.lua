function LoadingScene_IO(eventtype, toplayer, toptag)
	
	if eventtype == SceneIOFlag_OnInit then
		return LoadingScene_OnInit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnter then
		return LoadingScene_OnEnter(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnterTDF then
		return LoadingScene_OnEnterTDF(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnExit then
		return LoadingScene_OnExit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchBegin then
		return LoadingScene_OnTouchBegin(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchEnd then
		return LoadingScene_OnTouchEnd(toplayer, toptag);
	end
end

function LoadingScene_OnInit(toplayer, toptag)
end

function LoadingScene_OnEnter(toplayer, toptag)
	--_PrintMissionEnemyTable();
	game.ReplaceScene(ktag_TitleSceneLayer, LConst_SceneTransTime)
	
end
function LoadingScene_OnEnterTDF(toplayer, toptag)
end
function LoadingScene_OnExit(toplayer, toptag)
end
function LoadingScene_OnTouchBegin(toplayer, toptag)
end
function LoadingScene_OnTouchEnd(toplayer, toptag)
end

function _PrintMissionEnemyTable()
	local str;
	for i=0, 7 do
		
		str = string.format("#		World_%02d", i);
		LOG(str);
		
		local missionmax = 48;
		local missionmin = 1;
		if i==7 then
			missionmin = 0;
			missionmax = 7;
		end
		
		for j=missionmin, missionmax do
			
			str = string.format("#		Mission_%02d", j);
			LOG(str);
			
			local initcount = RANDT(2, 5);
			for k=1, initcount do
				str = string.format("-	%d	%d	%d	%d	%d	%d	%d	0",	i, j, 0, RANDT(0,9), RANDT(100, 860), RANDT(150, 490), RANDT(1, 3));
				LOG(str);
			end
			
			local turncount = RANDT(1, 4);
			for k=1, turncount do
				local turnenemycount = RANDT(1, 3);
				for l=1, turnenemycount do
					local ltrindex = RANDT(0, 2);
					local x, y, angle;
					if ltrindex == 0 then
						x = RANDT(4, 60);
						y = RANDT(200, 340);
						angle = RANDT(4500, 13500);
					elseif ltrindex == 1 then
						x = RANDT(200, 760);
						y = RANDT(4, 60);
						angle = RANDT(13500, 22500);
					else
						x = RANDT(900, 956);
						y = RANDT(200, 340);
						angle = RANDT(-13500, -4500);
					end
					str = string.format("-	%d	%d	%d	%d	%d	%d	%d	0",	i, j, k, RANDT(0,9), x, y, angle);
					LOG(str)
				end
			end
			
		end
	end
end