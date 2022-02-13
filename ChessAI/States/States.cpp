#include "States.h"

#include <AI/Blackboard/Blackboard.h>
#include <Input/InputManager/InputManager.h>
#include <Renderer/Renderer.h>
#include <Components/TransformComponent/TransformComponent.h>
#include <GameObject/GameObject.h>
#include <EventQueue/EventQueue.h>

#include "../TileComponent/TileComponent.h"
#include "../Piece/Piece.h"
#include "../Chessboard/Chessboard.h"
#include "../Piece/Pawn/Pawn.h"

#include <algorithm>

namespace HelperFunctions
{
	void TakePiece(TileComponent* const pClickedTile, Piece* const pSelectedPiece)
	{
		using namespace Integrian2D;

		/* Safety check */
		if (pClickedTile)
		{
			/* Check if the clicked tile is present in the selected piece's potential moves */
			const std::vector<TileComponent*> potentialMoves{ pSelectedPiece->GetPossibleMoves() };

			auto isMoveValid{ std::find(potentialMoves.cbegin(), potentialMoves.cend(), pClickedTile) };

			if (isMoveValid != potentialMoves.cend())
			{
				Chessboard* const pChessboard{ Chessboard::GetInstance() };

				/* cache this in case it's a pawn */
				const int originalTileIndex{ pChessboard->GetTileIndex(pSelectedPiece->GetOwner()->GetComponentByType<TileComponent>()) };

				switch (pSelectedPiece->GetTypeOfPiece())
				{
				case TypeOfPiece::Pawn:
					/* if the piece is a pawn, check for a normal attack, en passant or whether we moved twice */
				{
					const int clickedTileIndex{ pChessboard->GetTileIndex(pClickedTile) };
					const int sign{ pSelectedPiece->GetColourOfPiece() == PieceColour::White ? 1 : -1 };
					constexpr int rowMovement{ 8 };

					/* first check for a normal attack */
					if (Piece* const _pPiece{ pClickedTile->GetPiece() }; _pPiece != nullptr)
					{
						EventQueue::GetInstance()->QueueEvent("DeletePiece", _pPiece);
					}
					/* secondly check if we just moved twice */
					else if (abs(clickedTileIndex - originalTileIndex) == (rowMovement * 2))
					{
						static_cast<Pawn*>(pSelectedPiece)->SetMovedDouble(true);
					}
					/* else check if the move we're doing is en passant */
					else
					{
						/* get the tile behind our pawn */
						TileComponent* const pTileBehindPawn{ pChessboard->GetTileComponent(clickedTileIndex + (rowMovement * (-sign))) };

						if (Piece* const pPiece{ pTileBehindPawn->GetPiece() }; pPiece != nullptr)
						{
							/* is the piece behind our pawn is a pawn as well */
							if (pPiece->GetTypeOfPiece() == TypeOfPiece::Pawn)
							{
								/* check if it just moved double */
								if (static_cast<Pawn*>(pPiece)->GetMovedDoubleLastTurn())
								{
									EventQueue::GetInstance()->QueueEvent("DeletePiece", pPiece);
								}
							}
						}
					}
				}
				break;
				case TypeOfPiece::Bishop:
				case TypeOfPiece::Knight:
				case TypeOfPiece::Rook:
				case TypeOfPiece::Queen:
				case TypeOfPiece::King:
					if (Piece* const pPiece{ pClickedTile->GetPiece() }; pPiece != nullptr)
						EventQueue::GetInstance()->QueueEvent("DeletePiece", pPiece);
					break;
				}
			}
		}
	}

