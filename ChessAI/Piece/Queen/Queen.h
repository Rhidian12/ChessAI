#pragma once

#include "../Piece.h"

class Queen final : public Piece
{
public:
	Queen(Integrian2D::GameObject* const pOwner, Integrian2D::Texture* const pTexture);

	virtual Component* Clone(Integrian2D::GameObject* pOwner) noexcept override;

	virtual std::vector<TileComponent*> GetPossibleMoves() const noexcept override;
};