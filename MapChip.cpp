#include "MapChip.h"
#include "Source/Screen.h"
#include "Input.h"
#include "ImGui/imgui.h"

namespace
{
	// 同じ名前の変数は後でまとめましょう
	const int IMAGE_SIZE = { 32 }; // 画像のサイズ
	const int MAP_CHIP_WIDTH = { 16 }; // チップの横並び数
	const int MAP_CHIP_HEIGHT = { 12 }; // チップの縦並び数
	const int MAP_CHIP_NUM_X = { 8 };
	const int MAP_CHIP_NUM_Y = { 24};
	const int MAP_CHIP_WIN_WIDTH = { IMAGE_SIZE * MAP_CHIP_NUM_X };
	const int MAP_CHIP_WIN_HEIGHT = { IMAGE_SIZE * MAP_CHIP_NUM_Y };
	int TOPLEFT_X = Screen::WIDTH - MAP_CHIP_WIN_WIDTH;
	int TOPLEFT_Y = 0;
	int RIGHTBOTTOM_X = Screen::WIDTH;
	int RIGHTBOTTOM_Y = MAP_CHIP_WIN_HEIGHT;
}

MapChip::MapChip()
	:GameObject(), isUpdate_(false), isInMapChipArea_(false), selectedIndex_(-1)
	, hImage_(MAP_CHIP_WIDTH* MAP_CHIP_HEIGHT, -1), selected_({ 0,0 }) //初期値を-1で16*12の配列を初期化する
{
	LoadDivGraph("./bg.png", MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT, IMAGE_SIZE, IMAGE_SIZE, hImage_.data());
	for (int i = 0; i < MAP_CHIP_NUM_X; i++) {
		for (int j = 0; j < MAP_CHIP_NUM_Y; j++) {
			Rect tmp{
				i * IMAGE_SIZE, j * IMAGE_SIZE,
				IMAGE_SIZE, IMAGE_SIZE
			};
			bgRects_.push_back(tmp);
		}
	}
	// isInMapChipArea_ = false;
}

MapChip::~MapChip()
{
	for (int i = 0; i < MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT;i++)
	{
		if (hImage_[i] != -1)
		{
			DeleteGraph(hImage_[i]);
			hImage_[i] = -1;
		}
	}
}

void MapChip::Update()
{
	
	Point mousePos;
	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1)
	{
		return;
	}

	isInMapChipArea_ = (mousePos.x > Screen::WIDTH - MAP_CHIP_WIN_WIDTH && mousePos.x < Screen::WIDTH &&mousePos.y > 0 && mousePos.y < MAP_CHIP_WIN_HEIGHT);

	if (isInMapChipArea_)
	{
		selected_.x = (mousePos.x - (Screen::WIDTH - MAP_CHIP_WIN_WIDTH)) / IMAGE_SIZE;
		selected_.y = mousePos.y / IMAGE_SIZE;
		if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
		{
			isHold_ = true;
			selectedIndex_ = hImage_[selected_.y * MAP_CHIP_NUM_X + selected_.x];
		}
	}
	else
	{
		isInMapChipArea_ = false;
	}

	//if (Input::IsMouseDown())
	//{
	//	DxLib::printfDx("左押された！！\n");
	//}
}

void MapChip::Draw()
{
	
	for (int i = 0;i < MAP_CHIP_NUM_X;i++)
	{
		for (int j = 0; j < MAP_CHIP_NUM_Y;j++)
		{
			DrawGraph(TOPLEFT_X + i * IMAGE_SIZE, TOPLEFT_Y + j * IMAGE_SIZE, hImage_[i + j * MAP_CHIP_NUM_X], TRUE);
		}
	}
 	//DrawBox(TOPLEFT_X,TOPLEFT_Y,RIGHTBOTTOM_X,RIGHTBOTTOM_Y, GetColor(255, 0, 0), FALSE, 3);
	if (isInMapChipArea_)
	{
		int xM = Screen::WIDTH - MAP_CHIP_WIN_WIDTH;
		
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(xM + selected_.x * IMAGE_SIZE + 1, selected_.y * IMAGE_SIZE - 1, xM + (selected_.x + 1) * IMAGE_SIZE - 1, (selected_.y + 1) * IMAGE_SIZE + 1, GetColor(32, 255, 193), true, 2);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawBox(xM + selected_.x * IMAGE_SIZE, selected_.y * IMAGE_SIZE, xM + (selected_.x + 1) * IMAGE_SIZE, (selected_.y + 1) * IMAGE_SIZE, GetColor(255, 0, 0), FALSE, 2);

		

	/*	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(TOPLEFT_X, TOPLEFT_Y, RIGHTBOTTOM_X, RIGHTBOTTOM_Y, GetColor(132, 255, 193), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);*/
	}

	if (isHold_)
	{
		Point mousePos;
		if (GetMousePoint(&mousePos.x, &mousePos.y) != -1)
		{
			DrawExtendGraph(mousePos.x, mousePos.y,
				mousePos.x + IMAGE_SIZE, mousePos.y + IMAGE_SIZE, selectedIndex_, TRUE);
		}
		if (Input::IsButtonUP(MOUSE_INPUT_RIGHT))
		{
			isHold_ = false;
			selectedIndex_ = -1;
		}
	}
}

bool MapChip::isHold()
{
	return isHold_;
}

int MapChip::GetHoldImage()
{
	if (isHold_)
	{
		return selectedIndex_;
	}
	else
	{
		return -1;
	}
}
