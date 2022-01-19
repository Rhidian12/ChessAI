#pragma once

#include <Components/Component/Component.h>

namespace Integrian2D
{
	class Texture;
}

class Piece;

class TileComponent final : public Integrian2D::Component
{
public:
	TileComponent(Integrian2D::GameObject* const pOwner, const float tileWidth, const float tileHeight, Integrian2D::Texture* const pTexture);

	virtual Integrian2D::Component* Clone(Integrian2D::GameObject* pOwner) noexcept override;

	virtual void Render() const override;

	void SetPiece(Piece* const pPiece) noexcept;

	Piece* const GetPiece() const noexcept;

private:
	/* [TODO] Add reference to piece in here */
	float m_TileWidth;
	float m_TileHeight;

	Integrian2D::Texture* m_pTexture;
	Piece* m_pPiece;
};