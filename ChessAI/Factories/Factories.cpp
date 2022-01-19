#include "Factories.h"

#include <GameObject/GameObject.h>
#include <Core/Core.h>
#include <Components/TextureComponent/TextureComponent.h>
#include <TextureManager/TextureManager.h>
#include <Components/TransformComponent/TransformComponent.h>

#include "../TileComponent/TileComponent.h"

namespace Factories
{
	std::vector<Integrian2D::GameObject*> CreateChessboard() noexcept
	{
		using namespace Integrian2D;

		/* Chessboard has 8x8 tiles */

		const Point2f windowDimensions{ Core::GetInstance()->GetWindowWidth(), Core::GetInstance()->GetWindowHeight() };

		const Point2f tileDimensions{ windowDimensions.x / 8.f, windowDimensions.y / 8.f };

		std::vector<GameObject*> tiles{};

		int counter{};
		for (int x{}; x < 8; ++x)
		{
			for (int y{}; y < 8; ++y)
			{
				GameObject* pTile{ new GameObject{} };

				if (counter % 2 == 0)
					pTile->AddComponent(new TileComponent{ pTile, tileDimensions.x, tileDimensions.y, TextureManager::GetInstance()->GetTexture("WhiteTile") });
				else
					pTile->AddComponent(new TileComponent{ pTile, tileDimensions.x, tileDimensions.y, TextureManager::GetInstance()->GetTexture("BlackTile") });

				pTile->pTransform->SetPosition(Point2f{ x * tileDimensions.x, y * tileDimensions.y });

				tiles.push_back(pTile);
			}
		}

		return tiles;
	}
}