#pragma once

#include <vector>

namespace Integrian2D
{
	class GameObject;
}

namespace Factories
{
	/* [TODO] Finish function when Pieces are implemented */
	[[nodiscard]] std::vector<Integrian2D::GameObject*> CreateChessboard() noexcept;
}