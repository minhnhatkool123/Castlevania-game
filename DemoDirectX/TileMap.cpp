#include "TileMap.h"

TileMap::TileMap(int ID, LPCWSTR filePath_tex, LPCWSTR filePath_data, int tile_width , int tile_height)
{
	id = ID;

	this->mappic = filePath_tex;
	this->mapFilePath = filePath_data;


	this->tile_width = tile_width;
	this->tile_height = tile_height;

	
	LoadMap();
	Load();
}
void TileMap::Load()
{
	DebugOut(L"[INFO] Start loading map resources from : %s \n", mapFilePath);

	ifstream fs(mapFilePath, ios::in);

	if (fs.fail())
	{
		DebugOut(L"[ERROR] TileMap::Load_MapData failed: ID=%d", id);
		fs.close();
		return;
	}

	string line;

	while (!fs.eof())
	{
		getline(fs, line);

		// Lưu sprite tile vào vector tilemap
		vector<LPSPRITE> spriteline;
		stringstream ss(line);
		int n;

		while (ss >> n)
		{
			int idTile = id + n;
			spriteline.push_back(sprites->Get(idTile));
		}

		tilemap.push_back(spriteline);
	}

	fs.close();

	DebugOut(L"[INFO] Done loading map resources %s\n", mapFilePath);
}

void TileMap::LoadMap()
{
	CTextures * texture = CTextures::GetInstance();
	/*if (id == 1000)
		texture->Add(id, L"TileMap\\TilesetStage1.png", D3DCOLOR_XRGB(255, 0, 255));*/
	texture->Add(id, mappic, D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texTileMap = texture->Get(id);
	int num_row_read, num_col_read;
	switch (id)
	{
	case 2000:
		num_row = 10;//6;
		num_col = 48;//24;
		num_row_read = 4;
		num_col_read = 17; //8;
		break;
	default:
		break;
	}

	int id_sprite = 1;
	for (UINT i = 0; i < num_row_read; i++)
	{
		for (UINT j = 0; j < num_col_read; j++)
		{
			//string idTile = "map_" + to_string(ID) + "_tile_" + to_string(id_sprite);
			int id_SPRITE = id + id_sprite;
			sprites->Add(id_SPRITE, tile_width * j, tile_height * i, tile_width * (j + 1), tile_height * (i + 1), texTileMap);
			id_sprite = id_sprite + 1;
		}
	}



	//switch (id)
	//{
	//case 1000:
	//	//mapFilePath = L"TileMap\\TilesetStage1Text.txt";
	//	num_row = 6;
	//	num_col = 24;
	//	tile_height = tile_width = 64;
	//	Load();
	//	break;
	//}
	
}

void TileMap::Draw()
{
	//int rowscreen = SCREEN_HEIGHT / tile_height;

	int firstcol = (int)CGame::GetInstance()->GetCamPosX() / tile_width;
	int lastcol = firstcol + (SCREEN_WIDTH / tile_width) ;

	for (UINT i = 0; i < num_row; i++)
	{
		for (UINT j = firstcol; j <= lastcol; j++)
		{
			float x = tile_width * (j - firstcol) + CGame::GetInstance()->GetCamPosX()- (int)(CGame::GetInstance()->GetCamPosX()) % tile_width;
			float y = tile_height * i + 80;

			tilemap[i][j]->Draw(-1, x, y);
		}
	}


}

TileMap::~TileMap()
{
}


TileMaps * TileMaps::_instance = NULL;

void TileMaps::Add(int ID, LPCWSTR filePath_tex, LPCWSTR filePath_data, int tile_width, int tile_height)
{
	LPTILEMAP tilemap = new TileMap(ID, filePath_tex, filePath_data, tile_width, tile_height);
	tilemaps[ID] = tilemap;
}

TileMaps * TileMaps::GetInstance()
{
	if (_instance == NULL) _instance = new TileMaps();
	return _instance;
}