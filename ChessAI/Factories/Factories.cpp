#include "Factories.h"

#include <GameObject/GameObject.h>
#include <Core/Core.h>
#include <Components/TextureComponent/TextureComponent.h>
#include <TextureManager/TextureManager.h>

namespace Factories
{
	std::vector<Integrian2D::GameObject*> CreateChessboard() noexcept
	{
		using namespace Integrian2D;

		/* Chessboard has 8x8 tiles */

		const Point2f windowDimensions{ Core::GetInstance()->GetWindowWidth(), Core::GetInstance()->GetWindowHeight() };

		const Point2f tileDimensions{ windowDimensions.x / 8.f, windowDimensions.y / 8.f };

		std::vector<GameObject*> m_Tiles{};

		for (int x{}; x < 8; ++x)
		{
			for (int y{}; y < 8; ++y)
			{
				GameObject* pTile{ new GameObject{} };
			}
		}
	}
}