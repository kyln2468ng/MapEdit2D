#pragma once
#include "Library//GameObject.h"
#include <vector>
#include "MapChip.h"
#include "MapEdit.h"

class Stage :
    public GameObject
{
public:
    Stage();
    ~Stage();
    void Update() override;
    void Draw() override;
    bool RightMouseCheck();
private:
    //int *hImage; // 背景画像のハンドルの配列毛のポインタ（配列自体）
    //std::vector<int> hImage; // 背景画像のハンドル
    MapChip* mapChip_;
    MapEdit* mapEdit_;
  /*  bool isMouseDoen_;
    bool isOldMouseDown_;
    bool isDragging_;*/
};

