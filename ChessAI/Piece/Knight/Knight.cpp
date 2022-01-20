#include "Knight.h"

#include "../../Chessboard/Chessboard.h"
#include "../../TileComponent/TileComponent.h"

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
	std::vector<TileComponent*> possibleMoves{};
	const Chessboard* const pChessboard{ Chessboard::GetInstance() };

	const int currentTileIndex{ pChessboard->GetTileIndex(m_pOwner) };

	/* A knight can only move in L shapes across the board */
	/* There are 8 different L shapes */
	/* These are represented as:
	index + 2 + 8, index + 2 + 8,
	index - 2 - 8, index - 2 - 8,
	index + 1 + 16, index - 1 + 16,
	index + 1 - 16, index - 1 - 16 */

	/* Check each possibility */
	TileComponent* pTileComponent{};
	int nextIndex{};

	
}
