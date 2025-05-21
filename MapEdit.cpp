#include "MapEdit.h"
#include "Source/Screen.h"

MapEdit::MapEdit()
	:GameObject(), myMap_(MAP_WIDTH* MAP_HEIGHT, -1)
{
}

MapEdit::~MapEdit()
{
}

void MapEdit::Update()
{
}

void MapEdit::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(LEFT_MARGIN, TOP_MARGIN, MAP_IMAGE_SIZE * MAP_WIDTH + LEFT_MARGIN, MAP_IMAGE_SIZE * MAP_HEIGHT + TOP_MARGIN, GetColor(255, 0, 0), FALSE,5);
	//int MAP_MAX = MAP_HEIGHT * MAP_WIDTH;
	//for (int i = 0;i < MAP_MAX;i++)
	//{
	//	DrawLine(i % MAP_MAX * MAP_IMAGE_SIZE + LEFT_MARGIN, i / MAP_MAX * MAP_IMAGE_SIZE + TOP_MARGIN, i % MAP_MAX * MAP_IMAGE_SIZE + LEFT_MARGIN, i / MAP_MAX * MAP_IMAGE_SIZE + TOP_MARGIN, GetColor(0, 255, 0));
	//}
	for (int j = 0;j < MAP_HEIGHT;j++)
	{
		for (int i = 0;i < MAP_WIDTH;i++)
		{
			DrawLine(LEFT_MARGIN + i * MAP_IMAGE_SIZE, TOP_MARGIN + j * MAP_IMAGE_SIZE, LEFT_MARGIN + (i + 1) * MAP_IMAGE_SIZE, TOP_MARGIN + j * MAP_IMAGE_SIZE, GetColor(255, 255, 255), 1);
			DrawLine(LEFT_MARGIN + i * MAP_IMAGE_SIZE, TOP_MARGIN + j * MAP_IMAGE_SIZE, LEFT_MARGIN + i * MAP_IMAGE_SIZE, TOP_MARGIN + (j + 1) * MAP_IMAGE_SIZE, GetColor(255, 255, 255), 1);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	/*for (int i = 0;i < MAP_HEIGHT+1;i++)
	{
		DrawLine(LEFT_MARGIN, i * MAP_IMAGE_SIZE + TOP_MARGIN, MAP_WIDTH * MAP_IMAGE_SIZE + LEFT_MARGIN, i * MAP_IMAGE_SIZE + TOP_MARGIN, GetColor(0, 255, 0));
	}
	for (int j = 0;j < MAP_WIDTH+1;j++)
	{
		DrawLine(j * MAP_IMAGE_SIZE + LEFT_MARGIN, TOP_MARGIN, j * MAP_IMAGE_SIZE + LEFT_MARGIN, MAP_HEIGHT * MAP_IMAGE_SIZE + TOP_MARGIN, GetColor(0, 255, 0));
	}*/
	//DrawBox(j * MAP_IMAGE_SIZE + LEFT_MARGIN, i * MAP_IMAGE_SIZE + TOP_MARGIN, MAP_IMAGE_SIZE * (j + 1) + LEFT_MARGIN, MAP_IMAGE_SIZE * (i + 1) + TOP_MARGIN, GetColor(255, 0, 0), FALSE);

}
