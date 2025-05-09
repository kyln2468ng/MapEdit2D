#include "MapEdit.h"
#include "Source/Screen.h"

MapEdit::MapEdit()
	:px(16), py(12)
{
}

MapEdit::~MapEdit()
{
}

void MapEdit::Update()
{
}

void MapEdit::Draw()
{
	for (int i = 0;i < px;i++)
	{
		for (int j = 0;j < py;j++)
		{
			DrawBox()
		}
	}
}
