#pragma once
struct MapEditConfig
{
	int MAP_IMAGE_SIZE;
	int MAP_WIDTH;
	int MAP_HEIGHT;
	int LEFT_MARGIN;
	int TOP_MARGIN;
};

const MapEditConfig& GetMapEditConfig();
