#include "Bishop.h"

#include "../../Chessboard/Chessboard.h"
#include "../../TileComponent/TileComponent.h"

Bishop::Bishop(Integrian2D::GameObject* const pOwner, Integrian2D::Texture* const pTexture)
	: Piece{ pOwner, TypeOfPiece::Bishop, pTexture }
{
}

Integrian2D::Component* Bishop::Clone(Integrian2D::GameObject* pOwner) noexcept
{
	return new Bishop{ pOwner, m_pTexture };
}

std::vector<TileComponent*> Bishop::GetPossibleMoves() const noexcept
{
	std::vector<TileComponent*> possibleMoves{};
	const Chessboard* const pChessboard{ Chessboard::GetInstance() };

	const int currentTileIndex{ pChessboard->GetTileIndex(m_pOwner) };

	/* Bishop moves diagonally in 4 directions */
	/* Moving diagonally is index + 8 + 1, index + 8 - 1, index - 8 + 1, index - 8 - 1 */

	/* Only 7 tiles in both directions need to be checked at most */

	/* Check top movement */
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

	/* Check bottom movement */
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
