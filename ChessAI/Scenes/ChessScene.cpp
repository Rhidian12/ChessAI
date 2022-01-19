#include "ChessScene.h"

#include <Texture/Texture.h>
#include <TextureManager/TextureManager.h>

#include "../Factories/Factories.h"

ChessScene::ChessScene(const std::string& name)
	: Scene{ name.c_str() }
{}

void ChessScene::Start()
{
	using namespace Integrian2D;

	TextureManager::GetInstance()->AddTexture("WhiteTile", new Texture{ "Resources/White_Tile.png" });
	TextureManager::GetInstance()->AddTexture("BlackTile", new Texture{ "Resources/Black_Tile.png" });

	for (GameObject* const pG : Factories::CreateChessboard())
		AddGameObject("Tile", pG);
}
