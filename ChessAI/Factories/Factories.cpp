#include "Factories.h"

#include <GameObject/GameObject.h>
#include <Core/Core.h>
#include <Components/TextureComponent/TextureComponent.h>
#include <TextureManager/TextureManager.h>
#include <Components/TransformComponent/TransformComponent.h>

#include "../TileComponent/TileComponent.h"
#include "../Piece/Pawn/Pawn.h"
#include "../Piece/Rook/Rook.h"
#include "../Piece/Bishop/Bishop.h"
#include "../Piece/Queen/Queen.h"
#include "../Piece/King/King.h"
#include "../Piece/Knight/Knight.h"

namespace Factories
{
	std::vector<Integrian2D::GameObject*> CreateChessboard() noexcept
	{
		using namespace Integrian2D;

		const TextureManager* const pTextureManager{ TextureManager::GetInstance() };

		/* Chessboard has 8x8 tiles */

		const Point2f windowDimensions{ static_cast<float>(Core::GetInstance()->GetWindowWidth()), static_cast<float>(Core::GetInstance()->GetWindowHeight()) };

		const Point2f tileDimensions{ windowDimensions.x / 8.f, windowDimensions.y / 8.f };

		std::vector<GameObject*> tiles{};

		int counter{};
		for (int y{}; y < 8; ++y)
		{
			for (int x{}; x < 8; ++x)
			{
				GameObject* pTile{ new GameObject{} };

				if (counter++ % 2 == 0)
					pTile->AddComponent(new TileComponent{ pTile, tileDimensions.x, tileDimensions.y, pTextureManager->GetTexture("WhiteTile") });
				else
					pTile->AddComponent(new TileComponent{ pTile, tileDimensions.x, tileDimensions.y, pTextureManager->GetTexture("BlackTile") });

				pTile->pTransform->SetPosition(Point2f{ x * tileDimensions.x, y * tileDimensions.y });

				tiles.push_back(pTile);
			}
			--counter;
		}

#pragma region Pawns
		{
			/* Add white pawns */
			Texture* const pWhitePawn{ pTextureManager->GetTexture("WhitePawn") };
			for (int i{ 8 }; i < 16; ++i)
			{
				tiles[i]->AddComponent(new Pawn{ tiles[i], pWhitePawn });
				tiles[i]->GetComponentByType<Pawn>()->SetColourOfPiece(PieceColour::White);
				tiles[i]->GetComponentByType<TileComponent>()->SetPiece(tiles[i]->GetComponentByType<Pawn>());
			}
		}

		{
			/* Add black pawns */
			Texture* const pBlackPawn{ pTextureManager->GetTexture("BlackPawn") };
			for (int i{ 48 }; i < 56; ++i)
			{
				tiles[i]->AddComponent(new Pawn{ tiles[i], pBlackPawn });
				tiles[i]->GetComponentByType<Pawn>()->SetColourOfPiece(PieceColour::Black);
				tiles[i]->GetComponentByType<TileComponent>()->SetPiece(tiles[i]->GetComponentByType<Pawn>());
			}
		}
#pragma endregion

#pragma region Rooks
		{
			/* Add White Rooks */
			Texture* const pWhiteRook{ pTextureManager->GetTexture("WhiteRook") };
			tiles[0]->AddComponent(new Rook{ tiles[0], pWhiteRook });
			tiles[0]->GetComponentByType<Rook>()->SetColourOfPiece(PieceColour::White);
			tiles[0]->GetComponentByType<TileComponent>()->SetPiece(tiles[0]->GetComponentByType<Rook>());

			tiles[7]->AddComponent(new Rook{ tiles[7], pWhiteRook });
			tiles[7]->GetComponentByType<Rook>()->SetColourOfPiece(PieceColour::White);
			tiles[7]->GetComponentByType<TileComponent>()->SetPiece(tiles[7]->GetComponentByType<Rook>());
		}

		{
			/* Add Black Rooks */
			Texture* const pBlackRook{ pTextureManager->GetTexture("BlackRook") };
			tiles[56]->AddComponent(new Rook{ tiles[56], pBlackRook });
			tiles[56]->GetComponentByType<Rook>()->SetColourOfPiece(PieceColour::Black);
			tiles[56]->GetComponentByType<TileComponent>()->SetPiece(tiles[56]->GetComponentByType<Rook>());

			tiles[63]->AddComponent(new Rook{ tiles[63], pBlackRook });
			tiles[63]->GetComponentByType<Rook>()->SetColourOfPiece(PieceColour::Black);
			tiles[63]->GetComponentByType<TileComponent>()->SetPiece(tiles[63]->GetComponentByType<Rook>());
		}
#pragma endregion

#pragma region Bishops
		{
			/* Add White Bishops */
			Texture* const pWhiteBishop{ pTextureManager->GetTexture("WhiteBishop") };
			tiles[2]->AddComponent(new Bishop{ tiles[2], pWhiteBishop });
			tiles[2]->GetComponentByType<Bishop>()->SetColourOfPiece(PieceColour::White);
			tiles[2]->GetComponentByType<TileComponent>()->SetPiece(tiles[2]->GetComponentByType<Bishop>());

			tiles[5]->AddComponent(new Bishop{ tiles[5], pWhiteBishop });
			tiles[5]->GetComponentByType<Bishop>()->SetColourOfPiece(PieceColour::White);
			tiles[5]->GetComponentByType<TileComponent>()->SetPiece(tiles[5]->GetComponentByType<Bishop>());
		}

		{
			/* Add Black Bishops */
			Texture* const pBlackBishop{ pTextureManager->GetTexture("BlackBishop") };
			tiles[58]->AddComponent(new Bishop{ tiles[58], pBlackBishop });
			tiles[58]->GetComponentByType<Bishop>()->SetColourOfPiece(PieceColour::Black);
			tiles[58]->GetComponentByType<TileComponent>()->SetPiece(tiles[58]->GetComponentByType<Bishop>());

			tiles[61]->AddComponent(new Bishop{ tiles[61], pBlackBishop });
			tiles[61]->GetComponentByType<Bishop>()->SetColourOfPiece(PieceColour::Black);
			tiles[61]->GetComponentByType<TileComponent>()->SetPiece(tiles[61]->GetComponentByType<Bishop>());
		}
#pragma endregion

#pragma region Knights
		{
			/* Add White Knights */
			Texture* const pWhiteKnight{ pTextureManager->GetTexture("WhiteKnight") };
			tiles[1]->AddComponent(new Knight{ tiles[1], pWhiteKnight });
			tiles[1]->GetComponentByType<Knight>()->SetColourOfPiece(PieceColour::White);
			tiles[1]->GetComponentByType<TileComponent>()->SetPiece(tiles[1]->GetComponentByType<Knight>());

			tiles[6]->AddComponent(new Knight{ tiles[6], pWhiteKnight });
			tiles[6]->GetComponentByType<Knight>()->SetColourOfPiece(PieceColour::White);
			tiles[6]->GetComponentByType<TileComponent>()->SetPiece(tiles[6]->GetComponentByType<Knight>());
		}

		{
			/* Add Black Knights */
			Texture* const pBlackKnight{ pTextureManager->GetTexture("BlackKnight") };
			tiles[57]->AddComponent(new Knight{ tiles[57], pBlackKnight });
			tiles[57]->GetComponentByType<Knight>()->SetColourOfPiece(PieceColour::Black);
			tiles[57]->GetComponentByType<TileComponent>()->SetPiece(tiles[57]->GetComponentByType<Knight>());

			tiles[62]->AddComponent(new Knight{ tiles[62], pBlackKnight });
			tiles[62]->GetComponentByType<Knight>()->SetColourOfPiece(PieceColour::Black);
			tiles[62]->GetComponentByType<TileComponent>()->SetPiece(tiles[62]->GetComponentByType<Knight>());
		}
#pragma endregion

#pragma region Queens
		{
			/* Add White Queen */
			Texture* const pWhiteQueen{ pTextureManager->GetTexture("WhiteQueen") };
			tiles[4]->AddComponent(new Queen{ tiles[4], pWhiteQueen });
			tiles[4]->GetComponentByType<Queen>()->SetColourOfPiece(PieceColour::White);
			tiles[4]->GetComponentByType<TileComponent>()->SetPiece(tiles[4]->GetComponentByType<Queen>());
		}

		{
			/* Add Black Queen */
			Texture* const pBlackQueen{ pTextureManager->GetTexture("BlackQueen") };
			tiles[60]->AddComponent(new Queen{ tiles[60], pBlackQueen });
			tiles[60]->GetComponentByType<Queen>()->SetColourOfPiece(PieceColour::Black);
			tiles[60]->GetComponentByType<TileComponent>()->SetPiece(tiles[60]->GetComponentByType<Queen>());
		}
#pragma endregion

#pragma region Kings
		{
			/* Add White King */
			Texture* const pWhiteKing{ pTextureManager->GetTexture("WhiteKing") };
			tiles[3]->AddComponent(new King{ tiles[3], pWhiteKing });
			tiles[3]->GetComponentByType<King>()->SetColourOfPiece(PieceColour::White);
			tiles[3]->GetComponentByType<TileComponent>()->SetPiece(tiles[3]->GetComponentByType<King>());
		}

		{
			/* Add Black King */
			Texture* const pBlackKing{ pTextureManager->GetTexture("BlackKing") };
			tiles[59]->AddComponent(new King{ tiles[59], pBlackKing });
			tiles[59]->GetComponentByType<King>()->SetColourOfPiece(PieceColour::Black);
			tiles[59]->GetComponentByType<TileComponent>()->SetPiece(tiles[59]->GetComponentByType<King>());
		}
#pragma endregion

		return tiles;
	}
}