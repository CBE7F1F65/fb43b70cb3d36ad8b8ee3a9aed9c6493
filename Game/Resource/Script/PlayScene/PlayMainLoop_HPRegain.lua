function PS_HPRegain(toplayer, toptag)
	-- Add AP
	
	local hp, ap, sp = game.GetHPAPSP();
	hp = hp + HPMax*LConst_HPRegainRate;
	game.SetHPAPSP(hp, ap, sp);
	return true;
end