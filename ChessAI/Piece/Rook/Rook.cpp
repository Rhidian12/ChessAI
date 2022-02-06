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

std::vector<TileComponent*> Rook::GetPossibleMoves() const noexcept
{
	std::vector<TileComponent*> possibleMoves{};
	const Chessboard* const pChessboard{ Chessboard::GetInstance() };

	const int currentTileIndex{ pChessboard->GetTileIndex(m_pOwner) };

	/* A Rook can move unlimitedly horizontal and vertical, until it encounters a piece or an edge */
	/* Horizontal movement is index + 1 or index - 1 */
	/* Vertical movement is index + 8 or index - 8 */

	/* Only 7 tiles in both directions need to be checked at most */

	constexpr int amountOfTilesToCheck{ 7 };
	constexpr int amountOfIndicesToAdd{ 8 };
	constexpr int indicesToAdd[amountOfIndicesToAdd]{ 1, -1, 8, -8 };

	TileComponent* pTileComponent{};
	int nextIndex{};

	for (int i{}; i < amountOfIndicesToAdd; ++i)
	{
		for (int amountOfTilesTravelled{ 1 }; amountOfTilesTravelled < amountOfTilesToCheck; ++amountOfTilesTravelled)
		{
			nextIndex = currentTileIndex + amountOfTilesTravelled * indicesToAdd[i];
			if (Integrian2D::Utils::IsInRange(nextIndex, 0, 63))
			{
				/* check horizontal movement if we're moving horizontally */
				if (indicesToAdd[i] == 1 || indicesToAdd[i] == -1)
				{
					if (pChessboard->GetRowNumber(nextIndex) != pChessboard->GetRowNumber(currentTileIndex))
						continue;
				}
				/* Check vertical movement if we're moving vertically */
				else if (indicesToAdd[i] == 8 || indicesToAdd[i] == -8)
				{
					if (pChessboard->GetColumnNumber(nextIndex) != pChessboard->GetColumnNumber(currentTileIndex))
						continue;
				}

				pTileComponent = pChessboard->GetTileComponent(nextIndex);

				/* if there is no piece, we can move and further */
				if (!pTileComponent->GetPiece())
				{
					possibleMoves.push_back(pTileComponent);
				}
				/* if there is an enemy piece we can move, but no further */
				else if (pTileComponent->GetPiece()->GetColourOfPiece() != m_PieceColour)
				{
					possibleMoves.push_back(pTileComponent);
					break;
				}
				/* if our piece is there, we can't move and no further */
				else
				{
					break;
				}
			}
		}
	}

	/* [TODO] Should still check to take other pieces + castling */

	return possibleMoves;
}
