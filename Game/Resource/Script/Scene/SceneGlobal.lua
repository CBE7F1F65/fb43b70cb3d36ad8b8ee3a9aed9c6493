--
CCSTL_Debug	=	CCTag_Layer_14;
CCSTL_BG = CCTag_Layer_00;
--

-- TitleScene
--
CCTSTL_Menu = CCTag_Layer_01;
	CCTSTM_Menu_Main = CCTag_Menu_01;
	--
	CCTSTM_Menu_MainDelay = CCTag_Menu_14;
CCTSTL_HiScore = CCTag_Layer_03;
	CCTSTM_HiScore_Menu = CCTag_Menu_01;
	CCTSTM_HiScore_Display = CCTag_Menu_03;
	CCTSTM_HiScore_OKCancel = CCTag_Menu_04;
	--
	CCTSTM_HiScore_MenuDelay = CCTag_Menu_14;
	CCTSTM_HiScore_OKCancelDelay = CCTag_Menu_11;
CCTSTL_Option = CCTag_Layer_05;
	CCTSTM_Option_Menu = CCTag_Menu_01;
	CCTSTM_Option_OKCancel = CCTag_Menu_04;
	--
	CCTSTM_Option_MenuDelay = CCTag_Menu_14;
	CCTSTM_Option_OKCancelDelay = CCTag_Menu_11;
CCTSTL_BGMTouch = CCTag_Layer_06;
	CCTSTM_BGMTouch_Bar = CCTag_Menu_01;
CCTSTL_SETouch = CCTag_Layer_07;
	CCTSTM_SETouch_Bar = CCTag_Menu_01;
CCTSTL_Online = CCTag_Layer_09;
	CCTSTM_Online_Menu = CCTag_Menu_01;
	--
	CCTSTM_Online_MenuDelay = CCTag_Menu_14;
CCTSTL_Input = CCTag_Layer_13;
	CCTSTM_Input_Layer = CCTag_Menu_01;
	CCTSTM_Input_Hint = CCTag_Menu_04;
--

-- StoryScene
--
CCSSTL_Menu = CCTag_Layer_01;
	CCSSTM_Menu_Main = CCTag_Menu_01;
	--
	CCSSTM_Menu_MainDelay = CCTag_Menu_14;
--

-- StageSelectScene
--
CCSSSTL_Menu = CCTag_Layer_01;
	CCSSSTM_Menu_Main = CCTag_Menu_01;
	--
	CCSSSTM_Menu_MainDelay = CCTag_Menu_14;
--

-- MissionSelectScene
--
CCMSSTL_Menu = CCTag_Layer_01;
	CCMSSTM_Menu_Main = CCTag_Menu_01;
	--
	CCMSSTM_Menu_MainDelay = CCTag_Menu_14;
--

-- HelpScene
--
CCHSTL_Menu = CCTag_Layer_01;
	CCHSTM_Menu_Main = CCTag_Menu_01;
	CCHSTM_Menu_Category = CCTag_Menu_02;
	--
	CCHSTM_Menu_MainDelay = CCTag_Menu_14;
	CCHSTM_Menu_CategoryDelay = CCTag_Menu_13;
CCHSTL_Sub = CCTag_Layer_04;
--

-- PlayScene
--
CCPSTL_ObjBG = CCTag_Layer_01;
CCPSTL_Enemy = CCTag_Layer_02;
	CCPSTM_Enemy_CallNode = CCTag_Menu_11;
CCPSTL_ObjFG = CCTag_Layer_03;
CCPSTL_Message = CCTag_Layer_04;
	CCPSTM_Message_TargetBoard = CCTag_Menu_01;
	CCPSTM_Message_OverBoard = CCTag_Menu_02;
	CCPSTM_Message_TargetMenu = CCTag_Menu_04;
	CCPSTM_Message_OverMenu = CCTag_Menu_06;
	--
	CCPSTM_Message_OverMenuDelay = CCTag_Menu_09;
	CCPSTM_Message_TargetMenuDelay = CCTag_Menu_11;
CCPSTL_Frame = CCTag_Layer_05;
CCPSTL_Touch = CCTag_Layer_06;
	CCPSTM_Touch_Layer = CCTag_Menu_01;
CCPSTL_HPAPSP = CCTag_Layer_07;
	CCPSTM_HPAPSP_HPAP = CCTag_Menu_01;
	CCPSTM_HPAPSP_SP = CCTag_Menu_02;
CCPSTL_EnemyOnSide = CCTag_Layer_08;
CCPSTL_Plan = CCTag_Layer_11;
	CCPSTM_Plan_RenderTexture = CCTag_Menu_01;
	CCPSTM_Plan_LinesFeather = CCTag_Menu_04;
	CCPSTM_Plan_CirclesFeather = CCTag_Menu_05;
	CCPSTM_Plan_DotsFeather = CCTag_Menu_06;
	CCPSTM_Plan_XFeather = CCTag_Menu_10;
	CCPSTM_Plan_CallNode = CCTag_Menu_11;
CCPSTL_Menu = CCTag_Layer_13;
	CCPSTM_Menu_Main = CCTag_Menu_01;
	CCPSTM_Menu_PlanGroup = CCTag_Menu_02;
	CCPSTM_Menu_SubLevel01 = CCTag_Menu_03;	--item
	CCPSTM_Menu_QuitRestart = CCTag_Menu_04;
	CCPSTM_Menu_SubLevel02 = CCTag_Menu_05;	--modify
	CCPSTM_Menu_SubLevel03 = CCTag_Menu_06;	--use
	--
	CCPSTM_Menu_MainDelay = CCTag_Menu_14;
	CCPSTM_Menu_SubLevel01Delay = CCTag_Menu_12;	--item
	CCPSTM_Menu_QuitRestartDelay = CCTag_Menu_11;
	CCPSTM_Menu_SubLevel02Delay = CCTag_Menu_10;	--modify
	CCPSTM_Menu_SubLevel03Delay = CCTag_Menu_09;	--use
--


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