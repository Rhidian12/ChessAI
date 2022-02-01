#include "ChessScene.h"

#include <Texture/Texture.h>
#include <TextureManager/TextureManager.h>
#include <Input/InputManager/InputManager.h>

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

	TextureManager* const pTextureManager{ TextureManager::GetInstance() };

	pTextureManager->AddTexture("WhiteTile", new Texture{ "Resources/White_Tile.png" });
	pTextureManager->AddTexture("BlackTile", new Texture{ "Resources/Black_Tile.png" });
	pTextureManager->AddTexture("WhitePawn", new Texture{ "Resources/White_Pawn.png" });
	pTextureManager->AddTexture("BlackPawn", new Texture{ "Resources/Black_Pawn.png" });
	pTextureManager->AddTexture("WhiteRook", new Texture{ "Resources/White_Rook.png" });
	pTextureManager->AddTexture("BlackRook", new Texture{ "Resources/Black_Rook.png" });
	pTextureManager->AddTexture("WhiteBishop", new Texture{ "Resources/White_Bishop.png" });
	pTextureManager->AddTexture("BlackBishop", new Texture{ "Resources/Black_Bishop.png" });
	pTextureManager->AddTexture("WhiteQueen", new Texture{ "Resources/White_Queen.png" });
	pTextureManager->AddTexture("BlackQueen", new Texture{ "Resources/Black_Queen.png" });
	pTextureManager->AddTexture("WhiteKing", new Texture{ "Resources/White_King.png" });
	pTextureManager->AddTexture("BlackKing", new Texture{ "Resources/Black_King.png" });
	pTextureManager->AddTexture("WhiteKnight", new Texture{ "Resources/White_Knight.png" });
	pTextureManager->AddTexture("BlackKnight", new Texture{ "Resources/Black_Knight.png" });

	std::vector<GameObject*> tiles{ Factories::CreateChessboard() };

	for (GameObject* const pG : tiles)
		AddGameObject("Tile", pG);

	Chessboard::GetInstance()->SetTiles(tiles);
}

void ChessScene::Update()
{
	using namespace Integrian2D;

	Chessboard::GetInstance()->Update();
}