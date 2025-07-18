#pragma once
#include "Library/GameObject.h"
#include <vector>
#include "globals.h"
#include <map>
#include "MapChipConfig.h"

class MapChip :
    public GameObject
{
public:
    MapChip();
    ~MapChip();
    void Update() override;
    void Draw() override;
    int GetHandle(int index) { return hImage_[index]; } //ハンドルを取得する
    bool isHold();
    int GetHoldImage();
    int GetChipIndex(int handle);
    Point GetViewOrigin() const; // マップチップの表示位置を取得するを返す
    bool IsInChipArea(const Point& mouse) const; // const &~ 値変わらない
    Point ScreenToChipIndex(const Point& mouse) const;
private:
    MapChipConfig cfg_; // マップチップの設定を保持する
    std::vector<int> hImage_;
    std::map<int, int> HandlToIndex; // ハンドル入れたらインデックスになる配列

    //std::vector<Rect> bgRects_;
    bool isUpdate_;
    bool isInMapChipArea_;
    Point selected_;
    int selectedIndex_;
    bool isHold_;
    Point ScrollOffset_; // スクロールオフセット
};

