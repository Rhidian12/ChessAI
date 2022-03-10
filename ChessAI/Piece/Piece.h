#pragma once

#include <Components/Component/Component.h>

#include <vector>

namespace Integrian2D
{
	class Texture;
}

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

enum class PieceColour : int8_t
{
	White = 0b0001,
	Black = ~0b0001,
	None = 0
};

/* Other pieces inherit from this class */
class Piece : public Integrian2D::Component
{
public:
	Piece(Integrian2D::GameObject* const pOwner, const TypeOfPiece type, Integrian2D::Texture* const pTexture);

	virtual Component* Clone(Integrian2D::GameObject*) noexcept = 0;

	virtual void Render() const override;

	virtual Piece* GhostMove(TileComponent* const pDestinationTile) noexcept;
	virtual void Move(TileComponent* const pDestinationTile) noexcept;

	virtual std::vector<TileComponent*> GetPossibleMoves() const noexcept = 0;

	void SetColourOfPiece(const PieceColour colour) noexcept;

	TypeOfPiece GetTypeOfPiece() const noexcept;
	PieceColour GetColourOfPiece() const noexcept;

protected:
	TypeOfPiece m_TypeOfPiece;
	PieceColour m_PieceColour;
	Integrian2D::Texture* m_pTexture;

private:
	TileComponent* m_pTileComponent;
};