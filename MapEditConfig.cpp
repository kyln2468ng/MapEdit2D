#include "MapEditConfig.h"
#include <Windows.h>
#include<string>

const MapEditConfig LoadMapEditConfig(const std::string& iniPath)
{
	MapEditConfig efg;
	efg.MAP_IMAGE_SIZE	= GetPrivateProfileInt("MapEdit", "MAP_SIZE", 255,iniPath.c_str());
	efg.MAP_WIDTH		= GetPrivateProfileInt("MapEdit", "MAP_WIDTH", 255,iniPath.c_str());
	efg.MAP_HEIGHT		= GetPrivateProfileInt("MapEdit", "MAP_HEIGHT", 255,iniPath.c_str());
	efg.LEFT_MARGIN		= GetPrivateProfileInt("MapEdit", "LEFT_MARGIN", 255,iniPath.c_str());
	efg.TOP_MARGIN		= GetPrivateProfileInt("MapEdit", "TOP_MARGIN", 255,iniPath.c_str());

	return efg;
}

const MapEditConfig& GetMapEditConfig()
{
	static MapEditConfig config = LoadMapEditConfig("./mySetup.ini");
	return config;
}
