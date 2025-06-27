#include "MapEdit.h"
#include "Source/Screen.h"
#include "cassert"
#include "MapChip.h"
#include "Input.h"

MapEdit::MapEdit()
	:GameObject(), myMap_(MAP_WIDTH* MAP_HEIGHT, -1),isMapEditArea_(false),selected_{(0,0)},drawAreaRect{0,0,0,0}
{
	mapEditRect_ = { LEFT_MARGIN,TOP_MARGIN,MAP_WIDTH * MAP_IMAGE_SIZE,MAP_HEIGHT * MAP_IMAGE_SIZE };
}

MapEdit::~MapEdit()
{
}

void MapEdit::SetMap(Point p, int value)
{
	// マップ座標pにvalueをセットする
	// pが、配列の範囲外の時はassertに引っかかる
	
	assert(p.x >= 0 && p.x < MAP_WIDTH);
	assert(p.y >= 0 && p.y < MAP_HEIGHT);
	myMap_[ p.y * MAP_WIDTH + p.x ] = value;
}

int MapEdit::GetMap(Point p) const
{
	// マップ座標pにvalueをセットする
// pが、配列の範囲外の時はassertに引っかかる

	assert(p.x >= 0 && p.x < MAP_WIDTH);
	assert(p.y >= 0 && p.y < MAP_HEIGHT);
	return myMap_[p.y * MAP_WIDTH + p.x];
}

void MapEdit::Update()
{

	Point mousePos;
	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1)
	{
		return;
	}
	// マウス座標がマップエディタ領域内にいるかどうか判定する
	isMapEditArea_ = mousePos.x > mapEditRect_.x && mousePos.x < mapEditRect_.x + mapEditRect_.w && 
					 mousePos.y > mapEditRect_.y && mousePos.y < mapEditRect_.y + mapEditRect_.h;

	if (!isMapEditArea_)
	{
		return; // 領域外なら何もしない
	}

	selected_.x = (mousePos.x - (LEFT_MARGIN)) / MAP_IMAGE_SIZE;
	selected_.y = (mousePos.y - (TOP_MARGIN)) / MAP_IMAGE_SIZE;

	drawAreaRect = { LEFT_MARGIN + selected_.x * MAP_IMAGE_SIZE,TOP_MARGIN + selected_.y * MAP_IMAGE_SIZE,MAP_IMAGE_SIZE,MAP_IMAGE_SIZE };

	if (Input::IsButtonDown(MOUSE_INPUT_LEFT) || Input::IsButtonKeep(MOUSE_INPUT_LEFT))
	{
		MapChip* mapChip = FindGameObject<MapChip>();
		if (mapChip && mapChip->isHold())
		{
			SetMap({ selected_.x,selected_.y }, mapChip->GetHoldImage());
		}

		/*if (Input::IsKeyDown(KEY_INPUT_SPACE))
		{
			SetMap({ selected_.x,selected_.y }, -1);
		}*/
	}

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
			DrawLine(LEFT_MARGIN + i * MAP_IMAGE_SIZE, TOP_MARGIN + j * MAP_IMAGE_SIZE,
				LEFT_MARGIN + (i + 1) * MAP_IMAGE_SIZE, TOP_MARGIN + j * MAP_IMAGE_SIZE, GetColor(255, 255, 255), 1);
			DrawLine(LEFT_MARGIN + i * MAP_IMAGE_SIZE, TOP_MARGIN + j * MAP_IMAGE_SIZE,
				LEFT_MARGIN + i * MAP_IMAGE_SIZE, TOP_MARGIN + (j + 1) * MAP_IMAGE_SIZE, GetColor(255, 255, 255), 1);
		}
	}
	if (isMapEditArea_)
	{
		int xM = LEFT_MARGIN;
		int yM = TOP_MARGIN;
		//DrawBox(mapEditRect_.x, mapEditRect_.y, mapEditRect_.x + mapEditRect_.w, mapEditRect_.y + mapEditRect_.h, GetColor(0, 255, 255), TRUE);
		DrawBox(xM + selected_.x * MAP_IMAGE_SIZE,yM + selected_.y * MAP_IMAGE_SIZE, xM + (selected_.x + 1) * MAP_IMAGE_SIZE,yM + (selected_.y + 1) * MAP_IMAGE_SIZE, GetColor(0, 255, 255), FALSE, 2);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	for (int j = 0;j < MAP_HEIGHT;j++)
	{
		for (int i = 0;i < MAP_WIDTH;i++)
		{
			int value = GetMap({ i,j });
			if (value != -1)
			{
				DrawGraph(LEFT_MARGIN + i * MAP_IMAGE_SIZE, TOP_MARGIN + j * MAP_IMAGE_SIZE, value, TRUE);
			}
		}
	}
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
