#define NOMINMAX
#include <Windows.h>
#include "MapEdit.h"
#include "Source/Screen.h"
#include "cassert"
#include "MapChip.h"
#include "Input.h"
#include <fstream>
#include <sstream>
#include <iostream>

MapEdit::MapEdit()
	:GameObject(),efg_(GetMapEditConfig()), myMap_(efg_.MAP_WIDTH* efg_.MAP_HEIGHT, -1),isMapEditArea_(false),selected_{(0,0)},drawAreaRect{0,0,0,0}
{
	mapEditRect_ = { efg_.LEFT_MARGIN,efg_.TOP_MARGIN,efg_.MAP_WIDTH * efg_.MAP_IMAGE_SIZE,efg_.MAP_HEIGHT * efg_.MAP_IMAGE_SIZE };
}

MapEdit::~MapEdit()
{
}

void MapEdit::SetMap(Point p, int value)
{
	// マップ座標pにvalueをセットする
	// pが、配列の範囲外の時はassertに引っかかる
	
	assert(p.x >= 0 && p.x < efg_.MAP_WIDTH);
	assert(p.y >= 0 && p.y < efg_.MAP_HEIGHT);
	myMap_[ p.y * efg_.MAP_WIDTH + p.x ] = value;
}

int MapEdit::GetMap(Point p) const
{
	// マップ座標pにvalueをセットする
// pが、配列の範囲外の時はassertに引っかかる

	assert(p.x >= 0 && p.x < efg_.MAP_WIDTH);
	assert(p.y >= 0 && p.y < efg_.MAP_HEIGHT);
	return myMap_[p.y * efg_.MAP_WIDTH + p.x];
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

	selected_.x = (mousePos.x - (efg_.LEFT_MARGIN)) / efg_.MAP_IMAGE_SIZE;
	selected_.y = (mousePos.y - (efg_.TOP_MARGIN)) / efg_.MAP_IMAGE_SIZE;

	drawAreaRect = { efg_.LEFT_MARGIN + selected_.x * efg_.MAP_IMAGE_SIZE,efg_.TOP_MARGIN + selected_.y * efg_.MAP_IMAGE_SIZE,efg_.MAP_IMAGE_SIZE,efg_.MAP_IMAGE_SIZE };

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
	if (Input::IsKeyDown(KEY_INPUT_S))
	{
		SaveMapData();
	}
	if (Input::IsKeyDown(KEY_INPUT_L))
	{
		LoadMapDate();
	}

	if (Input::IsKeyDown(KEY_INPUT_RIGHT))
	{
		
	}
}

