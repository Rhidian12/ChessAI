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
			return BehaviourState::Running;

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
		using namespace Integrian2D;

		std::vector<GameObject*>* pTiles{ pBlackboard->GetData<std::vector<GameObject*>*>("Tiles") };
		const Point2f& mousePos{ pBlackboard->GetData<Point2f>("LMBMousePosition") };

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
			return BehaviourState::Running;

		const TileComponent* const pTile{ (*it)->GetComponentByType<TileComponent>() };

		/* Safety check */
		if (pTile)
		{
			/* Does the tile have a piece */
			if (const Piece* const pPiece{ pTile->GetPiece() }; pPiece != nullptr)
			{
				pBlackboard->ChangeData("SelectedPiece", pPiece);

				return BehaviourState::Success;
			}
			else
				return BehaviourState::Running;
		}

		return BehaviourState::Running;
	}

	Integrian2D::BehaviourState MovePiece(Integrian2D::Blackboard* const pBlackboard)
	{
		using namespace Integrian2D;

		std::vector<GameObject*>* pTiles{ pBlackboard->GetData<std::vector<GameObject*>*>("Tiles") };
		const Point2f& mousePos{ pBlackboard->GetData<Point2f>("LMBMousePosition") };
		Piece* const pSelectedPiece{ pBlackboard->GetData<Piece*>("SelectedPiece") };

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
			return BehaviourState::Running;

		TileComponent* const pClickedTile{ (*it)->GetComponentByType<TileComponent>() };

		/* Safety check */
		if (pClickedTile)
		{
			/* Check if the clicked tile is present in the selected piece's potential moves */
			const std::vector<TileComponent*> potentialMoves{ pSelectedPiece->GetPossibleMoves() };

			auto isMoveValid{ std::find(potentialMoves.cbegin(), potentialMoves.cend(), pClickedTile) };

			if (isMoveValid != potentialMoves.cend())
			{
				/* Move the piece */

				/* First tell the old tile it no longer has the piece */
				pBlackboard->GetData<TileComponent*>("OriginalTile")->SetPiece(nullptr);

				/* Next up, if there is a piece on the clicked tile, take it */
				/* [TODO] Implement this */

				/* Now, move the Selected Piece and set it to a nullptr in the blackboard */
				pClickedTile->SetPiece(pSelectedPiece);
				pBlackboard->ChangeData("SelectedPiece", nullptr);

				return BehaviourState::Success;
			}
			else
			{
				/* The move is invalid */
				return BehaviourState::Running;
			}
		}

		return BehaviourState::Running;
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

	bool HasPieceBeenSelectedAndHasUserLeftClicked(Integrian2D::Blackboard* const pBlackboard)
	{
		return pBlackboard->GetData<Piece*>("SelectedPiece") != nullptr && HasUserLeftClicked(pBlackboard);
	}
}