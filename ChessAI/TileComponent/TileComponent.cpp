#include "TileComponent.h"

#include <GameObject/GameObject.h>
#include <Components/TransformComponent/TransformComponent.h>
#include <Renderer/Renderer.h>

TileComponent::TileComponent(Integrian2D::GameObject* const pOwner, const float tileWidth, const float tileHeight, Integrian2D::Texture* const pTexture)
	: Component{ pOwner }
	, m_TileWidth{ tileWidth }
	, m_TileHeight{ tileHeight }
	, m_pTexture{ pTexture }
{
}

Integrian2D::Component* TileComponent::Clone(Integrian2D::GameObject* pOwner) noexcept
{
	return new TileComponent{ pOwner, m_TileWidth, m_TileHeight, m_pTexture };
}

void TileComponent::Render() const
{
	using namespace Integrian2D;

	Renderer::GetInstance()->RenderTexture(m_pTexture, PRectf{ m_pOwner->pTransform->GetWorldPosition(), m_TileWidth, m_TileHeight }, Rectf{});
}