void MapEdit::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(efg_.LEFT_MARGIN, efg_.TOP_MARGIN, efg_.MAP_IMAGE_SIZE * efg_.MAP_WIDTH + efg_.LEFT_MARGIN, efg_.MAP_IMAGE_SIZE * efg_.MAP_HEIGHT + efg_.TOP_MARGIN, GetColor(255, 0, 0), FALSE, 5);
	//int MAP_MAX = efg_.MAP_HEIGHT * efg_.MAP_WIDTH;
	//for (int i = 0;i < MAP_MAX;i++)
	//{
	//	DrawLine(i % MAP_MAX * efg_.MAP_IMAGE_SIZE + efg_.LEFT_MARGIN, i / MAP_MAX * efg_.MAP_IMAGE_SIZE + efg_.TOP_MARGIN, i % MAP_MAX * efg_.MAP_IMAGE_SIZE + efg_.LEFT_MARGIN, i / MAP_MAX * efg_.MAP_IMAGE_SIZE + efg_.TOP_MARGIN, GetColor(0, 255, 0));
	//}
	for (int j = 0;j < efg_.MAP_HEIGHT;j++)
	{
		for (int i = 0;i < efg_.MAP_WIDTH;i++)
		{
			DrawLine(efg_.LEFT_MARGIN + i * efg_.MAP_IMAGE_SIZE, efg_.TOP_MARGIN + j * efg_.MAP_IMAGE_SIZE,
				efg_.LEFT_MARGIN + (i + 1) * efg_.MAP_IMAGE_SIZE, efg_.TOP_MARGIN + j * efg_.MAP_IMAGE_SIZE, GetColor(255, 255, 255), 1);
			DrawLine(efg_.LEFT_MARGIN + i * efg_.MAP_IMAGE_SIZE, efg_.TOP_MARGIN + j * efg_.MAP_IMAGE_SIZE,
				efg_.LEFT_MARGIN + i * efg_.MAP_IMAGE_SIZE, efg_.TOP_MARGIN + (j + 1) * efg_.MAP_IMAGE_SIZE, GetColor(255, 255, 255), 1);
		}
	}
	if (isMapEditArea_)
	{
		int xM = efg_.LEFT_MARGIN;
		int yM = efg_.TOP_MARGIN;
		//DrawBox(mapEditRect_.x, mapEditRect_.y, mapEditRect_.x + mapEditRect_.w, mapEditRect_.y + mapEditRect_.h, GetColor(0, 255, 255), TRUE);
		DrawBox(xM + selected_.x * efg_.MAP_IMAGE_SIZE,yM + selected_.y * efg_.MAP_IMAGE_SIZE, xM + (selected_.x + 1) * efg_.MAP_IMAGE_SIZE,yM + (selected_.y + 1) * efg_.MAP_IMAGE_SIZE, GetColor(0, 255, 255), TRUE, 2);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	for (int j = 0;j < efg_.MAP_HEIGHT;j++)
	{
		for (int i = 0;i < efg_.MAP_WIDTH;i++)
		{
			int value = GetMap({ i,j });
			if (value != -1)
			{
				DrawGraph(efg_.LEFT_MARGIN + i * efg_.MAP_IMAGE_SIZE, efg_.TOP_MARGIN + j * efg_.MAP_IMAGE_SIZE, value, TRUE);
			}
		}
	}
	/*for (int i = 0;i < efg_.MAP_HEIGHT+1;i++)
	{
		DrawLine(efg_.LEFT_MARGIN, i * efg_.MAP_IMAGE_SIZE + efg_.TOP_MARGIN, efg_.MAP_WIDTH * efg_.MAP_IMAGE_SIZE + efg_.LEFT_MARGIN, i * efg_.MAP_IMAGE_SIZE + efg_.TOP_MARGIN, GetColor(0, 255, 0));
	}
	for (int j = 0;j < efg_.MAP_WIDTH+1;j++)
	{
		DrawLine(j * efg_.MAP_IMAGE_SIZE + efg_.LEFT_MARGIN, efg_.TOP_MARGIN, j * efg_.MAP_IMAGE_SIZE + efg_.LEFT_MARGIN, efg_.MAP_HEIGHT * efg_.MAP_IMAGE_SIZE + efg_.TOP_MARGIN, GetColor(0, 255, 0));
	}*/
	//DrawBox(j * efg_.MAP_IMAGE_SIZE + efg_.LEFT_MARGIN, i * efg_.MAP_IMAGE_SIZE + efg_.TOP_MARGIN, efg_.MAP_IMAGE_SIZE * (j + 1) + efg_.LEFT_MARGIN, efg_.MAP_IMAGE_SIZE * (i + 1) + efg_.TOP_MARGIN, GetColor(255, 0, 0), FALSE);

}

