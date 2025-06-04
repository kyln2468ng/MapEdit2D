#pragma once
#include "Library/GameObject.h"
#include <vector>

struct Point
{
    int x;
    int y;
};

struct Rect
{
    int x, y;
    int w, h;
};

class MapChip :
    public GameObject
{
    std::vector<int> hImage_;
    std::vector<Rect> bgRects_;
    bool isUpdate;
    bool isInMapChipArea_;
    Point selected_;
    int selectedIndex_;
public:
    MapChip();
    ~MapChip();
    void Update() override;
    void Draw() override;
};

