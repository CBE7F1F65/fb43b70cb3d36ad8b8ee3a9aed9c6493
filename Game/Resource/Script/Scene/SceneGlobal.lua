
g_SceneFunctions = 
{
	{ktag_PlaySceneLayer, PlayScene_IO, PlayScene_CB},
	
	{ktag_LoadingSceneLayer, LoadingScene_IO, LoadingScene_CB},
	{ktag_TitleSceneLayer, TitleScene_IO, TitleScene_CB},
	
	{ktag_HelpSceneLayer, HelpScene_IO, HelpScene_CB},
	
	{ktag_StageSelectSceneLayer, StageSelectScene_IO, StageSelectScene_CB},
	{ktag_MissionSelectSceneLayer, MissionSelectScene_IO, MissionSelectScene_CB},
	{ktag_StorySceneLayer, StoryScene_IO, StoryScene_CB},
	
	{ktag_BaseSceneLayer, BaseScene_IO, BaseScene_CB},
}

function GlobalScene_CreateCancelMenu(nownode, zOrder, itemtag)
	
		local spNormal = game.CreateSprite(SI_White, {0, 0, 0, 960, 640});
		local spSelected = game.CreateSprite(SI_White, {0, 0, 0, 960, 640});

		local menu = game.CreateMenuItem(nownode, {480, 320, zOrder, itemtag}, spNormal, spSelected);
		game.SetColor(menu, global.ARGB(0, 0));
		
		return menu;
		
end

LGlobal_MissionSelect_NodePos = 
{
	-- World 1 (17)
	{
		{100, 500},
		{150, 600},
		{200, 400},
		{250, 600},
		{300, 400},
		{350, 600},
		{400, 400},
		{450, 600},
		{500, 400},
		{550, 500},
		{600, 400},
		{550, 350},
		{500, 300},
		{450, 250},
		{400, 200},
		{350, 150},
		{300, 100},
	},
	-- World 2 (17)
	{
		{50, 500},
		{100, 500},
		{150, 500},
		{200, 500},
		{250, 500},
		{300, 500},
		{350, 500},
		{400, 500},
		{450, 500},
		{500, 500},
		{100, 400},
		{150, 350},
		{200, 300},
		{250, 250},
		{300, 200},
		{350, 150},
		{400, 100},
	},
	-- World 3 (17)
	{
		{50, 500},
		{100, 500},
		{150, 500},
		{200, 500},
		{250, 500},
		{300, 500},
		{350, 500},
		{400, 500},
		{450, 500},
		{500, 500},
		{100, 400},
		{150, 350},
		{200, 300},
		{250, 250},
		{300, 200},
		{350, 150},
		{400, 100},
	},
	-- World 4 (17)
	{
		{50, 500},
		{100, 500},
		{150, 500},
		{200, 500},
		{250, 500},
		{300, 500},
		{350, 500},
		{400, 500},
		{450, 500},
		{500, 500},
		{100, 400},
		{150, 350},
		{200, 300},
		{250, 250},
		{300, 200},
		{350, 150},
		{400, 100},
	},
	-- World 5 (17)
	{
		{50, 500},
		{100, 500},
		{150, 500},
		{200, 500},
		{250, 500},
		{300, 500},
		{350, 500},
		{400, 500},
		{450, 500},
		{500, 500},
		{100, 400},
		{150, 350},
		{200, 300},
		{250, 250},
		{300, 200},
		{350, 150},
		{400, 100},
	},
	-- World 6 (17)
	{
		{50, 500},
		{100, 500},
		{150, 500},
		{200, 500},
		{250, 500},
		{300, 500},
		{350, 500},
		{400, 500},
		{450, 500},
		{500, 500},
		{100, 400},
		{150, 350},
		{200, 300},
		{250, 250},
		{300, 200},
		{350, 150},
		{400, 100},
	},
	-- World 7 (17)
	{
		{50, 500},
		{100, 500},
		{150, 500},
		{200, 500},
		{250, 500},
		{300, 500},
		{350, 500},
		{400, 500},
		{450, 500},
		{500, 500},
		{100, 400},
		{150, 350},
		{200, 300},
		{250, 250},
		{300, 200},
		{350, 150},
		{400, 100},
	},
	-- World 8 (8)
	{
		{50, 500},
		{150, 500},
		{250, 500},
		{350, 500},
		{450, 500},
		{100, 400},
		{200, 300},
		{300, 200},
	},
}