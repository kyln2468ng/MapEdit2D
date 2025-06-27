#include "Stage.h"
#include "DxLib.h"
#include "MapChip.h"
#include "MapEdit.h"
#include "Input.h"
#include "./Source/Screen.h"

// shift + alt カーソル, ctrl + カーソル
//namespace
//{
//	const int IMAGE_SIZE = { 32 }; // 画像のサイズ
//	const int MAP_WIDTH = { 32 };
//	const int MAP_HEIGHT = { 22 };
//	const int MAP_CHIP_WIDTH = { 16 };
//	const int MAP_CHIP_HEIGHT = { 12 };
//
//	const int myMap[MAP_HEIGHT][MAP_WIDTH]
//		{
//			{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
//			{6,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,6},
//			{6,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,6},
//			{6,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,6},
//			{6,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,6},
//			{6,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,6},
//			{6,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,6},
//			{6,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,6},
//			{6,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,145,6},
//			{6,145,145,145,145,145,145,145,145,145,145,145,145,118,118,118,118,118,145,145,145,145,145,145,145,145,145,145,145,145,145,6},
//			{6,145,145,145,145,145,145,145,145,145,145,145,145,118,118,118,118,118,145,145,145,145,145,145,145,145,145,145,145,145,145,6},
//			{6,145,145,145,145,145,145,145,145,145,145,145,145,118,103,103,103,118,145,145,145,145,145,145,145,145,145,145,145,145,145,6},
//			{6,145,145,145,145,145,145,145,145,145,145,145,145,118,103,103,103,118,145,145,145,145,145,145,145,145,145,145,145,145,145,6},
//			{6,145,145,145,145,145,145,145,145,145,145,145,145,145,149,149,149,145,145,145,145,145,145,145,145,145,145,145,145,145,145,6},
//			{6,145,145,145,145,145,145,145,145,145,145,145,145,145,149,149,149,145,145,145,145,145,145,145,145,145,145,145,145,145,145,6},
//			{6,145,145,145,145,145,145,145,145,145,145,145,145,145,149,149,149,145,145,145,145,145,145,145,145,145,145,145,145,145,145,6},
//			{6,145,145,145,145,145,145,145,145,145,145,145,145,145,149,149,149,145,145,145,145,145,145,145,145,145,145,145,145,145,145,6},
//			{6,145,145,145,145,145,145,145,145,145,145,145,145,145,149,149,149,145,145,145,145,145,145,145,145,145,145,145,145,145,145,6},
//			{6,145,145,145,145,145,145,145,145,145,145,145,145,145,149,149,149,145,145,145,145,145,145,145,145,145,145,145,145,145,145,6},
//			{6,145,145,145,145,145,145,145,145,145,145,145,145,145,149,149,149,145,145,145,145,145,145,145,145,145,145,145,145,145,145,6},
//			{6,145,145,145,145,145,145,145,145,145,145,145,145,145,149,149,149,145,145,145,145,145,145,145,145,145,145,145,145,145,145,6},
//			{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6}
//
//		};
//}

namespace
{
	const int MAP_CHIP_NUM_X = { 8 };
	const int MAP_CHIP_MARGIN_WIDTH = { MAP_CHIP_NUM_X * 32 };
	const int MAP_CHIP_WIDTH = Screen::WIDTH - MAP_CHIP_MARGIN_WIDTH;
}

Stage::Stage()
	:GameObject()
{
	/*GameObject();
	hImage = -1;
	imageSize = 32;
	imageElement = 16;*/
	//hImage = new int[MAP_WIDTH * MAP_HEIGHT]; // 必要な時に必要な数だけ配列を準備する方法
	//hImage = std::vector<int>(MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT, -1);

	////hImage = LoadGraph("./bg.png");
	//LoadDivGraph("./bg.png", MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT, IMAGE_SIZE, IMAGE_SIZE, hImage.data());

	mapChip_ = new MapChip();
	mapEdit_ = new MapEdit();
	
}

Stage::~Stage()
{
	/*for (int i = 0;i < MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT;i++)
	{
		if (hImage[i] != -1)
		{
			DeleteGraph(i);
			hImage[i] = -1;
		}
	}*/
	//delete[] hImage; // 配列の開放　自分で取ったものは自分で消す

	/*if (hImage != -1)
	{
		DeleteGraph(hImage);
		hImage = -1;
	}*/
	delete mapChip_;
	//delete mapEdit_;
}

void Stage::Update()
{
	//if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
	//{
	//	// マウスが押された時の処理
	//	DxLib::printfDx("左押された！！\n");
	//}
	//if (Input::IsButtonDown(MOUSE_INPUT_RIGHT))
	//{
	//	// マウスが押された時の処理
	//	DxLib::printfDx("右押された！！\n");
	//}
	//if (Input::IsButtonKeep(MOUSE_INPUT_LEFT))
	//{
	//	// マウスが押された時の処理
	//	DxLib::printfDx("左押され続けてる！！\n");
	//}
	//if (Input::IsButtonKeep(MOUSE_INPUT_RIGHT))
	//{
	//	// マウスが押された時の処理
	//	DxLib::printfDx("右押された！！\n");
	//}
	//if (Input::IsButtonUP(MOUSE_INPUT_LEFT))
	//{
	//	// マウスが押された時の処理
	//	DxLib::printfDx("左離された！！\n");
	//}
	//if (Input::IsButtonUP(MOUSE_INPUT_RIGHT))
	//{
	//	// マウスが押された時の処理
	//	DxLib::printfDx("右離された！！\n");
	//}

	/*int mx = -1, my = -1;
	if (GetMousePoint(&mx, &my) == 0)
	{
		DxLib::printfDx("マウスの座標(%d,%d)\n", mx, my);
	}
	else
	{
		DxLib::printfDx("マウスの座標取得失敗\n");
	}*/
	//if ((mx > MAP_CHIP_WIDTH) && (mx < Screen::WIDTH) && (my > 0) && (my < Screen::HEIGHT))
	//{
	//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	//	//DrawBox(MAP_CHIP_WIDTH, 0, Screen::WIDTH, Screen::HEIGHT, GetColor(0, 255, 255), FALSE, 5);
	//	if (mx)
	//	{
	//	}
	//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//}

	/*Point mousePos;
	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1)
	{
		return;
	}*/
}

void Stage::Draw()
{
	//for (int j = 0; j < MAP_HEIGHT; j++)
	//{
	//	for (int i = 0; i < MAP_WIDTH; i++)
	//	{
	//		if (hImage[myMap[j][i]] != -1)
	//		{
	//			/*int kx = myMap[j][i] % imageElement;
	//				int ky = myMap[j][i] / imageElement;*/
	//			/*int ky = myMap[i][j] / 16;
	//				int kx = myMap[j][i] - ky;*/
	//			DrawGraph(i * IMAGE_SIZE, j * IMAGE_SIZE, hImage[myMap[j][i]], TRUE);
	//		}
	//	}
	//}
	
}

bool Stage::RightMouseCheck()
{
	if (Input::IsButtonDown(MOUSE_INPUT_RIGHT))
	{
		return true;
	}
}
