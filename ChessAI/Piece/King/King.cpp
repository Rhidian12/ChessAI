#include "King.h"

#include "../../Chessboard/Chessboard.h"
#include "../../TileComponent/TileComponent.h"

King::King(Integrian2D::GameObject* const pOwner, Integrian2D::Texture* const pTexture)
	: Piece{ pOwner, TypeOfPiece::King, pTexture }
{
}

Integrian2D::Component* King::Clone(Integrian2D::GameObject* pOwner) noexcept
{
	return new King{ pOwner, m_pTexture };
}

std::vector<TileComponent*> King::GetPossibleMoves() const noexcept
{
	std::vector<TileComponent*> possibleMoves{};
	const Chessboard* const pChessboard{ Chessboard::GetInstance() };

	const int currentTileIndex{ pChessboard->GetTileIndex(m_pOwner) };

	/* A King can move 1 tile horizontally, vertically and diagonally, until it encounters a piece or an edge */
	/* Horizontal movement is index + 1 or index - 1 */
	/* Vertical movement is index + 8 or index - 8 */
	/* Moving diagonally is index + 8 + 1, index + 8 - 1, index - 8 + 1, index - 8 - 1 */

	/* Only 1 tiles in all directions need to be checked at most */

	/* Check horizontal tiles */
	{
		const int currentRow{ pChessboard->GetRowNumber(currentTileIndex) };

		{
			const int nextIndex{ currentTileIndex - 1 };

			if (nextIndex >= 0)
			{
				/* Check if we're still in the same row */
				if (pChessboard->GetRowNumber(nextIndex) == currentRow)
				{
					/* If there is no piece on the tile, we can move there */
					TileComponent* const pTile{ pChessboard->GetTileComponent(nextIndex) };
					if (!pTile->GetPiece())
						possibleMoves.push_back(pTile);
				}
			}
		}

		{
			const int nextIndex{ currentTileIndex + 1 };

			if (nextIndex <= 63)
			{
				/* Check if we're still in the same row */
				if (pChessboard->GetRowNumber(nextIndex) == currentRow)
				{
					/* If there is no piece on the tile, we can move there */
					TileComponent* const pTile{ pChessboard->GetTileComponent(nextIndex) };
					if (!pTile->GetPiece())
						possibleMoves.push_back(pTile);
				}
			}
		}
	}

	/* Check vertical tiles */
	{
		const int currentCol{ pChessboard->GetColumnNumber(currentTileIndex) };

		{
			const int nextIndex{ currentTileIndex - 8 };

			if (nextIndex >= 0)
			{
				/* Check if we're still in the same column */
				if (pChessboard->GetColumnNumber(nextIndex) == currentCol)
				{
					/* If there is no piece on the tile, we can move there */
					TileComponent* const pTile{ pChessboard->GetTileComponent(nextIndex) };
					if (!pTile->GetPiece())
						possibleMoves.push_back(pTile);
				}
			}
		}

		{
			const int nextIndex{ currentTileIndex + 8 };

			if (nextIndex <= 63)
			{
				/* Check if we're still in the same column */
				if (pChessboard->GetColumnNumber(nextIndex) == currentCol)
				{
					/* If there is no piece on the tile, we can move there */
					TileComponent* const pTile{ pChessboard->GetTileComponent(nextIndex) };
					if (!pTile->GetPiece())
						possibleMoves.push_back(pTile);
				}
			}
		}
	}

	/* Check top diagonal movement */
	{
		/* Check top right */
		{
			const int nextIndex{ currentTileIndex + 9 };

			if (nextIndex <= 63)
			{
				TileComponent* const pTile{ pChessboard->GetTileComponent(nextIndex) };
				if (!pTile->GetPiece())
					possibleMoves.push_back(pTile);
			}
		}

		/* Check top left */
		{
			const int nextIndex{ currentTileIndex + 7 };

			if (nextIndex <= 63)
			{
				TileComponent* const pTile{ pChessboard->GetTileComponent(nextIndex) };
				if (!pTile->GetPiece())
					possibleMoves.push_back(pTile);
			}
		}
	}

	/* Check bottom diagonal movement */
	{
		/* Check bottom right */
		{
			const int nextIndex{ currentTileIndex - 9 };

			if (nextIndex >= 0)
			{
				TileComponent* const pTile{ pChessboard->GetTileComponent(nextIndex) };
				if (!pTile->GetPiece())
					possibleMoves.push_back(pTile);
			}
		}

		/* Check bottom left */
		{
			const int nextIndex{ currentTileIndex - 7 };

			if (nextIndex >= 0)
			{
				TileComponent* const pTile{ pChessboard->GetTileComponent(nextIndex) };
				if (!pTile->GetPiece())
					possibleMoves.push_back(pTile);
			}
		}
	}

	return possibleMoves;
}
