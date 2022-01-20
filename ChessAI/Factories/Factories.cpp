#include "Factories.h"

#include <GameObject/GameObject.h>
#include <Core/Core.h>
#include <Components/TextureComponent/TextureComponent.h>
#include <TextureManager/TextureManager.h>
#include <Components/TransformComponent/TransformComponent.h>

#include "../TileComponent/TileComponent.h"
#include "../Piece/Pawn/Pawn.h"

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

		return tiles;
	}
}