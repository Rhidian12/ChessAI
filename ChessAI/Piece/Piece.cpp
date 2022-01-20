#include "Piece.h"

#include <Renderer/Renderer.h>
#include <GameObject/GameObject.h>
#include <Components/TransformComponent/TransformComponent.h>
#include <Texture/Texture.h>

#include "../Chessboard/Chessboard.h"
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
	pos.y -= m_pTexture->GetHeight() * 0.5f;

	Renderer::GetInstance()->RenderTexture(m_pTexture, PRectf{ pos, m_pTexture->GetWidth(), m_pTexture->GetHeight()}
	, Rectf{});
}

void Piece::Move(TileComponent* const pDestinationTile) noexcept
{
	/* Remove the piece from the current tile */
	Chessboard::GetInstance()->GetTileComponent(m_pOwner->pTransform->GetWorldPosition())->SetPiece(nullptr);

	/* Set the piece to our destination tile */
	pDestinationTile->SetPiece(this);

	/* Set this piece's position to the center of the destination tile */
	m_pOwner->pTransform->SetPosition(pDestinationTile->GetCenterOfTile());
}

TypeOfPiece Piece::GetTypeOfPiece() const noexcept
{
	return m_TypeOfPiece;
}
