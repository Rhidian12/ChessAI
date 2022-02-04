#include "States.h"

#include <AI/Blackboard/Blackboard.h>
#include <Input/InputManager/InputManager.h>
#include <Renderer/Renderer.h>
#include <Components/TransformComponent/TransformComponent.h>
#include <GameObject/GameObject.h>

#include "../TileComponent/TileComponent.h"
#include "../Piece/Piece.h"

namespace States
{
	Integrian2D::BehaviourState NoUserInput(Integrian2D::Blackboard* const)
	{
		return Integrian2D::BehaviourState::Success;
	}

	Integrian2D::BehaviourState UserRightClick(Integrian2D::Blackboard* const pBlackboard)
	{
		using namespace Integrian2D;

		std::vector<GameObject*>* pTiles{ pBlackboard->GetData<std::vector<GameObject*>*>("Tiles") };
		const Point2f& mousePos{ pBlackboard->GetData<Point2f>("RMBMousePosition") };

		Renderer* const pRenderer{ Renderer::GetInstance() };

		const auto it{ std::find_if(pTiles->cbegin(), pTiles->cend(), [&mousePos](const GameObject* const pTile)->bool
			{
				const Point2f& pos{ pTile->pTransform->GetWorldPosition() };
				TileComponent* const pTileComponent{ pTile->GetComponentByType<TileComponent>() };

				if (mousePos.x <= pos.x || mousePos.x >= pos.x + pTileComponent->GetTileWidth())
					return false;

				if (mousePos.y <= pos.y || mousePos.y >= pos.y + pTileComponent->GetTileHeight())
					return false;

				return true;
			}) };

		if (it == pTiles->cend())
			return BehaviourState::Success;

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

		return BehaviourState::Success;
	}

	Integrian2D::BehaviourState SelectPiece(Integrian2D::Blackboard* const pBlackboard)
	{

	}
}

namespace Transitions
{
	bool HasUserRightClicked(Integrian2D::Blackboard* const pBlackboard)
	{
		if (pBlackboard->GetData<bool>("HasUserRightClicked"))
		{
			pBlackboard->ChangeData("HasUserRightClicked", false);
			pBlackboard->ChangeData("RMBMousePosition", Integrian2D::InputManager::GetInstance()->GetMousePosition());

			return true;
		}
		else
		{
			return false;
		}
	}

	bool HasUserLeftClicked(Integrian2D::Blackboard* const pBlackboard)
	{
		if (pBlackboard->GetData<bool>("HasUserLeftClicked"))
		{
			pBlackboard->ChangeData("HasUserLeftClicked", false);
			pBlackboard->ChangeData("LMBMousePosition", Integrian2D::InputManager::GetInstance()->GetMousePosition());

			return true;
		}
		else
		{
			return false;
		}
	}
}