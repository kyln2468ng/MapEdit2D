#define NOMINMAX
#include "MapChip.h"
#include "Source/Screen.h"
#include "Input.h"
#include "ImGui/imgui.h"
#include <algorithm>

namespace
{
	// 同じ名前の変数は後でまとめましょう
	//const int IMAGE_SIZE = { 32 }; // 画像のサイズ
	//const int MAP_CHIP_WIDTH = { 16 }; // チップの横並び数
	//const int MAP_CHIP_HEIGHT = { 12 }; // チップの縦並び数
	//const int MAP_CHIP_NUM_X = { 8 };
	//const int MAP_CHIP_NUM_Y = { 24};
	//const int MAP_CHIP_WIN_WIDTH = { IMAGE_SIZE * MAP_CHIP_NUM_X };
	//const int MAP_CHIP_WIN_HEIGHT = { IMAGE_SIZE * MAP_CHIP_NUM_Y };
	//int TOPLEFT_X = Screen::WIDTH - MAP_CHIP_WIN_WIDTH;
	//int TOPLEFT_Y = 0;
	//int RIGHTBOTTOM_X = Screen::WIDTH;
	//int RIGHTBOTTOM_Y = MAP_CHIP_WIN_HEIGHT;
	// const int DRAG_THRESHOLD = 5;
}

MapChip::MapChip()
	:GameObject(),cfg_(GetMapChipConfig()), isUpdate_(false), isInMapChipArea_(false), selectedIndex_(-1)
	, hImage_(cfg_.TILE_X * cfg_.TILE_Y, -1), selected_({ 0,0 }) //初期値を-1で16*12の配列を初期化する
	,isHold_(false),ScrollOffset_({0,0})
{
	/*char buff[128];
	GetPrivateProfileStringA("MapChip", "Title", "MYGAME", buff, sizeof(buff), "./mySetup.ini");
	int wsize = GetPrivateProfileInt("MapChip", "WinSize",255, "./mySetup.ini");*/

	hImage_.resize(cfg_.TILE_PIX_SIZE * cfg_.TILE_X * cfg_.TILE_Y, -1);
	LoadDivGraph("./bg.png", cfg_.TILE_X * cfg_.TILE_Y, cfg_.TILE_X, cfg_.TILE_Y, cfg_.TILE_PIX_SIZE, cfg_.TILE_PIX_SIZE, hImage_.data());
	//for (int i = 0; i < MAP_CHIP_NUM_X; i++) {
	//	for (int j = 0; j < MAP_CHIP_NUM_Y; j++) {
	//		Rect tmp{
	//			i * IMAGE_SIZE, j * IMAGE_SIZE,
	//			IMAGE_SIZE, IMAGE_SIZE
	//		};
	//		bgRects_.push_back(tmp);
	//	}
	//}
	// 
	// isInMapChipArea_ = false;

	// LUT(Look Up Table) 作成
	for (int i = 0;i < hImage_.size();i++)
	{
		// HandlToIndex[ハンドル番号]=i　※ハンドル番号i番目が何番か帰ってくるようにする
		// hImage[i]->i   ＿↑
		// HandlToIndex[hImage[i]] = i
		HandlToIndex[hImage_[i]] = i;
	}
}

MapChip::~MapChip()
{
	for (int i = 0; i < cfg_.TILE_X * cfg_.TILE_Y;i++)
	{
		if (hImage_[i] != -1)
		{
			DeleteGraph(hImage_[i]);
			hImage_[i] = -1;
		}
	}
}

Point MapChip::GetViewOrigin() const
{
	return { Screen::WIDTH - cfg_.MAPCHIP_WIN_WIDTH,0 };
}

bool MapChip::IsInChipArea(const Point& mouse) const
{
	return (mouse.x > GetViewOrigin().x && mouse.x < Screen::WIDTH && mouse.y > 0 && mouse.y < Screen::HEIGHT);
}

Point MapChip::ScreenToChipIndex(const Point& mouse) const
{
	int localX = (mouse.x - GetViewOrigin().x) / cfg_.TILE_PIX_SIZE;
	int localY = mouse.y / cfg_.TILE_PIX_SIZE;
	return { localX,localY };
}

