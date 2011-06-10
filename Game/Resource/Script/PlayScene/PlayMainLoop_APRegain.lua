function PS_APRegain(toplayer, toptag)
	-- Add AP
	
	local hp, ap, sp = game.GetHPAPSP();
	ap = ap + APMax*LConst_APRegainRate;
	game.SetHPAPSP(hp, ap, sp);
	return true;
end