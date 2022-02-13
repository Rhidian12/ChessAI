#include "Piece.h"

#include <Renderer/Renderer.h>
#include <GameObject/GameObject.h>
#include <Components/TransformComponent/TransformComponent.h>
#include <Texture/Texture.h>
#include <Utils/Utils.h>

#include <GameObject/GameObject.h>

#include "../Chessboard/Chessboard.h"
#include "../TileComponent/TileComponent.h"

#include "Pawn/Pawn.h"
#include "Bishop/Bishop.h"
#include "Knight/Knight.h"
#include "Rook/Rook.h"
#include "Queen/Queen.h"
#include "King/King.h"

Piece::Piece(Integrian2D::GameObject* const pOwner, const TypeOfPiece type, Integrian2D::Texture* const pTexture)
	: Component{ pOwner }
	, m_TypeOfPiece{ type }
	, m_PieceColour{ PieceColour::None }
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

	Renderer::GetInstance()->RenderTexture(
		m_pTexture,
		PRectf{ pos, m_pTexture->GetWidth(), m_pTexture->GetHeight() },
		Rectf{}
	);
}

void Piece::Move(TileComponent* const pDestinationTile, const bool) noexcept
{
	/* Remove the piece from the current tile */
	std::vector<Component*> pPieces{};

	/* Get the piece from the game object */
	/* [CRINGE] figure out why the fuck i have to ask for the specific class instead of Component */
	switch (m_TypeOfPiece)
	{
	case TypeOfPiece::Pawn:
		m_pTileComponent->GetOwner()->RemoveAllComponentsByType<Pawn>(&pPieces);
		break;
	case TypeOfPiece::Bishop:
		m_pTileComponent->GetOwner()->RemoveAllComponentsByType<Bishop>(&pPieces);
		break;
	case TypeOfPiece::Knight:
		m_pTileComponent->GetOwner()->RemoveAllComponentsByType<Knight>(&pPieces);
		break;
	case TypeOfPiece::Rook:
		m_pTileComponent->GetOwner()->RemoveAllComponentsByType<Rook>(&pPieces);
		break;
	case TypeOfPiece::Queen:
		m_pTileComponent->GetOwner()->RemoveAllComponentsByType<Queen>(&pPieces);
		break;
	case TypeOfPiece::King:
		m_pTileComponent->GetOwner()->RemoveAllComponentsByType<King>(&pPieces);
		break;
	}
	m_pTileComponent->SetPiece(nullptr);

	/* Change our tile component to the new tile component */
	m_pTileComponent = pDestinationTile;

	/* Set the piece to our destination tile */
	m_pTileComponent->SetPiece(this);
	m_pTileComponent->GetOwner()->AddComponent(pPieces[0]);
	pPieces[0]->SetOwner(m_pTileComponent->GetOwner());
}

void Piece::SetColourOfPiece(const PieceColour colour) noexcept
{
	Integrian2D::ASSERT(m_PieceColour == PieceColour::None, "Piece::SetColourOfPiece() > Colour has already been set!");

	m_PieceColour = colour;
}

TypeOfPiece Piece::GetTypeOfPiece() const noexcept
{
	return m_TypeOfPiece;
}

PieceColour Piece::GetColourOfPiece() const noexcept
{
	return m_PieceColour;
}
