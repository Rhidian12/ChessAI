#include "ChessScene.h"

#include <Texture/Texture.h>
#include <TextureManager/TextureManager.h>

#include "../Factories/Factories.h"
#include "../Chessboard/Chessboard.h"

ChessScene::ChessScene(const std::string& name)
	: Scene{ name.c_str() }
{}

ChessScene::~ChessScene()
{
	Chessboard::Cleanup();
}

void ChessScene::Start()
{
	using namespace Integrian2D;

	TextureManager::GetInstance()->AddTexture("WhiteTile", new Texture{ "Resources/White_Tile.png" });
	TextureManager::GetInstance()->AddTexture("BlackTile", new Texture{ "Resources/Black_Tile.png" });

	std::vector<GameObject*> tiles{ Factories::CreateChessboard() };

	for (GameObject* const pG : tiles)
		AddGameObject("Tile", pG);

	Chessboard::GetInstance()->SetTiles(tiles);
}
