#include "MoveGeneration.h"
#include <string>

std::vector<Move> MoveGeneration::GeneratePsuedoLegalMoves(Piece piece, Board board)
{
	std::vector<Move> legalMoves = GenerateKingMoves(piece, board);

	return legalMoves;
}

std::vector<Move> MoveGeneration::GenerateKingMoves(Piece piece, Board board)
{
	std::vector<Move> legalMoves;

	for (int dir : piece.GetDirections())
	{
		int index = piece.tileIndex + dir;
		if (!board.Contains(index)) continue;

		if (IsFirstRank(piece.tileIndex))
		{
			if (dir == 7 || dir == -1 || dir == -9) continue;
		}

		if (IsEighthRank(piece.tileIndex))
		{
			if (dir == -7 || dir == 1 || dir == 9) continue;
		}

		Tile tile = (*board.GetTiles())[index];

		if (tile.occupied)
		{
			if (tile.GetPiece()->color == piece.color) continue;
		}

		Move move(piece.tileIndex, tile.GetIndex(), piece.index, tile.GetPiece()->index);
		legalMoves.push_back(move);
	}
	return legalMoves;
}

bool MoveGeneration::Contains(int index, std::vector<Move> moves)
{
	for (Move move : moves) if (move.end == index) return true;
	return false;
}