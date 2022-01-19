#pragma once

#include <vector>

namespace Integrian2D
{
	class GameObject;
}

class GameInformation final
{
public:
	static GameInformation* const GetInstance() noexcept;
	static void Cleanup() noexcept;

	void SetTiles(const std::vector<Integrian2D::GameObject*>& tiles) noexcept;

	const std::vector<Integrian2D::GameObject*>& GetTiles() const noexcept;

private:
	GameInformation() = default;

	inline static GameInformation* m_pInstance{};

	std::vector<Integrian2D::GameObject*> m_Tiles{};
};