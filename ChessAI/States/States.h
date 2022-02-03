#pragma once

#include <AI/Blackboard/Blackboard.h>
#include <AI/DecisionMaking/FiniteStateMachine/FiniteStateMachine.h>

namespace States
{
	Integrian2D::BehaviourState NoUserInput(Integrian2D::Blackboard* const pBlackboard);
	Integrian2D::BehaviourState UserRightClick(Integrian2D::Blackboard* const pBlackboard);
}

namespace Transitions
{
	bool HasUserRightClicked(Integrian2D::Blackboard* const pBlackboard);
}

/*

Chessboard FSM: 
                                             ┌────────────┐
                           WasPieceMoved     │            │
                      ┌──────────────────────┤ MovePiece  │
                      │                      │            │
                      │                      └────────────┘
                      │                              ▲
                      │                              │
                      │                              │ HasUserLeftClicked
                      ▼                              │
                ┌───────────────┐             ┌──────┴──────┐
                │               │HasUserLeftCl│             │
                │  NoUserInput  ├────────────►│ SelectPiece │
                │               │             │             │
                └───────┬───────┘             └─────────────┘
                     ▲  │                                ▲
                     │  │                                │
  HasUserRightClicked│  │HasUserRightClicked             │
                     │  │                                │
                     │  ▼                                │
                ┌────┴──────────────────┐                │
                │                       │                │
                │  RenderPossibleMoves  ├────────────────┘
                │                       │ HasUserLeftClicked
                └───────────────────────┘
*/