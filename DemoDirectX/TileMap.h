#pragma once
#include"Sprites.h"
#include"Textures.h"
#include"Utils.h"
#include <iostream>
#include <fstream>
#include<string>
#include <sstream>
#include"Game.h"

class TileMap
{
	CSprites * sprites = CSprites::GetInstance();
	LPCWSTR mapFilePath;
	LPCWSTR mappic;
	//int map_width, map_height;
	int num_row, num_col;
	int tile_width, tile_height;
	int id;

	vector<vector<LPSPRITE>> tilemap;
	
public:
	TileMap(int ID, LPCWSTR filePath_tex, LPCWSTR filePath_data, int tile_width = 32, int tile_height = 32);
	~TileMap();

	void Load();
	void LoadMap();
	void Draw();
};

typedef TileMap *LPTILEMAP;

class TileMaps
{
	static TileMaps * _instance;
	unordered_map<int, LPTILEMAP> tilemaps;

public:
	void Add(int ID, LPCWSTR filePath_tex, LPCWSTR filePath_data, int tile_width = 32, int tile_height = 32);
	LPTILEMAP Get(int ID) { return tilemaps[ID]; }


	static TileMaps * GetInstance();
};
