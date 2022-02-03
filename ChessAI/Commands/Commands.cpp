#include "Commands.h"

#include <Input/InputManager/InputManager.h>
#include <Renderer/Renderer.h>
#include <GameObject/GameObject.h>
#include <Components/TransformComponent/TransformComponent.h>

#include <algorithm>

#include "../TileComponent/TileComponent.h"
#include "../Chessboard/Chessboard.h"
#include "../Piece/Piece.h"

namespace Commands
{
	ClickChessboardCommand::ClickChessboardCommand(Integrian2D::Scene* const pScene)
		: Command{ pScene }
	{
	}

	void ClickChessboardCommand::Execute()
	{
		using namespace Integrian2D;

		Renderer* const pRenderer{ Renderer::GetInstance() };
		Chessboard* const pChessboard{ Chessboard::GetInstance() };
		const Point2f& mousePos{ InputManager::GetInstance()->GetMousePosition() };

		const auto it{ std::find_if(pChessboard->GetTiles().cbegin(), pChessboard->GetTiles().cend(), [&mousePos](const GameObject* const pTile)->bool
			{
				const Point2f& pos{ pTile->pTransform->GetWorldPosition() };
				TileComponent* const pTileComponent{ pTile->GetComponentByType<TileComponent>() };

				if (mousePos.x <= pos.x || mousePos.x >= pos.x + pTileComponent->GetTileWidth())
					return false;

				if (mousePos.y <= pos.y || mousePos.y >= pos.y + pTileComponent->GetTileHeight())
					return false;

				return true;
			}) };

		if (it == pChessboard->GetTiles().cend())
			return;

		const TileComponent* const pTile{ (*it)->GetComponentByType<TileComponent>() };

		/* Safety check */
		if (pTile)
		{
			/* Does the tile have a piece */
			if (const Piece* const pPiece{ pTile->GetPiece() }; pPiece != nullptr)
			{
				auto moves{ pPiece->GetPossibleMoves() };
				for (const TileComponent* const pPossibleMove : moves)
				{
					/* [TODO] Figure out why Circlef is causing linker issues! */
					 //pRenderer->RenderFilledCircle(Circlef{pPossibleMove->GetCenterOfTile(), 5.f}); 
					const Rectf center{ pPossibleMove->GetCenterOfTile().x - 12.5f, pPossibleMove->GetCenterOfTile().y - 12.5f, 25.f, 25.f };
					pRenderer->RenderFilledRectangle(center);
				}
			}
		}
	}
}