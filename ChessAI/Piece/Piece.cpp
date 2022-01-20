#include "Piece.h"

#include <Renderer/Renderer.h>
#include <GameObject/GameObject.h>
#include <Components/TransformComponent/TransformComponent.h>
#include <Texture/Texture.h>

#include "../TileComponent/TileComponent.h"

Piece::Piece(Integrian2D::GameObject* const pOwner, const TypeOfPiece type, Integrian2D::Texture* const pTexture)
	: Component{ pOwner }
	, m_TypeOfPiece{ type }
	, m_pTexture{ pTexture }
	, m_pTileComponent{ pOwner->GetComponentByType<TileComponent>() } /* [CRINGE] dependant on order of initialisation */
{
}

void Piece::Render() const
{
	using namespace Integrian2D;

	Point2f pos{ m_pTileComponent->GetCenterOfTile() };
	pos.x -= m_pTexture->GetWidth() * 0.5f;
	pos.y -= m_pTexture->GetHeight() * 0.5;

	Renderer::GetInstance()->RenderTexture(m_pTexture, PRectf{ pos, m_pTexture->GetWidth(), m_pTexture->GetHeight()}, Rectf{});
}

TypeOfPiece Piece::GetTypeOfPiece() const noexcept
{
	return m_TypeOfPiece;
}
