#pragma once

#include <Command/Command.h>

namespace Commands
{
	class LeftClickChessboardCommand final : public Integrian2D::Command
	{
	public:
		LeftClickChessboardCommand(Integrian2D::Scene* const pScene);

		virtual void Execute() override;
	};

	class RightClickChessboardCommand final : public Integrian2D::Command
	{
	public:
		RightClickChessboardCommand(Integrian2D::Scene* const pScene);

		virtual void Execute() override;
	};
}