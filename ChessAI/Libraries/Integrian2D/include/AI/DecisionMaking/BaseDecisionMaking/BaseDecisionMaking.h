#pragma once

#include "../../../Integrian2D_API.h"
#include "../../BehaviourState.h"

namespace Integrian2D
{
	class AIComponent;
	class Blackboard;

	class INTEGRIAN2D_API BaseDecisionMaking
	{
	public:
		BaseDecisionMaking();
		virtual ~BaseDecisionMaking() = default;

		virtual BaseDecisionMaking* Clone() noexcept = 0;

		virtual BehaviourState Update(Blackboard* const) = 0;

		BehaviourState GetCurrentState() const noexcept;

	protected:
		BehaviourState m_CurrentState;
	};
}