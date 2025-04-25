#pragma once
#include "Library//GameObject.h"
class Stage :
    public GameObject
{
    int hImage;
    int imageSize;
    int imageElement;
public:
    Stage();
    ~Stage();
    void Update() override;
    void Draw() override;

};

