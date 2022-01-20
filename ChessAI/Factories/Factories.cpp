#include "Factories.h"

#include <GameObject/GameObject.h>
#include <Core/Core.h>
#include <Components/TextureComponent/TextureComponent.h>
#include <TextureManager/TextureManager.h>
#include <Components/TransformComponent/TransformComponent.h>

#include "../TileComponent/TileComponent.h"
#include "../Piece/Pawn/Pawn.h"
#include "../Piece/Rook/Rook.h"
#include "../Piece/Bishop/Bishop.h"
#include "../Piece/Queen/Queen.h"

namespace Factories
{
	std::vector<Integrian2D::GameObject*> CreateChessboard() noexcept
	{
		using namespace Integrian2D;

		const TextureManager* const pTextureManager{ TextureManager::GetInstance() };

		/* Chessboard has 8x8 tiles */

		const Point2f windowDimensions{ static_cast<float>(Core::GetInstance()->GetWindowWidth()), static_cast<float>(Core::GetInstance()->GetWindowHeight()) };

		const Point2f tileDimensions{ windowDimensions.x / 8.f, windowDimensions.y / 8.f };

		std::vector<GameObject*> tiles{};

		int counter{};
		for (int y{}; y < 8; ++y)
		{
			for (int x{}; x < 8; ++x)
			{
				GameObject* pTile{ new GameObject{} };

				if (counter++ % 2 == 0)
					pTile->AddComponent(new TileComponent{ pTile, tileDimensions.x, tileDimensions.y, pTextureManager->GetTexture("WhiteTile") });
				else
					pTile->AddComponent(new TileComponent{ pTile, tileDimensions.x, tileDimensions.y, pTextureManager->GetTexture("BlackTile") });

				pTile->pTransform->SetPosition(Point2f{ x * tileDimensions.x, y * tileDimensions.y });

				tiles.push_back(pTile);
			}
			--counter;
		}

#pragma region Pawns
		{
			/* Add white pawns */
			Texture* const pWhitePawn{ pTextureManager->GetTexture("WhitePawn") };
			for (int i{ 8 }; i < 16; ++i)
				tiles[i]->AddComponent(new Pawn{ tiles[i], pWhitePawn });
		}

		{
			/* Add black pawns */
			Texture* const pBlackPawn{ pTextureManager->GetTexture("BlackPawn") };
			for (int i{ 48 }; i < 56; ++i)
				tiles[i]->AddComponent(new Pawn{ tiles[i], pBlackPawn });
		}
#pragma endregion

#pragma region Rooks
		{
			/* Add White Rooks */
			Texture* const pWhiteRook{ pTextureManager->GetTexture("WhiteRook") };
			tiles[0]->AddComponent(new Rook{ tiles[0], pWhiteRook });
			tiles[7]->AddComponent(new Rook{ tiles[7], pWhiteRook });
		}

		{
			/* Add Black Rooks */
			Texture* const pBlackRook{ pTextureManager->GetTexture("BlackRook") };
			tiles[56]->AddComponent(new Rook{ tiles[56], pBlackRook });
			tiles[63]->AddComponent(new Rook{ tiles[63], pBlackRook });
		}
#pragma endregion

#pragma region Bishops
		{
			/* Add White Bishops */
			Texture* const pWhiteBishop{ pTextureManager->GetTexture("WhiteBishop") };
			tiles[2]->AddComponent(new Bishop{ tiles[2], pWhiteBishop });
			tiles[5]->AddComponent(new Bishop{ tiles[5], pWhiteBishop });
		}

		{
			/* Add Black Bishops */
			Texture* const pBlackBishop{ pTextureManager->GetTexture("BlackBishop") };
			tiles[58]->AddComponent(new Rook{ tiles[58], pBlackBishop });
			tiles[61]->AddComponent(new Rook{ tiles[61], pBlackBishop });
		}
#pragma endregion

#pragma region Queens
		{
			/* Add White Queen */
			Texture* const pWhiteQueen{ pTextureManager->GetTexture("WhiteQueen") };
			tiles[4]->AddComponent(new Queen{ tiles[4], pWhiteQueen });
		}

		{
			/* Add Black Queen */
			Texture* const pBlackQueen{ pTextureManager->GetTexture("BlackQueen") };
			tiles[60]->AddComponent(new Queen{ tiles[60], pBlackQueen });
		}
#pragma endregion

		return tiles;
	}
}