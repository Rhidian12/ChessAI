#include "Chessboard.h"

#include <Utils/Utils.h>

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

void Chessboard::SetTiles(const std::vector<Integrian2D::GameObject*>& tiles) noexcept
{
    m_Tiles = tiles;
}

const std::vector<Integrian2D::GameObject*>& Chessboard::GetTiles() const noexcept
{
    return m_Tiles;
}
