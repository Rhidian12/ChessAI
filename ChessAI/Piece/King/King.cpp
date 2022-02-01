#include "King.h"

#include "../../Chessboard/Chessboard.h"
#include "../../TileComponent/TileComponent.h"

#include <Utils/Utils.h>

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
	/* Only 1 tile in all directions need to be checked at most */

	constexpr int amountOfIndices{ 8 };
	constexpr int indicesToAdd[amountOfIndices]{ 1, -1, 8, -8, 9, 7, -9, -7 };


	/* Check each possibility */

	TileComponent* pTileComponent{};
	int nextIndex{};
	for (int i{}; i < amountOfIndices; ++i)
	{
		nextIndex = currentTileIndex + indicesToAdd[i];
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
			/* Diagonal movement gets checked regardless in the Range check */

			/* If there is no same coloured piece on the tile */
			pTileComponent = pChessboard->GetTileComponent(nextIndex);
			if (pTileComponent->GetPiece()->GetColourOfPiece() != m_PieceColour)
				possibleMoves.push_back(pTileComponent);
		}
	}

	return possibleMoves;
}
