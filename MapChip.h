#pragma once
#include "Library/GameObject.h"
#include <vector>
#include "globals.h"

class MapChip :
    public GameObject
{
public:
    MapChip();
    ~MapChip();
    void Update() override;
    void Draw() override;
    int GetHandle(int index) { return hImage_[index]; } //ƒnƒ“ƒhƒ‹‚ðŽæ“¾‚·‚é
    bool isHold();
    int GetHoldImage();
private:
    std::vector<int> hImage_;
    std::vector<Rect> bgRects_;
    bool isUpdate_;
    bool isInMapChipArea_;
    Point selected_;
    int selectedIndex_;
    bool isHold_;
};

