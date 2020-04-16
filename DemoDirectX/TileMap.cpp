#include "TileMap.h"

TileMap::TileMap()
{
	this->tile_width = TILE_WIDTH;
	this->tile_height = TILE_HEIGHT;
}
void TileMap::Load()
{
	DebugOut(L"[INFO] Start loading map resources from : %s \n", mapFilePath);

	ifstream f;
	f.open(mapFilePath);

	if (f.fail())
	{
		DebugOut(L"[ERROR] TileMap::Load_MapData failed: ID=%d", id);
		f.close();
		return;
	}



	//vector<LPSPRITE> spriteline;
	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);
		vector<LPSPRITE> spriteline;
		vector<string> tokens = splitmap(line);
		for (int i = 0; i < tokens.size(); i++)
		{
			int idsprite = id + atoi(tokens[i].c_str());
			spriteline.push_back(sprites->Get(idsprite));


		}
		tilemap.push_back(spriteline);
	}
	f.close();
	

	DebugOut(L"[INFO] Done loading map resources %s\n", mapFilePath);
}

void TileMap::LoadMap(int id, LPCWSTR file_pic, LPCWSTR filePath_data)
{
	CTextures * texture = CTextures::GetInstance();
	//
	this->id = id;
	this->mappic = file_pic;
	this->mapFilePath = filePath_data;

	texture->Add(id, mappic, D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texTileMap = texture->Get(id);
	int num_row_read, num_col_read;
	switch (id)
	{
	case SCENE_1:
		num_row = SCENE_1_ROW;//10;//6;
		num_col = SCENE_1_COL;//24;
		num_row_read = SCENE_1_ROW_READ;//4;
		num_col_read = SCENE_1_COL_READ;//17; //8;	
		break;
	default:
		break;
	}

	int idsprite = 1;
	for (UINT i = 0; i < num_row_read; i++)
	{
		for (UINT j = 0; j < num_col_read; j++)
		{
			int id_SPRITE = id + idsprite;
			sprites->Add(id_SPRITE, tile_width * j, tile_height * i, tile_width * (j + 1), tile_height * (i + 1), texTileMap);
			idsprite = idsprite + 1;
		}
	}

	Load();
}

void TileMap::Draw()
{

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


