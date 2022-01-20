#pragma once

#include "../Piece.h"

class Knight final : public Piece
{
public:
	Knight(Integrian2D::GameObject* const pOwner, Integrian2D::Texture* const pTexture);

	virtual Component* Clone(Integrian2D::GameObject* pOwner) noexcept override;

	virtual std::vector<TileComponent*> GetPossibleMoves() const noexcept override;
};