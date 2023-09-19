#pragma once

#include "../Util/Util.h"
#include "../Board/Board.h"

class MoveGeneration
{
	static std::vector<Move> GenerateKingMoves(Piece piece, Board board);
	static std::vector<Move> GenerateKnightMoves(Piece piece, Board board);
	static std::vector<Move> GenerateSlidingMoves(Piece piece, Board board);
public:
	static bool Contains(int index, std::vector<Move> moves);
	static std::vector<Move> GeneratePsuedoLegalMoves(Piece piece, Board board);
};