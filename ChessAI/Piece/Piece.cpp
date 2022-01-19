#include "Piece.h"

Piece::Piece(Integrian2D::GameObject* const pOwner, const TypeOfPiece type)
	: Component{ pOwner }
	, m_TypeOfPiece{ type }
{
}

TypeOfPiece Piece::GetTypeOfPiece() const noexcept
{
	return m_TypeOfPiece;
}
