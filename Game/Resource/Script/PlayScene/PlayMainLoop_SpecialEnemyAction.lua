function PS_SpecialEnemyAction(toplayer, toptag, index)
	-- Check all enemy action done
	local nowstage, nowmission, nowturn = game.GetNowStageMissionTurn();
	-- No action on initial
	if nowturn == 0 then
		return true;
	end
	if PS_DoEnemyAction(toplayer, toptag, index, nowstage, nowmission, nowturn, true) then
		return true;
	end
	
	return false;
end