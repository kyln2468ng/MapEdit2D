#pragma once
#include "Library//GameObject.h"
#include <vector>
#include "MapChip.h"

class Stage :
    public GameObject
{
    //int *hImage; // �w�i�摜�̃n���h���̔z��т̃|�C���^�i�z�񎩑́j
    std::vector<int> hImage; // �w�i�摜�̃n���h��
    MapChip* mapChip_;

public:
    Stage();
    ~Stage();
    void Update() override;
    void Draw() override;

};

