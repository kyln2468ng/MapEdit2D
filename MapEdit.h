#pragma once
#include "Library/GameObject.h"
class MapEdit :
    public GameObject
{
    int px;
    int py;
public:
    MapEdit();
    ~MapEdit();
    void Update() override;
    void Draw() override;
};

