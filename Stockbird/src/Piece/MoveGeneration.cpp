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

		Tile tile = (*board.GetTiles())[index];

		std::cout << "Tile Exists: " << std::to_string(index) << std::endl;
		Move move((*board.GetTiles())[piece.tileIndex], tile, piece, (*tile.GetPiece()));
		legalMoves.push_back(move);
	}
	return legalMoves;
}

bool MoveGeneration::Contains(int index, std::vector<Move> moves)
{
	for (Move move : moves) if (move.end.GetIndex() == index) return true;
	return false;
}