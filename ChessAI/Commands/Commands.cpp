#include "Commands.h"

#include <Input/InputManager/InputManager.h>
#include <Renderer/Renderer.h>
#include <GameObject/GameObject.h>
#include <Components/TransformComponent/TransformComponent.h>

#include <algorithm>

#include "../TileComponent/TileComponent.h"
#include "../Chessboard/Chessboard.h"
#include "../Piece/Piece.h"

namespace Commands
{
	LeftClickChessboardCommand::LeftClickChessboardCommand(Integrian2D::Scene* const pScene)
		: Command{ pScene }
	{}

	void LeftClickChessboardCommand::Execute()
	{
		Chessboard::GetInstance()->ToggleIsLMBClicked(__FILE__);
	}

	RightClickChessboardCommand::RightClickChessboardCommand(Integrian2D::Scene* const pScene)
		: Command{ pScene }
	{}

	void RightClickChessboardCommand::Execute()
	{
		Chessboard::GetInstance()->ToggleIsRMBClicked(__FILE__);
	}

	EscapePressedCommand::EscapePressedCommand(Integrian2D::Scene* const pScene)
		: Command{ pScene }
	{}

	void EscapePressedCommand::Execute()
	{
		Chessboard::GetInstance()->ToggleIsEscapePressed(__FILE__);
	}
}