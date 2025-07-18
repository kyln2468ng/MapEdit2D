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
    int GetHandle(int index) { return hImage_[index]; } //�n���h�����擾����
    bool isHold();
    int GetHoldImage();
    int GetChipIndex(int handle);
    Point GetViewOrigin() const; // �}�b�v�`�b�v�̕\���ʒu���擾�����Ԃ�
    bool IsInChipArea(const Point& mouse) const; // const &~ �l�ς��Ȃ�
    Point ScreenToChipIndex(const Point& mouse) const;
private:
    MapChipConfig cfg_; // �}�b�v�`�b�v�̐ݒ��ێ�����
    std::vector<int> hImage_;
    std::map<int, int> HandlToIndex; // �n���h�����ꂽ��C���f�b�N�X�ɂȂ�z��

    //std::vector<Rect> bgRects_;
    bool isUpdate_;
    bool isInMapChipArea_;
    Point selected_;
    int selectedIndex_;
    bool isHold_;
    Point ScrollOffset_; // �X�N���[���I�t�Z�b�g
};

