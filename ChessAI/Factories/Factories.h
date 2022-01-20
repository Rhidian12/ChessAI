#pragma once

#include <vector>

namespace Integrian2D
{
	class GameObject;
}

namespace Factories
{
	[[nodiscard]] std::vector<Integrian2D::GameObject*> CreateChessboard() noexcept;
}