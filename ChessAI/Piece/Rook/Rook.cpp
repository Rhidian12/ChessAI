#include "Rook.h"

#include "../../Chessboard/Chessboard.h"
#include "../../TileComponent/TileComponent.h"

Rook::Rook(Integrian2D::GameObject* const pOwner, Integrian2D::Texture* const pTexture)
	: Piece{ pOwner, TypeOfPiece::Rook, pTexture }
{
}

Integrian2D::Component* Rook::Clone(Integrian2D::GameObject* pOwner) noexcept
{
	return new Rook{ pOwner, m_pTexture };
}

void Rook::Move(TileComponent* const pDestinationTile) noexcept
{
	pDestinationTile;
}

std::vector<TileComponent*> Rook::GetPossibleMoves() const noexcept
{
	std::vector<TileComponent*> possibleMoves{};
	const Chessboard* const pChessboard{ Chessboard::GetInstance() };

	const int currentTileIndex{ pChessboard->GetTileIndex(m_pOwner) };

	/* A Rook can move unlimitedly horizontal and vertical, until it encounters a piece or an edge */
	/* Horizontal movement is index + 1 or index - 1 */
	/* Vertical movement is index + 8 or index - 8 */

	/* Only 7 tiles in both directions need to be checked at most */

	/* Check horizontal tiles */
	{
		const int currentRow{ pChessboard->GetRowNumber(currentTileIndex) };
		for (int horizontalChange{ -7 }; horizontalChange < 0; ++horizontalChange)
		{
			const int nextIndex{ currentTileIndex + horizontalChange };

			if (nextIndex < 0)
				break;

			/* Check if we're still in the same row */
			if (pChessboard->GetRowNumber(nextIndex) == currentRow)
			{
				/* If there is no piece on the tile, we can move there */
				TileComponent* const pTile{ pChessboard->GetTileComponent(nextIndex) };
				if (!pTile->GetPiece())
					possibleMoves.push_back(pTile);
				else /* we encountered a piece so we can't go further */
					break;
			}
		}

		for (int horizontalChange{ 1 }; horizontalChange < 8; ++horizontalChange)
		{
			const int nextIndex{ currentTileIndex + horizontalChange };

			if (nextIndex > 63)
				break;

			/* Check if we're still in the same row */
			if (pChessboard->GetRowNumber(nextIndex) == currentRow)
			{
				/* If there is no piece on the tile, we can move there */
				TileComponent* const pTile{ pChessboard->GetTileComponent(nextIndex) };
				if (!pTile->GetPiece())
					possibleMoves.push_back(pTile);
				else /* we encountered a piece so we can't go further */
					break;
			}
		}
	}

	/* Check vertical tiles */
	{
		const int currentCol{ pChessboard->GetColumnNumber(currentTileIndex) };
		for (int verticalChange{ -7 }; verticalChange < 0; ++verticalChange)
		{
			const int nextIndex{ currentTileIndex + verticalChange * 8 };

			if (nextIndex < 0)
				break;

			/* Check if we're still in the same column */
			if (pChessboard->GetColumnNumber(nextIndex) == currentCol)
			{
				/* If there is no piece on the tile, we can move there */
				TileComponent* const pTile{ pChessboard->GetTileComponent(nextIndex) };
				if (!pTile->GetPiece())
					possibleMoves.push_back(pTile);
				else /* we encountered a piece so we can't go further */
					break;
			}
		}

		for (int verticalChange{ 1 }; verticalChange < 8; ++verticalChange)
		{
			const int nextIndex{ currentTileIndex + verticalChange * 8 };

			if (nextIndex > 63)
				break;

			/* Check if we're still in the same column */
			if (pChessboard->GetColumnNumber(nextIndex) == currentCol)
			{
				/* If there is no piece on the tile, we can move there */
				TileComponent* const pTile{ pChessboard->GetTileComponent(nextIndex) };
				if (!pTile->GetPiece())
					possibleMoves.push_back(pTile);
				else /* we encountered a piece so we can't go further */
					break;
			}
		}
	}

	/* [TODO] Should still check to take other pieces + castling */

	return possibleMoves;
}
