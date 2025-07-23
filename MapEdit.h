#pragma once
#include "Library/GameObject.h"
#include <vector>
#include "globals.h"
#include "MapEditConfig.h"

//namespace
//{
//    const int MAP_IMAGE_SIZE = { 32 }; // 画像のサイズ
//    const int MAP_WIDTH = { 20 };
//    const int MAP_HEIGHT = { 20 };
//    const int LEFT_MARGIN = { 100 };
//    const int TOP_MARGIN = { 40 };
//}

class MapEdit :
    public GameObject
{
public:
    MapEdit();
    ~MapEdit();

    void SetMap(Point p, int value);
    int GetMap(Point p) const;
    void Update() override;
    void Draw() override;
    void SaveMapData();
    void LoadMapDate();
    void ResizeMap(int newWidth, int newHeight);
private:
    MapEditConfig efg_; // マップチップの設定を保持する
    std::vector<int> myMap_;
    Rect mapEditRect_;
    Rect drawAreaRect;
    bool isMapEditArea_ = false;
    Point selected_;
    int hHandl;
    Point ScrollOffset_; // スクロールオフセット
};

