--local lx, rx, by = 32, 928, 608;

LGlobal_EnemySideEdge = 64;

LGlobal_EnemySideLEdge = 64;
LGlobal_EnemySideREdge = 896;
LGlobal_EnemySideTEdge = 96;
LGlobal_EnemySideBEdge = 576;

LGlobal_EnemySideLEdgeCenter = 32;
LGlobal_EnemySideREdgeCenter = 928;
LGlobal_EnemySideBEdgeCenter = 608;



LGlobal_EnemyPosTable	=	
{
	--World1
	{
		--Mission1 (skip event mission)
		{
			--Init
			{
				--Enemy1
				-- x, y, type, layer
				{150, 350, 4, CCZ_eLayer_01},
				{250, 450, 5, CCZ_eLayer_02},
				{550, 450, 6, CCZ_eLayer_03},
			},
			--Turn1
			-- xorig, yorig, type, angle
			{
				{34, 300, 1, 4600},
				{650, 600, 2, 20700},
			},
			--Turn2
			-- xorig, yorig, type, angle
			{
				{60, 450, 3, 7500},
				{896, 400, 4, 27000},
			},
		},
	},
};