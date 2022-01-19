#include "Pawn.h"

#include "../../Chessboard/Chessboard.h"
#include "../../TileComponent/TileComponent.h"

#include <GameObject/GameObject.h>
#include <Components/TransformComponent/TransformComponent.h>

Pawn::Pawn(Integrian2D::GameObject* const pOwner)
	: Piece{ pOwner, TypeOfPiece::Pawn }
	, m_HasMoved{}
{
}

Integrian2D::Component* Pawn::Clone(Integrian2D::GameObject* pOwner) noexcept
{
	Pawn* pPawn{ new Pawn{ pOwner } };
	pPawn->m_HasMoved = m_HasMoved;

	return pPawn;
}

void Pawn::Move(TileComponent* const pDestinationTile) noexcept
{
	/* Remove the piece from the current tile */
	Chessboard::GetInstance()->GetTileComponent(m_pOwner->pTransform->GetWorldPosition())->SetPiece(nullptr);

	/* Set the piece to our destination tile */
	pDestinationTile->SetPiece(this);

	/* Set this piece's position to the center of the destination tile */
	m_pOwner->pTransform->SetPosition(pDestinationTile->GetCenterOfTile());
}

std::vector<TileComponent*> Pawn::GetPossibleMoves() const noexcept
{
	std::vector<TileComponent*> possibleMoves{};
	const Chessboard* const pChessboard{ Chessboard::GetInstance() };

	const int currentTileIndex{ pChessboard->GetTileIndex(m_pOwner) };

	/* moving a row up is doing currentTileIndex + 8 */
	/* First check the tile in front of the pawn */

	TileComponent* const pFirstTile{ pChessboard->GetTileComponent(currentTileIndex + 8) };

	/* If there is no piece on the tile, we can move on it */
	if (!pFirstTile->GetPiece())
	{
		possibleMoves.push_back(pFirstTile);

		/* If we haven't moved the pawn yet, check if we can move another tile */
		if (!m_HasMoved)
		{
			TileComponent* const pSecondTile{ pChessboard->GetTileComponent(currentTileIndex + 16) };

			if (!pSecondTile)
				possibleMoves.push_back(pSecondTile);
		}
	}

	return possibleMoves;
}