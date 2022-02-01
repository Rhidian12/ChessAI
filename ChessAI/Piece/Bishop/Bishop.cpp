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

	constexpr int amountOfTilesToCheck{ 7 };
	constexpr int amountOfIndicesToAdd{ 4 };
	constexpr int indicesToAdd[amountOfIndicesToAdd]{ 9, 7, -9, -7 };

	TileComponent* pTileComponent{};
	int nextIndex{};

	for (int i{}; i < amountOfIndicesToAdd; ++i)
	{
		for (int amountOfTilesTravelled{}; amountOfTilesTravelled < amountOfTilesToCheck; ++amountOfTilesTravelled)
		{
			nextIndex = currentTileIndex + amountOfTilesTravelled * indicesToAdd[i];
			if (Integrian2D::Utils::IsInRange(nextIndex, 0, 63))
			{
				/* Diagonal movement gets checked regardless in the Range check */

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

	return possibleMoves;
}
