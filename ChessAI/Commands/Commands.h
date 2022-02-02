#pragma once

#include <Command/Command.h>

namespace Commands
{
	class ClickChessboardCommand final : public Integrian2D::Command
	{
	public:
		ClickChessboardCommand(Integrian2D::Scene* const pScene);

		virtual void Execute() override;
	};
}