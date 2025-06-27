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
    //int *hImage; // �w�i�摜�̃n���h���̔z��т̃|�C���^�i�z�񎩑́j
    //std::vector<int> hImage; // �w�i�摜�̃n���h��
    MapChip* mapChip_;
    MapEdit* mapEdit_;
  /*  bool isMouseDoen_;
    bool isOldMouseDown_;
    bool isDragging_;*/
};

