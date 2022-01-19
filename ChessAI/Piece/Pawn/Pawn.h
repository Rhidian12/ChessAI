#pragma once

#include "../Piece.h"

namespace Integrian2D
{
	class Texture;
}

class Pawn final : public Piece
{
public:
	Pawn(Integrian2D::GameObject* const pOwner, Integrian2D::Texture* const pTexture);

	virtual Component* Clone(Integrian2D::GameObject* pOwner) noexcept override;

	virtual void Move(TileComponent* const pDestinationTile) noexcept override;

	virtual std::vector<TileComponent*> GetPossibleMoves() const noexcept override;

private:
	bool m_HasMoved;
};