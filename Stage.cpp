#include "Stage.h"
#include "DxLib.h"

namespace
{
	const int MAP_WIDTH = { 10 };
	const int MAP_HEIGHT = { 10 };
	const int myMap[MAP_HEIGHT][MAP_WIDTH]
		{
			{ 0,0,8,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0 }
		};
}

Stage::Stage()
	:GameObject(),hImage(-1),anim(0)
{
	hImage = LoadGraph("./bg.png");
}

Stage::~Stage()
{
	if (hImage != -1)
	{
		DeleteGraph(hImage);
		hImage = -1;
	}
}

void Stage::Update()
{
}

void Stage::Draw()
{
	if (hImage != -1)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			for (int i = 0; i < MAP_WIDTH; i++)
			{
				/*if (myMap[i][j] == 0)
				{
					anim = 0;
				}*/
				switch (myMap[j][i])
				{
				case 0:
					anim = 0;
					break;
				case 1:
					anim = 1;
					break;
				case 8:
					anim = 8;
					break;
				}
				DrawRectGraph(i * 32, j * 32, anim * 32, anim * 32, 32, 32, hImage, true);
			}
		}
	}
	
}
