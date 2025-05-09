#pragma once
#include "Library/GameObject.h"
#include <vector>

class MapChip :
    public GameObject
{
    std::vector<int> hImage_;
public:
    MapChip();
    ~MapChip();
    void Update() override;
    void Draw() override;
};