	bool IsMoveResultingInCheck(Integrian2D::Blackboard* const pBlackboard)
	{
		using namespace Integrian2D;

		const PieceColour currentColour{ *pBlackboard->GetData<PieceColour*>("CurrentTurn") };
		const std::vector<Piece*>* pPieces{ pBlackboard->GetData<std::vector<Piece*>*>("Pieces") };
		const std::vector<GameObject*>* pTiles{ pBlackboard->GetData<std::vector<GameObject*>*>("Tiles") };

		const TileComponent* const pKingTile{ (*std::find_if(pTiles->cbegin(), pTiles->cend(),
			[currentColour](const GameObject* const pTile)->bool
			{
				const Piece* const pPiece{ pTile->GetComponentByType<TileComponent>()->GetPiece() };
				if (pPiece)
					return pPiece->GetTypeOfPiece() == TypeOfPiece::King && pPiece->GetColourOfPiece() == currentColour;
				else
					return false;
			}))->GetComponentByType<TileComponent>() };

		// const Piece* const pKing{ pKingTile->GetPiece() };

		for (Piece* const pEnemyPiece : *pPieces)
		{
			/* we need to check the other pieces to see if we move that we're not going in check */
			if (pEnemyPiece->GetColourOfPiece() != currentColour)
			{
				const std::vector<TileComponent*> possibleMoves{ pEnemyPiece->GetPossibleMoves() };

				/* is the king is POSSIBLY being threatened */
				if (std::find(possibleMoves.cbegin(), possibleMoves.cend(), pKingTile) != possibleMoves.cend())
				{
					return true;
				}
			}
		}

		return false;
	}
}

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
		PieceColour* pPieceColour{ pBlackboard->GetData<PieceColour*>("CurrentTurn") };

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
			return BehaviourState::Failure;

		TileComponent* const pOriginalTile{ (*it)->GetComponentByType<TileComponent>() };

		/* Safety check */
		if (pOriginalTile)
		{
			/* Does the tile have a piece */
			if (Piece* const pPiece{ pOriginalTile->GetPiece() }; pPiece != nullptr)
			{
				/* Is the piece of the correct colour */
				if (pPiece->GetColourOfPiece() == *pPieceColour)
				{
					auto moves{ pPiece->GetPossibleMoves() };

					/* safety check */
					if (!moves.empty())
					{
						/* do a ghost move */
						pPiece->Move(moves[0], true);

						/* Check if our move would result in a check, ergo is the move valid */
						const bool wouldMoveResultInCheck{ HelperFunctions::IsMoveResultingInCheck(pBlackboard) };

						/* undo the the ghost move */
						pPiece->Move(pOriginalTile, true);

						/* if the move would result in check, stop moving */
						if (wouldMoveResultInCheck)
							return BehaviourState::Failure;

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

		return BehaviourState::Success;
	}

	Integrian2D::BehaviourState SelectPiece(Integrian2D::Blackboard* const pBlackboard)
	{
		using namespace Integrian2D;

		std::vector<GameObject*>* pTiles{ pBlackboard->GetData<std::vector<GameObject*>*>("Tiles") };
		const Point2f& mousePos{ pBlackboard->GetData<Point2f>("LMBMousePosition") };
		PieceColour* pPieceColour{ pBlackboard->GetData<PieceColour*>("CurrentTurn") };

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
			return BehaviourState::Failure;

		const TileComponent* const pTile{ (*it)->GetComponentByType<TileComponent>() };

		/* Safety check */
		if (pTile)
		{
			/* Does the tile have a piece */
			if (const Piece* const pPiece{ pTile->GetPiece() }; pPiece != nullptr)
			{
				/* Is it a piece of the correct colour */
				if (pPiece->GetColourOfPiece() == *pPieceColour)
				{
					pBlackboard->ChangeData("SelectedPiece", pPiece);
					pBlackboard->ChangeData("OriginalTile", pTile);

					return BehaviourState::Success;
				}
				else
					return BehaviourState::Failure;
			}
			else
				return BehaviourState::Failure;
		}

		return BehaviourState::Failure;
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
			return BehaviourState::Failure;

		TileComponent* const pClickedTile{ (*it)->GetComponentByType<TileComponent>() };

		/* Safety check */
		if (pClickedTile)
		{
			/* Check if the clicked tile is present in the selected piece's potential moves */
			const std::vector<TileComponent*> potentialMoves{ pSelectedPiece->GetPossibleMoves() };

			auto isMoveValid{ std::find(potentialMoves.cbegin(), potentialMoves.cend(), pClickedTile) };

			if (isMoveValid != potentialMoves.cend())
			{
				/* cache our original tile */
				TileComponent* const pOriginalTile{ pSelectedPiece->GetOwner()->GetComponentByType<TileComponent>() };

				/* do a GHOST move, we already move the piece, but this will be nullified */
				pSelectedPiece->Move(pClickedTile, true);

				/* Check if our move would result in a check, ergo is the move valid */
				const bool wouldMoveResultInCheck{ HelperFunctions::IsMoveResultingInCheck(pBlackboard) };

				/* undo the GHOST move */
				pSelectedPiece->Move(pOriginalTile, true);

				/* if the move would result in check, stop moving */
				if (wouldMoveResultInCheck)
				{
					pBlackboard->ChangeData("SelectedPiece", nullptr);

					return BehaviourState::Failure;
				}

				/* Take a piece if possible */
				HelperFunctions::TakePiece(pClickedTile, pSelectedPiece);

				/* ACTUALLY Move the piece */
				pSelectedPiece->Move(pClickedTile, false);

				pBlackboard->ChangeData("SelectedPiece", nullptr);
				pBlackboard->ChangeData("WasPieceMoved", true);

				Chessboard::GetInstance()->EndTurn();

				return BehaviourState::Success;
			}
			else
			{
				/* The move is invalid */
				return BehaviourState::Failure;
			}
		}

		return BehaviourState::Failure;
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

	bool WasPieceMoved(Integrian2D::Blackboard* const pBlackboard)
	{
		if (pBlackboard->GetData<bool>("WasPieceMoved"))
		{
			pBlackboard->ChangeData("WasPieceMoved", false);

			return true;
		}
		else
			return false;
	}

	bool WasEscapePressed(Integrian2D::Blackboard* const pBlackboard)
	{
		if (pBlackboard->GetData<bool>("WasEscapePressed"))
		{
			pBlackboard->ChangeData("WasEscapePressed", false);

			return true;
		}
		else
			return false;
	}
}