#include "TileComponent.h"

#include <GameObject/GameObject.h>
#include <Components/TransformComponent/TransformComponent.h>
#include <Renderer/Renderer.h>

TileComponent::TileComponent(Integrian2D::GameObject* const pOwner, const float tileWidth, const float tileHeight, Integrian2D::Texture* const pTexture)
	: Component{ pOwner }
	, m_TileWidth{ tileWidth }
	, m_TileHeight{ tileHeight }
	, m_pTexture{ pTexture }
	, m_pPiece{}
{
}

Integrian2D::Component* TileComponent::Clone(Integrian2D::GameObject* pOwner) noexcept
{
	TileComponent* pTile{ new TileComponent{ pOwner, m_TileWidth, m_TileHeight, m_pTexture } };

	pTile->m_pPiece = m_pPiece;

	return pTile;
}

void TileComponent::Render() const
{
	using namespace Integrian2D;

	Renderer::GetInstance()->RenderTexture(m_pTexture, PRectf{ m_pOwner->pTransform->GetWorldPosition(), m_TileWidth, m_TileHeight }, Rectf{});
}

void TileComponent::SetPiece(Piece* const pPiece) noexcept
{
	m_pPiece = pPiece;
}

Piece* const TileComponent::GetPiece() const noexcept
{
	return m_pPiece;
}

Integrian2D::Point2f TileComponent::GetCenterOfTile() const noexcept
{
	using namespace Integrian2D;

	Point2f center{ m_pOwner->pTransform->GetWorldPosition() };

	center.x += m_TileWidth * 0.5f;
	center.y += m_TileHeight * 0.5f;

	return center;
}
