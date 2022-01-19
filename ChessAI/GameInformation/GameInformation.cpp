#include "GameInformation.h"

#include <Utils/Utils.h>

GameInformation* const GameInformation::GetInstance() noexcept
{
    if (!m_pInstance)
        m_pInstance = new GameInformation{};

    return m_pInstance;
}

void GameInformation::Cleanup() noexcept
{
    Integrian2D::Utils::SafeDelete(m_pInstance);
}

void GameInformation::SetTiles(const std::vector<Integrian2D::GameObject*>& tiles) noexcept
{
    m_Tiles = tiles;
}

const std::vector<Integrian2D::GameObject*>& GameInformation::GetTiles() const noexcept
{
    return m_Tiles;
}
