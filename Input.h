#pragma once


namespace Input {
	//キーボード取得関連
	void KeyStateUpdate(); // キーの状態を更新
	bool IsKeyUp(int keyCode); // キーが離された瞬間
	bool IsKeyDown(int keyCode); // キーが押された瞬間
	int IsKeepKeyDown(int keyCode); // キーが押されている間

	bool IsMouseDown();			   // マウスが押された瞬間
	bool IsMouseUP();			   // マウスが離された瞬間
	bool IsMouseKeep();			   // マウスが押されている間
	bool IsButtonDown(int button); // ボタンが押された瞬間
	bool IsButtonUP(int button);   // ボタンが離れた瞬間
	bool IsButtonKeep(int button); // ボタンが押されている間
}

//MOUSE_INPUT_LEFT  => 0x0001
//MOUSE_INPUT_MIDLE => 0x0004
//MOUSE_INPUT_RIGHT => 0x0002

// 各ビットをtrue falseのフラグとして使う→ビットフラグ