void MapChip::Update()
{
	
	Point mousePos;
	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1)
	{
		return;
	}

	isInMapChipArea_ = IsInChipArea(mousePos);

	if (isInMapChipArea_)
	{
		//if (Input::IsKeyDown(KEY_INPUT_LEFT))
		//	//ScrollOffset_.y = std::min(std::max(cfg_.MAPCHIP_VIEW_X,cfg_.TILE_X - cfg_.MAPCHIP_VIEW_X), ScrollOffset_.x + 1);
		//	ScrollOffset_.x = ScrollOffset_.x + 1;
		//if (Input::IsKeyDown(KEY_INPUT_RIGHT))
		//	ScrollOffset_.x = std::max(0, ScrollOffset_.x - 1);
		//	//ScrollOffset_.x += 1;
		//if (Input::IsKeyDown(KEY_INPUT_UP))
		//	ScrollOffset_.y = std::max(0, ScrollOffset_.y - 1);
		//if (Input::IsKeyDown(KEY_INPUT_DOWN))
		//	//ScrollOffset_.y += 1;
		//	ScrollOffset_.y = std::min(std::max(0, cfg_.TILE_Y - cfg_.MAPCHIP_VIEW_Y), ScrollOffset_.y + 1);


		if (Input::IsKeyDown(KEY_INPUT_LEFT))
			ScrollOffset_.x = std::max(0, ScrollOffset_.x - 1);
		if (Input::IsKeyDown(KEY_INPUT_RIGHT))
			ScrollOffset_.x = std::min(std::max(0, cfg_.TILE_X - cfg_.MAPCHIP_VIEW_X), ScrollOffset_.x + 1);
		if (Input::IsKeyDown(KEY_INPUT_UP))
			ScrollOffset_.y = std::max(0, ScrollOffset_.y - 1);
		if (Input::IsKeyDown(KEY_INPUT_DOWN))
			ScrollOffset_.y = std::min(std::max(0, cfg_.TILE_Y - cfg_.MAPCHIP_VIEW_Y), ScrollOffset_.y + 1);


		selected_ = ScreenToChipIndex(mousePos);

		int gx = selected_.x + ScrollOffset_.x;
		int gy = selected_.y + ScrollOffset_.y;
		//int index = selected_.y * cfg_.TILE_X + selected_.x;
		int index = gy * cfg_.TILE_X + gy;

		if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
		{
			isHold_ = true;
			selectedIndex_ = hImage_[index];
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
	
	/*for (int j = 0;j < cfg_.TILE_Y;j++)
	{
		for (int i = 0; i < cfg_.TILE_X;i++)
		{
			DrawGraph(GetViewOrigin().x + i * cfg_.TILE_PIX_SIZE, GetViewOrigin().y + j * cfg_.TILE_PIX_SIZE, hImage_[i + j * cfg_.TILE_X], TRUE);
		}
	}*/

	//for (int j = 0;j < cfg_.TILE_Y;j++)
	//{
	//	for (int i = 0;i < cfg_.TILE_X;i++)
	//	{
	//		int index = i + ScrollOffset_.x + (j + ScrollOffset_.y) * cfg_.TILE_X;
	//		//int index = i + (j + ScrollOffset_.y) * cfg_.TILE_Y;
	//		if (index < 0 || index >= hImage_.size())
	//			continue;
	//		
	//		DrawGraph(GetViewOrigin().x + i * cfg_.TILE_PIX_SIZE,
	//				  GetViewOrigin().y + j * cfg_.TILE_PIX_SIZE,
	//				  hImage_[index], TRUE);
	//		
	//	}
	//}

	const int originX = GetViewOrigin().x;
	const int originY = GetViewOrigin().y;

	// チップ表示
	for (int y = 0; y < cfg_.TILE_Y-4; y++) {
		for (int x = 0; x < cfg_.TILE_X; x++) {

			int gx = x + ScrollOffset_.x;
			int gy = y + ScrollOffset_.y;
			//int index = gy * cfg_.TILES_X + gx;
			int index = gy * cfg_.TILE_X+ gx;
			DrawGraph(originX + x * cfg_.TILE_PIX_SIZE,
				originY + y * cfg_.TILE_PIX_SIZE,
				hImage_[index], TRUE);
		}
	}

 	//DrawBox(TOPLEFT_X,TOPLEFT_Y,RIGHTBOTTOM_X,RIGHTBOTTOM_Y, GetColor(255, 0, 0), FALSE, 3);
	
	//if (isInMapChipArea_)
	//{
	//	int px = GetViewOrigin().x + selected_.x * cfg_.TILE_PIX_SIZE;
	//	int py = selected_.y * cfg_.TILE_PIX_SIZE;

	//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//	DrawBox(px, py, px + cfg_.TILE_PIX_SIZE, py + cfg_.TILE_PIX_SIZE, GetColor(32, 255, 193), TRUE);
	//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//	DrawBox(px, py, px + cfg_.TILE_PIX_SIZE, py + cfg_.TILE_PIX_SIZE, GetColor(255, 0, 0), FALSE, 2);
	//	

	///*	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//	DrawBox(TOPLEFT_X, TOPLEFT_Y, RIGHTBOTTOM_X, RIGHTBOTTOM_Y, GetColor(132, 255, 193), TRUE);
	//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);*/
	//}


	if (isInMapChipArea_) {
		int x = originX + selected_.x * cfg_.TILE_PIX_SIZE;
		int y = selected_.y * cfg_.TILE_PIX_SIZE;
		int size = cfg_.TILE_PIX_SIZE;

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(x + 1, y - 1, x + size - 1, y + size + 1, GetColor(255, 255, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawBox(x, y, x + size, y + size, GetColor(255, 0, 0), FALSE, 2);
	}

	if (isHold_)
	{
		Point mousePos;
		if (GetMousePoint(&mousePos.x, &mousePos.y) != -1)
		{
			DrawExtendGraph(mousePos.x, mousePos.y,
				mousePos.x + cfg_.TILE_PIX_SIZE, mousePos.y + cfg_.TILE_PIX_SIZE, selectedIndex_, TRUE);
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

int MapChip::GetChipIndex(int handle)
{
	/*for (int i = 0; i < hImage_.size();i++)
	{
		if (handle == hImage_[i])
		{
			return i;
		}
	}*/
	return HandlToIndex[handle];
}

