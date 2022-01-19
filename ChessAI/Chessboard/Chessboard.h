#pragma once

#include <vector>

namespace Integrian2D
{
	class GameObject;
}

class Chessboard final
{
public:
	static Chessboard* const GetInstance() noexcept;
	static void Cleanup() noexcept;

	void SetTiles(const std::vector<Integrian2D::GameObject*>& tiles) noexcept;

	const std::vector<Integrian2D::GameObject*>& GetTiles() const noexcept;

private:
	Chessboard() = default;

	inline static Chessboard* m_pInstance{};

	std::vector<Integrian2D::GameObject*> m_Tiles{};
};