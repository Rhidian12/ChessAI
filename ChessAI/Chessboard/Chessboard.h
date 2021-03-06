#pragma once

#include <Math/TypeDefines.h>
#include <IListener/IListener.h>

#include "../Piece/Piece.h"

#include <vector>

namespace Integrian2D
{
	class GameObject;
	class FiniteStateMachine;
	class Blackboard;
}

class TileComponent;
class Piece;

class Chessboard final : public Integrian2D::IListener
{
public:
	static Chessboard* const GetInstance() noexcept;
	static void Cleanup() noexcept;

	virtual bool OnEvent(const Integrian2D::Event& event) override;

	~Chessboard() = default;

	void Update() noexcept;

	void SetTiles(const std::vector<Integrian2D::GameObject*>& tiles) noexcept;

	int GetTileIndex(const Integrian2D::GameObject* const pTile) const noexcept;
	int GetTileIndex(const TileComponent* const pTile) const noexcept;
	int GetRowNumber(const int index) const noexcept;
	int GetColumnNumber(const int index) const noexcept;
	TileComponent* const GetTileComponent(const Integrian2D::Point2f& pos) const noexcept;
	TileComponent* const GetTileComponent(const int index) const noexcept;
	const std::vector<Integrian2D::GameObject*>& GetTiles() const noexcept;
	PieceColour GetCurrentTurn() const noexcept;

	void ToggleIsLMBClicked(const std::string& file) noexcept;
	void ToggleIsRMBClicked(const std::string& file) noexcept;
	void ToggleIsEscapePressed(const std::string& file) noexcept;
	void EndTurn() noexcept;

private:
	Chessboard();

	inline static Chessboard* m_pInstance{};

	Integrian2D::Blackboard* m_pBlackboard;
	Integrian2D::FiniteStateMachine* m_pFSM;
	
	std::vector<Integrian2D::GameObject*> m_Tiles{};
	std::vector<Piece*> m_Pieces{};

	PieceColour m_Turn;
};