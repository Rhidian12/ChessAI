#include "Pawn.h"

#include "../../Chessboard/Chessboard.h"
#include "../../TileComponent/TileComponent.h"

#include <GameObject/GameObject.h>
#include <Components/TransformComponent/TransformComponent.h>
#include <Utils/Utils.h>

Pawn::Pawn(Integrian2D::GameObject* const pOwner, Integrian2D::Texture* const pTexture)
	: Piece{ pOwner, TypeOfPiece::Pawn, pTexture }
	, m_HasMoved{}
	, m_MovedDouble{}
{
}

Integrian2D::Component* Pawn::Clone(Integrian2D::GameObject* pOwner) noexcept
{
	Pawn* pPawn{ new Pawn{ pOwner, m_pTexture } };
	pPawn->m_HasMoved = m_HasMoved;
	pPawn->m_MovedDouble = m_MovedDouble;

	return pPawn;
}

void Pawn::Move(TileComponent* const pDestinationTile) noexcept
{
	Piece::Move(pDestinationTile);

	/* notify when the pawn gets moved */
	m_HasMoved = true;
}

std::vector<TileComponent*> Pawn::GetPossibleMoves() const noexcept
{
	std::vector<TileComponent*> possibleMoves{};
	const Chessboard* const pChessboard{ Chessboard::GetInstance() };

	const int currentTileIndex{ pChessboard->GetTileIndex(m_pOwner) };

	/* moving a row up is doing currentTileIndex + 8 */
	/* First check the tile in front of the pawn */

	const int sign{ m_PieceColour == PieceColour::White ? 1 : -1 };
	constexpr int rowMovement{ 8 };

	constexpr int amountOfTilesToCheck{ 2 };
	constexpr int possibleAttackMoves[amountOfTilesToCheck]{ -1, 1 };

	TileComponent* const pFirstTile{ pChessboard->GetTileComponent(currentTileIndex + (rowMovement * sign)) };

	/* If there is no piece on the tile, we can move on it */
	if (!pFirstTile->GetPiece())
	{
		possibleMoves.push_back(pFirstTile);

		/* If we haven't moved the pawn yet, check if we can move another tile */
		if (!m_HasMoved)
		{
			TileComponent* const pSecondTile{ pChessboard->GetTileComponent(currentTileIndex + (rowMovement * 2 * sign)) };

			if (!pSecondTile->GetPiece())
				possibleMoves.push_back(pSecondTile);
		}
	}

	/* Check if we can take pieces */
	for (int i{}; i < amountOfTilesToCheck; ++i)
	{
		const int nextIndex{ currentTileIndex + (rowMovement * sign + possibleAttackMoves[i]) };

		/* safety check */
		if (Integrian2D::Utils::IsInRange(nextIndex, 0, 63))
		{
			TileComponent* const pTile{ pChessboard->GetTileComponent(nextIndex) };

			/* safety check */
			if (pTile)
				/* if the tile has a piece */
				if (Piece* const pPiece{ pTile->GetPiece() }; pPiece != nullptr)
					/* if the piece does not have the same colour of our piece */
					if (pPiece->GetColourOfPiece() != m_PieceColour)
						possibleMoves.push_back(pTile);
		}
	}

	/* check for en passant */
	for (int i{}; i < amountOfTilesToCheck; ++i)
	{
		const int nextIndex{ currentTileIndex + possibleAttackMoves[i] };

		/* safety check */
		if (Integrian2D::Utils::IsInRange(nextIndex, 0, 63))
		{
			const int row{ pChessboard->GetRowNumber(currentTileIndex) };

			/* make sure we're checking a pawn that's next to our current pawn */
			if (pChessboard->GetRowNumber(nextIndex) == row)
			{
				TileComponent* const pTile{ pChessboard->GetTileComponent(nextIndex) };

				/* safety check */
				if (pTile)
				{
					if (Piece* const pPiece{ pTile->GetPiece() }; pPiece != nullptr)
					{
						/* we only care about other pawns */
						if (pPiece->GetTypeOfPiece() == TypeOfPiece::Pawn)
						{
							/* if the pawn next to us just moved double, we can do en passant */
							if (static_cast<Pawn*>(pPiece)->GetMovedDoubleLastTurn())
							{
								possibleMoves.push_back(pChessboard->GetTileComponent(nextIndex + (sign * rowMovement)));
								break; /* we can only do en passant on one pawn */
							}
						}
					}
				}
			}
		}
	}

	return possibleMoves;
}

void Pawn::SetMovedDouble(bool value) noexcept
{
	m_MovedDouble = value;
}

bool Pawn::GetMovedDoubleLastTurn() const noexcept
{
	return m_MovedDouble;
}
