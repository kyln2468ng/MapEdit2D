#include "MapChipConfig.h"
#include <Windows.h>
#include <string>

MapChipConfig LoadMapChipConfig(const std::string& iniPath)
{
	MapChipConfig cfg;
	cfg.TILE_PIX_SIZE =  GetPrivateProfileInt("MapChip", "TILE_SIZE", 255, iniPath.c_str());
	cfg.TILE_X =		 GetPrivateProfileInt("MapChip", "TILE_X",    255, iniPath.c_str());
	cfg.TILE_Y =		 GetPrivateProfileInt("MapChip", "TILE_Y",    255, iniPath.c_str());
	cfg.MAPCHIP_VIEW_X = GetPrivateProfileInt("MapChip", "VIEW_X",    255, iniPath.c_str());
	cfg.MAPCHIP_VIEW_Y = GetPrivateProfileInt("MapChip", "VIEW_Y",    255, iniPath.c_str());
	cfg.MAPCHIP_WIN_WIDTH = cfg.TILE_PIX_SIZE * cfg.MAPCHIP_VIEW_X;
	cfg.MAPCHIP_WIN_HEIGHT = cfg.TILE_PIX_SIZE * cfg.MAPCHIP_VIEW_Y;
	return cfg;
}

const MapChipConfig& GetMapChipConfig()
{
	static MapChipConfig config = LoadMapChipConfig("./mySetup.ini"); // ˆê‰ñ‚¾‚¯“Ç‚ñ‚Å‚Ë‚Á‚Ä‚â‚Â
	return config;
}