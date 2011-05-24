
g_SceneFunctions = 
{
	{ktag_PlaySceneLayer, PlayScene_IO, PlayScene_CB},
	
	{ktag_LoadingSceneLayer, LoadingScene_IO, LoadingScene_CB},
	{ktag_TitleSceneLayer, TitleScene_IO, TitleScene_CB},
	
	{ktag_HelpSceneLayer, HelpScene_IO, HelpScene_CB},
	
	{ktag_StageSelectSceneLayer, StageSelectScene_IO, StageSelectScene_CB},
	{ktag_MissionSelectSceneLayer, MissionSelectScene_IO, MissionSelectScene_CB},
	
	{ktag_BaseSceneLayer, BaseScene_IO, BaseScene_CB},
}

function GlobalScene_CreateCancelMenu(nownode, zOrder, itemtag)
	
		local spNormal = game.CreateSprite(SI_White, {0, 0, 0, 960, 640});
		local spSelected = game.CreateSprite(SI_White, {0, 0, 0, 960, 640});

		local menu = game.CreateMenuItem(nownode, {480, 320, zOrder, itemtag}, spNormal, spSelected);
		game.SetColor(menu, global.ARGB(0, 0));
		
		return menu;
		
end