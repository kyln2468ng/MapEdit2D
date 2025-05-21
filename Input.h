#pragma once


namespace Input {
	//�L�[�{�[�h�擾�֘A
	void KeyStateUpdate(); // �L�[�̏�Ԃ��X�V
	bool IsKeyUp(int keyCode); // �L�[�������ꂽ�u��
	bool IsKeyDown(int keyCode); // �L�[�������ꂽ�u��
	int IsKeepKeyDown(int keyCode); // �L�[��������Ă����

	bool IsMouseDown();			   // �}�E�X�������ꂽ�u��
	bool IsMouseUP();			   // �}�E�X�������ꂽ�u��
	bool IsMouseKeep();			   // �}�E�X��������Ă����
	bool IsButtonDown(int button); // �{�^���������ꂽ�u��
	bool IsButtonUP(int button);   // �{�^�������ꂽ�u��
	bool IsButtonKeep(int button); // �{�^����������Ă����
}

//MOUSE_INPUT_LEFT  => 0x0001
//MOUSE_INPUT_MIDLE => 0x0004
//MOUSE_INPUT_RIGHT => 0x0002

// �e�r�b�g��true false�̃t���O�Ƃ��Ďg�����r�b�g�t���O