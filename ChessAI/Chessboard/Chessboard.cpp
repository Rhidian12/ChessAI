#include "Chessboard.h"

#include <Utils/Utils.h>
#include <GameObject/GameObject.h>
#include <Components/TransformComponent/TransformComponent.h>
#include <Input/InputManager/InputManager.h>
#include <Renderer/Renderer.h>
#include <Math/TypeDefines.h>
#include <SceneManager/SceneManager.h>
#include <AI/DecisionMaking/FiniteStateMachine/FiniteStateMachine.h>
#include <AI/Blackboard/Blackboard.h>

#include "../TileComponent/TileComponent.h"
#include "../Piece/Piece.h"
#include "../Commands/Commands.h"
#include "../States/States.h"

Chessboard::Chessboard()
	: m_pBlackboard{}
	, m_pFSM{}
{
	using namespace Integrian2D;

	m_pBlackboard = new Blackboard{};

	m_pBlackboard->AddData("Tiles", &m_Tiles);
	m_pBlackboard->AddData("RMBMousePosition", Point2f{});
	m_pBlackboard->AddData("LMBMousePosition", Point2f{});
	m_pBlackboard->AddData("HasUserRightClicked", false);
	m_pBlackboard->AddData("HasUserLeftClicked", false);
	m_pBlackboard->AddData("SelectedPiece", static_cast<Piece*>(nullptr));
	m_pBlackboard->AddData("OriginalTile", static_cast<TileComponent*>(nullptr));
	m_pBlackboard->AddData("WasPieceMoved", false);
	m_pBlackboard->AddData("WasEscapePressed", false);

	FSMState* pNoInputState{ new FSMState{ m_pFSM, &States::NoUserInput } };
	FSMState* pRightClickState{ new FSMState{ m_pFSM, &States::UserRightClick } };
	FSMState* pSelectPieceState{ new FSMState{ m_pFSM, &States::SelectPiece } };
	FSMState* pMovePieceState{ new FSMState{ m_pFSM, &States::MovePiece } };

	m_pFSM = new FiniteStateMachine{ m_pBlackboard, pNoInputState };

	m_pFSM->AddState(pRightClickState);

	Transition* pFromNoInputToRightClick{ new Transition{ m_pFSM, pNoInputState, pRightClickState, &Transitions::HasUserRightClicked } };
	Transition* pFromRightClickToNoUserInput{ new Transition{ m_pFSM, pRightClickState, pNoInputState, &Transitions::HasUserRightClicked } };
	Transition* pFromNoInputToSelectPiece{ new Transition{ m_pFSM, pNoInputState, pSelectPieceState, &Transitions::HasUserLeftClicked } };
	Transition* pFromSelectPieceToMovePiece{ new Transition{ m_pFSM, pSelectPieceState, pMovePieceState, &Transitions::HasPieceBeenSelectedAndHasUserLeftClicked } };
	Transition* pFromMovePieceToNoUserInput{ new Transition{ m_pFSM, pMovePieceState, pNoInputState, &Transitions::WasPieceMoved } };
	Transition* pFromRightClickToSelectPiece{ new Transition{ m_pFSM, pRightClickState, pSelectPieceState, &Transitions::HasUserLeftClicked } };

	m_pFSM->AddTransition(pFromRightClickToNoUserInput);
	m_pFSM->AddTransition(pFromNoInputToRightClick);
	m_pFSM->AddTransition(pFromNoInputToSelectPiece);
	m_pFSM->AddTransition(pFromSelectPieceToMovePiece);
	m_pFSM->AddTransition(pFromMovePieceToNoUserInput);
	m_pFSM->AddTransition(pFromRightClickToSelectPiece);

	InputManager::GetInstance()->AddCommand(
		GameInput{ MouseButton::LMB },
		new Commands::LeftClickChessboardCommand{ SceneManager::GetInstance()->GetScene("ChessScene") },
		State::OnRelease);

	InputManager::GetInstance()->AddCommand(
		GameInput{ MouseButton::RMB },
		new Commands::RightClickChessboardCommand{ SceneManager::GetInstance()->GetScene("ChessScene") },
		State::OnRelease);

	InputManager::GetInstance()->AddCommand(
		GameInput{ MouseButton::RMB },
		new Commands::EscapePressedCommand{ SceneManager::GetInstance()->GetScene("ChessScene") },
		State::OnRelease);
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
	//HandleInput();

	m_pFSM->Update();
}

void Chessboard::HandleInput() noexcept
{
	using namespace Integrian2D;
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

void Chessboard::ToggleIsLMBClicked(const std::string& file) noexcept
{
	Integrian2D::ASSERT(file.find("Commands.cpp") != std::string::npos, "Chessboard::SetIsLMBClicked() > Only Commands may call this function!");

	m_pBlackboard->ChangeData("HasUserLeftClicked", true);
}

void Chessboard::ToggleIsRMBClicked(const std::string& file) noexcept
{
	Integrian2D::ASSERT(file.find("Commands.cpp") != std::string::npos, "Chessboard::SetIsRMBClicked() > Only Commands may call this function!");

	m_pBlackboard->ChangeData("HasUserRightClicked", true);
}

void Chessboard::ToggleIsEscapePressed(const std::string& file) noexcept
{
	Integrian2D::ASSERT(file.find("Commands.cpp") != std::string::npos, "Chessboard::ToggleIsEscapePressed() > Only Commands may call this function!");

	m_pBlackboard->ChangeData("WasEscapePressed", true);
}
