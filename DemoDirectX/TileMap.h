#pragma once
#include"Sprites.h"
#include"Textures.h"
#include"Utils.h"
#include <iostream>
#include <fstream>
#include<string>
#include <sstream>
#include"Game.h"
#define SCENE_1 2000
#define SCENE_2 3000
#define SCENE_1_ROW 10
#define SCENE_1_COL 48
#define SCENE_1_ROW_READ 4
#define SCENE_1_COL_READ 17
#define SCENE_2_ROW 12
#define SCENE_2_COL 17
#define SCENE_2_ROW_READ 4
#define SCENE_2_COL_READ 7

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

#define MAX_SCENE_LINE 1024


class TileMap
{
	CSprites * sprites; //= CSprites::GetInstance();
	LPCWSTR mapFilePath;
	//LPCWSTR mappic;
	int num_row, num_col;
	int tile_width, tile_height;
	int id;

	vector<vector<LPSPRITE>> tilemap;
	
public:
	TileMap();
	~TileMap();
	int getwidthmap() { return num_col*tile_width; }
	int getid() { return id; }
	void Load();
	void LoadMap(int id, LPCWSTR file_pic, LPCWSTR filePath_data);
	void Draw();
};


