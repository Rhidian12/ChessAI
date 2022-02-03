#include "Pawn.h"

#include "../../Chessboard/Chessboard.h"
#include "../../TileComponent/TileComponent.h"

#include <GameObject/GameObject.h>
#include <Components/TransformComponent/TransformComponent.h>

Pawn::Pawn(Integrian2D::GameObject* const pOwner, Integrian2D::Texture* const pTexture)
	: Piece{ pOwner, TypeOfPiece::Pawn, pTexture }
	, m_HasMoved{}
{
}

Integrian2D::Component* Pawn::Clone(Integrian2D::GameObject* pOwner) noexcept
{
	Pawn* pPawn{ new Pawn{ pOwner, m_pTexture } };
	pPawn->m_HasMoved = m_HasMoved;

	return pPawn;
}

void Pawn::Move(TileComponent* const pDestinationTile) noexcept
{
	Piece::Move(pDestinationTile);

	m_HasMoved = true;
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
	if (!pFirstTile->GetPiece() || pFirstTile->GetPiece()->GetColourOfPiece() != m_PieceColour)
	{
		possibleMoves.push_back(pFirstTile);

		/* If we haven't moved the pawn yet, check if we can move another tile */
		if (!m_HasMoved)
		{
			TileComponent* const pSecondTile{ pChessboard->GetTileComponent(currentTileIndex + 16) };

			if (!pSecondTile->GetPiece() || pSecondTile->GetPiece()->GetColourOfPiece() != m_PieceColour)
				possibleMoves.push_back(pSecondTile);
		}
	}

	/* [TODO] Should still check to take other pieces + en passant */

	return possibleMoves;
}