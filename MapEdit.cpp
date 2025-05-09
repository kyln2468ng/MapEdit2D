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
	DrawBox(LEFT_MARGIN, TOP_MARGIN, MAP_IMAGE_SIZE * MAP_WIDTH + LEFT_MARGIN, MAP_IMAGE_SIZE * MAP_HEIGHT + TOP_MARGIN, GetColor(255, 0, 0), FALSE,5);
	for (int i = 0;i < MAP_HEIGHT;i++)
	{
		DrawLine(0, i * MAP_IMAGE_SIZE, MAP_WIDTH * MAP_IMAGE_SIZE, i * MAP_IMAGE_SIZE, GetColor(0, 255, 0));
	}
	for (int j = 0;j < MAP_WIDTH;j++)
	{
		DrawLine(j * MAP_IMAGE_SIZE,0,j*MAP_IMAGE_SIZE,MAP_HEIGHT*MAP_IMAGE_SIZE, GetColor(0, 255, 0));
	}
	//DrawBox(j * MAP_IMAGE_SIZE + LEFT_MARGIN, i * MAP_IMAGE_SIZE + TOP_MARGIN, MAP_IMAGE_SIZE * (j + 1) + LEFT_MARGIN, MAP_IMAGE_SIZE * (i + 1) + TOP_MARGIN, GetColor(255, 0, 0), FALSE);

}
