#pragma once

#include <AI/DecisionMaking/FiniteStateMachine/FiniteStateMachine.h>

namespace Integrian2D
{
    class Blackboard;
}

namespace States
{
	Integrian2D::BehaviourState NoUserInput(Integrian2D::Blackboard* const pBlackboard);
	Integrian2D::BehaviourState UserRightClick(Integrian2D::Blackboard* const pBlackboard);
    Integrian2D::BehaviourState SelectPiece(Integrian2D::Blackboard* const pBlackboard);
    Integrian2D::BehaviourState MovePiece(Integrian2D::Blackboard* const pBlackboard);
}

namespace Transitions
{
	bool HasUserRightClicked(Integrian2D::Blackboard* const pBlackboard);
	bool HasUserLeftClicked(Integrian2D::Blackboard* const pBlackboard);
	bool HasPieceBeenSelectedAndHasUserLeftClicked(Integrian2D::Blackboard* const pBlackboard);
	bool WasPieceMoved(Integrian2D::Blackboard* const pBlackboard);
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
                      │                              │ HasPieceBeenSelected && HasUserLeftClicked
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