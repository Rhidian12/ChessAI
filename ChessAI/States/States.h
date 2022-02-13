#pragma once

/* BehaviourState */
#include <AI/DecisionMaking/FiniteStateMachine/FiniteStateMachine.h>

namespace Integrian2D
{
    class Blackboard;
}

class TileComponent;
class Piece;

namespace HelperFunctions
{
    void TakePiece(TileComponent* const pClickedTile, Piece* const pSelectedPiece);
	bool IsMoveResultingInCheck(Integrian2D::Blackboard* const pBlackboard);
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
    bool WasEscapePressed(Integrian2D::Blackboard* const pBlackboard);
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
    EscapePressed     │  NoUserInput  ├────────────►│ SelectPiece │
  ┌──────────────────►│               │             │             │
  │                   └───────┬───────┘◄────────────┴─────────────┘
  │                        ▲  │         EscapePressed          ▲
  │                        │  │                                │
  │     HasUserRightClicked│  │HasUserRightClicked             │
  │                        │  │                                │
  │                        │  ▼                                │
  │                   ┌────┴──────────────────┐                │
  │                   │                       │                │
  │                   │  RenderPossibleMoves  ├────────────────┘
  └───────────────────┤                       │ HasUserLeftClicked
                      └───────────────────────┘
*/