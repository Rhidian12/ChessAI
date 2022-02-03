#include "Knight.h"

#include "../../Chessboard/Chessboard.h"
#include "../../TileComponent/TileComponent.h"

#include <Utils/Utils.h>

Knight::Knight(Integrian2D::GameObject* const pOwner, Integrian2D::Texture* const pTexture)
	: Piece{ pOwner, TypeOfPiece::Knight, pTexture }
{
}

Integrian2D::Component* Knight::Clone(Integrian2D::GameObject* pOwner) noexcept
{
	return new Knight{ pOwner, m_pTexture };
}

std::vector<TileComponent*> Knight::GetPossibleMoves() const noexcept
{
	using namespace Integrian2D;

	std::vector<TileComponent*> possibleMoves{};
	const Chessboard* const pChessboard{ Chessboard::GetInstance() };

	const int currentTileIndex{ pChessboard->GetTileIndex(m_pOwner) };

	/* A knight can only move in L shapes across the board */
	/* There are 8 different L shapes */
	/* These are represented as:
	0. index + 2 + 8
	1. index - 2 + 8
	2. index - 2 - 8
	3. index + 2 - 8
	4. index + 1 + (2 * 8)
	5. index - 1 + (2 * 8)
	6. index - 1 - (2 * 8)
	7. index + 1 - (2 * 8) */

	constexpr int amountOfIndicesToAdd{ 8 };
	constexpr int indicesToAdd[amountOfIndicesToAdd]{ 10, 6, -10, -6, 17, 15, -17, -15 };

	/* Check each possibility */
	TileComponent* pTileComponent{};
	int nextIndex{};

	for (int i{}; i < amountOfIndicesToAdd; ++i)
	{
		nextIndex = currentTileIndex + indicesToAdd[i];
		if (Utils::IsInRange(nextIndex, 0, 63))
		{
			/* 0. - 3. must only go up or down 1 row */
			if (Utils::IsInRange(i, 0, 3))
				if (!Utils::AreEqual(fabs(pChessboard->GetRowNumber(nextIndex) - pChessboard->GetRowNumber(currentTileIndex)), 1.0))
					continue;

			/* 4. - 7. must only go up or down 2 rows */
			if (Utils::IsInRange(i, 4, 7))
				if (!Utils::AreEqual(fabs(pChessboard->GetRowNumber(nextIndex) - pChessboard->GetRowNumber(currentTileIndex)), 2.0))
					continue;

			/* If there is no same coloured piece on the tile */
			pTileComponent = pChessboard->GetTileComponent(nextIndex);
			if (!pTileComponent->GetPiece() || (pTileComponent->GetPiece()->GetColourOfPiece() != m_PieceColour))
				possibleMoves.push_back(pTileComponent);
		}
	}

	return possibleMoves;
}
