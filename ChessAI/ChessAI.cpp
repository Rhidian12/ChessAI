#include <Core/Core.h>
#include <SceneManager/SceneManager.h>

#include "Scenes/ChessScene.h"

int main()
{
    using namespace Integrian2D;

    Core* pCore{ Core::CreateEngine(720, 720, "ChessAI") };

    SceneManager::GetInstance()->AddScene(new ChessScene{ "ChessScene" });

    pCore->Run();

    pCore->Cleanup();

    return 0;
}