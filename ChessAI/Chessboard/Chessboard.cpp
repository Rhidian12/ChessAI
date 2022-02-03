#include "Chessboard.h"

#include <Utils/Utils.h>
#include <GameObject/GameObject.h>
#include <Components/TransformComponent/TransformComponent.h>
#include <Input/InputManager/InputManager.h>
#include <Renderer/Renderer.h>
#include <Math/TypeDefines.h>
#include <SceneManager/SceneManager.h>

#include "../TileComponent/TileComponent.h"
#include "../Piece/Piece.h"
#include "../Commands/Commands.h"

Chessboard::Chessboard()
	: m_IsRMBClicked{}
	, m_IsLMBClicked{}
{
	using namespace Integrian2D;
}

Chessboard* const Chessboard::GetInstance() noexcept
{
	if (!m_pInstance)
		m_pInstance = new Chessboard{};

	return m_pInstance;
}

void Chessboard::Cleanup() noexcept
{
	Integrian2D::Utils::SafeDelete(m_pInstance);
}

void Chessboard::Update() noexcept
{
	HandleInput();
}

void Chessboard::HandleInput() noexcept
{
	using namespace Integrian2D;

	if (InputManager::GetInstance()->IsMouseButtonPressed(MouseButton::RMB))
		m_IsRMBClicked = !m_IsRMBClicked;

	if (InputManager::GetInstance()->IsMouseButtonPressed(MouseButton::LMB))
		m_IsLMBClicked = !m_IsLMBClicked;

	if (m_IsRMBClicked)
		RenderPossibleMoves();
}

void Chessboard::RenderPossibleMoves() noexcept
{
	using namespace Integrian2D;

	Renderer* const pRenderer{ Renderer::GetInstance() };
	Chessboard* const pChessboard{ Chessboard::GetInstance() };
	const Point2f& mousePos{ InputManager::GetInstance()->GetMousePosition() };

	const auto it{ std::find_if(pChessboard->GetTiles().cbegin(), pChessboard->GetTiles().cend(), [&mousePos](const GameObject* const pTile)->bool
		{
			const Point2f& pos{ pTile->pTransform->GetWorldPosition() };
			TileComponent* const pTileComponent{ pTile->GetComponentByType<TileComponent>() };

			if (mousePos.x <= pos.x || mousePos.x >= pos.x + pTileComponent->GetTileWidth())
				return false;

			if (mousePos.y <= pos.y || mousePos.y >= pos.y + pTileComponent->GetTileHeight())
				return false;

			return true;
		}) };

	if (it == pChessboard->GetTiles().cend())
		return;

	const TileComponent* const pTile{ (*it)->GetComponentByType<TileComponent>() };

	/* Safety check */
	if (pTile)
	{
		/* Does the tile have a piece */
		if (const Piece* const pPiece{ pTile->GetPiece() }; pPiece != nullptr)
		{
			auto moves{ pPiece->GetPossibleMoves() };
			for (const TileComponent* const pPossibleMove : moves)
			{
				/* [TODO] Figure out why Circlef is causing linker issues! */
				 //pRenderer->RenderFilledCircle(Circlef{pPossibleMove->GetCenterOfTile(), 5.f}); 
				const Rectf center{ pPossibleMove->GetCenterOfTile().x - 12.5f, pPossibleMove->GetCenterOfTile().y - 12.5f, 25.f, 25.f };
				pRenderer->RenderFilledRectangle(center);
			}
		}
	}
}

void Chessboard::SetTiles(const std::vector<Integrian2D::GameObject*>& tiles) noexcept
{
	m_Tiles = tiles;
}

int Chessboard::GetTileIndex(const Integrian2D::GameObject* const pTile) const noexcept
{
	using namespace Integrian2D;

	ASSERT(pTile != nullptr, "Chessboard::GetTileIndex(GameObject*) > Provided GameObject is a nullptr!");

	for (int i{}; i < m_Tiles.size(); ++i)
		if (m_Tiles[i] == pTile)
			return i;

	return -1;
}

int Chessboard::GetTileIndex(const TileComponent* const pTile) const noexcept
{
	using namespace Integrian2D;

	ASSERT(pTile != nullptr, "Chessboard::GetTileIndex(TileComponent*) > Provided TileComponent is a nullptr!");

	for (int i{}; i < m_Tiles.size(); ++i)
		if (m_Tiles[i]->GetComponentByType<TileComponent>() == pTile)
			return i;

	return -1;
}

int Chessboard::GetRowNumber(const int index) const noexcept
{
	Integrian2D::ASSERT(index >= 0 && index < m_Tiles.size(), "Chessboard::GetRowNumber() > Index is out of bounds!");

	return index / 8;
}

int Chessboard::GetColumnNumber(const int index) const noexcept
{
	Integrian2D::ASSERT(index >= 0 && index < m_Tiles.size(), "Chessboard::GetRowNumber() > Index is out of bounds!");

	return index % 8;
}

TileComponent* const Chessboard::GetTileComponent(const Integrian2D::Point2f& pos) const noexcept
{
	using namespace Integrian2D;

	for (const GameObject* const pTile : m_Tiles)
		if (pTile->pTransform->GetWorldPosition() == pos)
			return pTile->GetComponentByType<TileComponent>();

	return nullptr;
}

TileComponent* const Chessboard::GetTileComponent(const int index) const noexcept
{
	Integrian2D::ASSERT((index < m_Tiles.size()) && (index >= 0), "Chessboard::GetTileComponent(index) > Index was out of bounds!");

	return m_Tiles[index]->GetComponentByType<TileComponent>();
}

const std::vector<Integrian2D::GameObject*>& Chessboard::GetTiles() const noexcept
{
	return m_Tiles;
}
