#pragma once

#include <Components/Component/Component.h>

#include <vector>

class TileComponent;

enum class TypeOfPiece
{
	Pawn,
	Rook,
	Knight,
	Bishop,
	Queen,
	King
};

/* Other pieces inherit from this class */
class Piece : public Integrian2D::Component
{
public:
	Piece(Integrian2D::GameObject* const pOwner, const TypeOfPiece type);

	virtual Component* Clone(Integrian2D::GameObject*) noexcept = 0;

	virtual void Move(TileComponent* const pDestinationTile) noexcept = 0;

	virtual std::vector<TileComponent*> GetPossibleMoves() const noexcept = 0;

	TypeOfPiece GetTypeOfPiece() const noexcept;

protected:
	TypeOfPiece m_TypeOfPiece;
};