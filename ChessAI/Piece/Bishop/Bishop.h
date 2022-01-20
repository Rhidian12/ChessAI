#pragma once

#include "../Piece.h"

class Bishop final : public Piece
{
public:
	Bishop(Integrian2D::GameObject* const pOwner, Integrian2D::Texture* const pTexture);

	virtual Component* Clone(Integrian2D::GameObject* pOwner) noexcept override;

	virtual std::vector<TileComponent*> GetPossibleMoves() const noexcept override;
};