#include "Piece.h"

#include <Renderer/Renderer.h>
#include <GameObject/GameObject.h>
#include <Components/TransformComponent/TransformComponent.h>
#include <Texture/Texture.h>

Piece::Piece(Integrian2D::GameObject* const pOwner, const TypeOfPiece type, Integrian2D::Texture* const pTexture)
	: Component{ pOwner }
	, m_TypeOfPiece{ type }
	, m_pTexture{ pTexture }
{
}

void Piece::Render() const
{
	using namespace Integrian2D;

	Renderer::GetInstance()->RenderTexture(m_pTexture, PRectf{ m_pOwner->pTransform->GetWorldPosition(), m_pTexture->GetWidth(), m_pTexture->GetHeight() }, Rectf{});
}

TypeOfPiece Piece::GetTypeOfPiece() const noexcept
{
	return m_TypeOfPiece;
}
