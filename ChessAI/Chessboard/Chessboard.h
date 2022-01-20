#pragma once

#include <Math/TypeDefines.h>

#include <vector>

namespace Integrian2D
{
	class GameObject;
}

class TileComponent;
class Piece;

class Chessboard final
{
public:
	static Chessboard* const GetInstance() noexcept;
	static void Cleanup() noexcept;

	~Chessboard() = default;

	void SetTiles(const std::vector<Integrian2D::GameObject*>& tiles) noexcept;

	int GetTileIndex(const Integrian2D::GameObject* const pTile) const noexcept;
	int GetTileIndex(const TileComponent* const pTile) const noexcept;
	int GetRowNumber(const int index) const noexcept;
	int GetColumnNumber(const int index) const noexcept;
	TileComponent* const GetTileComponent(const Integrian2D::Point2f& pos) const noexcept;
	TileComponent* const GetTileComponent(const int index) const noexcept;
	const std::vector<Integrian2D::GameObject*>& GetTiles() const noexcept;

private:
	Chessboard() = default;

	inline static Chessboard* m_pInstance{};

	std::vector<Integrian2D::GameObject*> m_Tiles{};
};