#include "Queen.h"

#include "../../Chessboard/Chessboard.h"
#include "../../TileComponent/TileComponent.h"

Queen::Queen(Integrian2D::GameObject* const pOwner, Integrian2D::Texture* const pTexture)
    : Piece{ pOwner, TypeOfPiece::Queen, pTexture }
{
}

Integrian2D::Component* Queen::Clone(Integrian2D::GameObject* pOwner) noexcept
{
    return new Queen{ pOwner, m_pTexture };
}

std::vector<TileComponent*> Queen::GetPossibleMoves() const noexcept
{
	std::vector<TileComponent*> possibleMoves{};
	const Chessboard* const pChessboard{ Chessboard::GetInstance() };

	const int currentTileIndex{ pChessboard->GetTileIndex(m_pOwner) };

	/* A Queen can move unlimitedly horizontally, vertically and diagonally, until it encounters a piece or an edge */
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

	/* Check top diagonal movement */
	{
		/* Check top right */
		for (int i{}; i < 7; ++i)
		{
			const int nextIndex{ currentTileIndex + i * 8 + 1 };

			if (nextIndex > 63)
				break;

			TileComponent* const pTile{ pChessboard->GetTileComponent(nextIndex) };
			if (!pTile->GetPiece())
				possibleMoves.push_back(pTile);
			else
				break; /* we've encountered a piece so we can't move in that direction any longer*/
		}

		/* Check top left */
		for (int i{}; i < 7; ++i)
		{
			const int nextIndex{ currentTileIndex + i * 8 - 1 };

			if (nextIndex > 63)
				break;

			TileComponent* const pTile{ pChessboard->GetTileComponent(nextIndex) };
			if (!pTile->GetPiece())
				possibleMoves.push_back(pTile);
			else
				break; /* we've encountered a piece so we can't move in that direction any longer*/
		}
	}

	/* Check bottom diagonal movement */
	{
		/* Check bottom right */
		for (int i{}; i < 7; ++i)
		{
			const int nextIndex{ currentTileIndex - i * 8 + 1 };

			if (nextIndex < 0)
				break;

			TileComponent* const pTile{ pChessboard->GetTileComponent(nextIndex) };
			if (!pTile->GetPiece())
				possibleMoves.push_back(pTile);
			else
				break; /* we've encountered a piece so we can't move in that direction any longer*/
		}

		/* Check bottom left */
		for (int i{}; i < 7; ++i)
		{
			const int nextIndex{ currentTileIndex - i * 8 - 1 };

			if (nextIndex < 0)
				break;

			TileComponent* const pTile{ pChessboard->GetTileComponent(nextIndex) };
			if (!pTile->GetPiece())
				possibleMoves.push_back(pTile);
			else
				break; /* we've encountered a piece so we can't move in that direction any longer*/
		}
	}

	return possibleMoves;
}
