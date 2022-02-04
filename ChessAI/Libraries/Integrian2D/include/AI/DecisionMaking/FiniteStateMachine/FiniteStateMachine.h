#pragma once

#include "../../../Integrian2D_API.h"
#include "../BaseDecisionMaking/BaseDecisionMaking.h"

#include <functional>
#include <vector>

namespace Integrian2D
{
	class FiniteStateMachine;

	class FSMState final : public BaseDecisionMaking
	{
	public:
		using Action = std::function<BehaviourState(Blackboard* const)>;

		INTEGRIAN2D_API FSMState(FiniteStateMachine* const pFSM, const Action& action);

		INTEGRIAN2D_API virtual BaseDecisionMaking* Clone() noexcept override;

		INTEGRIAN2D_API virtual BehaviourState Update(Blackboard* const pBlackboard) override;

		INTEGRIAN2D_API FiniteStateMachine* const GetFiniteStateMachine() const noexcept;
		INTEGRIAN2D_API const Action& GetAction() const noexcept;

	private:
		FiniteStateMachine* m_pFSM;
		Action m_Action;
	};

	class Transition final
	{
	public:
		using Predicate = std::function<bool(Blackboard* const)>;

		INTEGRIAN2D_API Transition(FiniteStateMachine* const pFSM, FSMState* const pFrom, FSMState* const pTo, const Predicate& predicate);

		INTEGRIAN2D_API Transition* Clone() noexcept;

		INTEGRIAN2D_API bool Update(Blackboard* const pBlackboard);

		INTEGRIAN2D_API FiniteStateMachine* const GetFiniteStateMachine() const noexcept;
		INTEGRIAN2D_API FSMState* const GetFrom() const noexcept;
		INTEGRIAN2D_API FSMState* const GetTo() const noexcept;

	private:
		FiniteStateMachine* m_pFSM;
		Predicate m_Predicate;
		FSMState* m_pFrom;
		FSMState* m_pTo;
	};

	class FiniteStateMachine final : public BaseDecisionMaking
	{
	public:
		INTEGRIAN2D_API FiniteStateMachine(BaseDecisionMaking* const pStartState);
		INTEGRIAN2D_API virtual ~FiniteStateMachine() override;

		INTEGRIAN2D_API FiniteStateMachine(const FiniteStateMachine& other) noexcept;
		INTEGRIAN2D_API FiniteStateMachine(FiniteStateMachine&& other) noexcept;
		INTEGRIAN2D_API FiniteStateMachine& operator=(const FiniteStateMachine& other) noexcept;
		INTEGRIAN2D_API FiniteStateMachine& operator=(FiniteStateMachine&& other) noexcept;

		virtual BaseDecisionMaking* Clone() noexcept override;

		INTEGRIAN2D_API void AddState(FSMState* const pState) noexcept;
		INTEGRIAN2D_API void AddTransition(Transition* const pTransition) noexcept;

		INTEGRIAN2D_API virtual BehaviourState Update(Blackboard* const pBlackboard) override;

	private:
		std::vector<BaseDecisionMaking*> m_pStates;
		std::vector<Transition*> m_pTransitions;

		BaseDecisionMaking* m_pCurrentState;
	};
}