void MapEdit::SaveMapData()
{
	// 頑張ってファイル選択ダイアログを出す回
	TCHAR filename[255] = "";
	OPENFILENAME ofn = { 0 };
	
	ofn.lStructSize = sizeof(ofn);
	// ウィンドウのオーナー＝親ウィンドウのハンドル
	ofn.hwndOwner = GetMainWindowHandle();
	ofn.lpstrFilter = "全てのファイル (*.*)\0*.*\0";
	//ofn.lpstrFilter = "テキストドキュメント(*.txt)\0*txt\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = 255;
	ofn.Flags = OFN_OVERWRITEPROMPT;

	//if (GetSaveFileName(&ofn))
	//{
	//	printfDx("ファイルが選択された\n");

	//	// ファイル開いてセーブ
	//	std::ofstream file(ofn.lpstrFile);
	//	file << "#header" << std::endl;
	//	file << "WIDTH " << efg_.MAP_WIDTH << std::endl;
	//	file << "HEIGHT " << efg_.MAP_HEIGHT << std::endl << std::endl;
	//	file << "#data" << std::endl;

	//	MapChip* mc = FindGameObject<MapChip>();

	//	for (int j = 0;j < efg_.MAP_HEIGHT;j++)
	//	{
	//		for (int i = 0;i < efg_.MAP_WIDTH;i++)
	//		{
	//			int index;
	//			if (myMap_[j * efg_.MAP_WIDTH + i] != -1)
	//			{
	//				index = mc->GetChipIndex(myMap_[j * efg_.MAP_WIDTH + i]);
	//			}
	//			else
	//				index = -1;
	//			file << index << " ";
	//		}
	//		file << std::endl;
	//		
	//	}
	//	printfDx("File Save\n");
	//	file.close();
	//	// std::filesystem ファイル名だけ取り出す	
	//}
	//else
	//{
	//	// ファイルの選択がキャンセル
	//	printfDx("セーブがキャンセル\n");
	//}

	// ofnstreamを開く
	
	//std::ofstream opnfile(filename);


	if (GetSaveFileName(&ofn))
	{
		printfDx("ファイルが選択された\n");
		//ファイルを開いて、セーブ
		//std::filesystem ファイル名だけ取り出す
		//ofstreamを開く
		//std::ofstream openfile(filename);
	

		printfDx("File Saved!!!\n");
		std::ofstream openfile(filename);
		//file << "#header" << std::endl;
		openfile << "#TinyMapData\n";

		MapChip* mc = FindGameObject<MapChip>();

		for (int j = 0; j < efg_.MAP_HEIGHT; j++) {
			for (int i = 0; i < efg_.MAP_WIDTH; i++) {

				int index;
				if (myMap_[j * efg_.MAP_WIDTH + i] != -1)
					index = mc->GetChipIndex(myMap_[j * efg_.MAP_WIDTH + i]);
				else
					index = -1;
				//openfile << index << " ";
				openfile << index << ",";
			}
			openfile << std::endl;
		}

		openfile.close();
	
	}
	else
	{
		//ファイルの選択がキャンセル
		printfDx("セーブがキャンセル\n");
	}

	//printfDx("File Saved!!!\n");
	//std::ofstream file("data.txt");
	//file << "#header" << std::endl;
	//file << "WIDTH " << efg_.MAP_WIDTH << std::endl;
	//file << "HEIGHT " << efg_.MAP_HEIGHT << std::endl << std::endl;
	//file << "#data" << std::endl;


	/*for (auto& itr : myMap_)
	{
		file << itr << std::endl;
	}*/

	//for (int i = 0;i < myMap_.size();i++)
//{
//	file << myMap_[i] << std::endl;
//}
}

void MapEdit::LoadMapDate()
{
	TCHAR filename[255] = "";
	OPENFILENAME ifn = { 0 };

	ifn.lStructSize = sizeof(ifn);
	// ウィンドウのオーナー＝親ウィンドウのハンドル
	ifn.hwndOwner = GetMainWindowHandle();
	ifn.lpstrFilter = "全てのファイル (*.*)\0*.*\0";
	//ofn.lpstrFilter = "テキストドキュメント(*.txt)\0*txt\0";
	ifn.lpstrFile = filename;
	ifn.nMaxFile = 255;
	ifn.Flags = OFN_OVERWRITEPROMPT;

	if (GetOpenFileName(&ifn))
	{
		printfDx("open%s\n",filename);
		std::ifstream inputfile(filename);
		// ファイルがオープンされたらチェック必要
		std::string line;

		MapChip* mc = FindGameObject<MapChip>();

		myMap_.clear(); // マップを空に
		while (std::getline(inputfile, line))
		{
			if (line.empty()) continue;
			//printfDx("%s\n", line.c_str());
			// ここに読み込みの処理を書く
			if (line[0] != '#')
			{
				std::istringstream iss(line);
				std::string tmp;// これにいったん読み込み
				while (getline(iss, tmp, ','))
				{
					//if (tmp == -1)
					//	myMap_.push_back(-1);
					//else
					//	myMap_.push_back(mc->GetHandle(tmp)); // マップのハンドルのセット
					
				//	printfDx("%s ", tmp.c_str());

					if (tmp == "-1")
					{
						myMap_.push_back(-1); // 何もしない
					}
					else
					{
						int index = std::stoi(tmp);
						int handle = mc->GetHandle(index);
						myMap_.push_back(handle); // マップにハンドルをセット
					}
				}
				printfDx("\n");
			}
			//else
			//{
			//	// MessageBox(nullptr, "ファイル形式が間違っています", "読み込みエラー", MB_OK | MB_ICONWARNING);
			//}
		}
	}
	else
		printfDx("cansele");
}
