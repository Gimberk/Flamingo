#include "MoveGeneration.h"
#include <string>

std::vector<Move> MoveGeneration::GeneratePsuedoLegalMoves(Piece piece, Board board)
{
	std::vector<Move> legalMoves;

	if (piece.type == Board::King) legalMoves = GenerateKingMoves(piece, board);
	else if (piece.type == Board::Knight) legalMoves = GenerateKnightMoves(piece, board);
	else if (piece.type == Board::Queen || piece.type == Board::Bishop 
		|| piece.type == Board::Rook) legalMoves = GenerateSlidingMoves(piece, board);

	return legalMoves;
}

std::vector<Move> MoveGeneration::GenerateKingMoves(Piece piece, Board board)
{
	std::vector<Move> legalMoves;

	if (!piece.moved)
	{
		Tile rookK = (*board.GetTiles())[piece.tileIndex + 3];
		if (!rookK.GetPiece()->moved)
		{
			Tile bishop = (*board.GetTiles())[piece.tileIndex + 1], knight = (*board.GetTiles())[piece.tileIndex + 2];
			if (!bishop.occupied && !knight.occupied) legalMoves.push_back(Move(piece.tileIndex, knight.GetIndex(), piece.index, -1, 1));
		}

		Tile rookQ = (*board.GetTiles())[piece.tileIndex - 4];
		if (!rookQ.GetPiece()->moved)
		{
			Tile bishop = (*board.GetTiles())[piece.tileIndex - 2], knight = (*board.GetTiles())[piece.tileIndex - 3];
			Tile queen = (*board.GetTiles())[piece.tileIndex - 1];
			if (!bishop.occupied && !knight.occupied
				&& !queen.occupied) legalMoves.push_back(Move(piece.tileIndex, bishop.GetIndex(), piece.index, -1, 2));
		}
	}

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

std::vector<Move> MoveGeneration::GenerateKnightMoves(Piece piece, Board board)
{
	std::vector<Move> legalMoves;

	for (int dir : piece.GetDirections())
	{
		int index = piece.tileIndex + dir;
		if (!board.Contains(index)) continue;

		if (IsFirstRank(piece.tileIndex))
		{
			if (dir == 15 || dir == 6 || dir == -10 || dir == -17) continue;
		}
		else if (IsEighthRank(piece.tileIndex))
		{
			if (dir == -15 || dir == -6 || dir == 10 || dir == 17) continue;
		}
		else if (IsSecondRank(piece.tileIndex))
		{
			if (dir == 6 || dir == -10) continue;
		}
		else if (IsSeventhRank(piece.tileIndex))
		{
			if (dir == -6 || dir == 10) continue;
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

std::vector<Move> MoveGeneration::GenerateSlidingMoves(Piece piece, Board board)
{
	std::vector<Move> legalMoves;

	int start = piece.tileIndex;
	bool left = IsFirstRank(start);
	bool right = IsEighthRank(start);
	for(int dir : piece.GetDirections())
	{
		if (dir == 9 || dir == 1 || dir == -7)
		{
			if (right) continue;
		}
		else if (dir == -1 || dir == 7 || dir == -9)
		{
			if (left) continue;
		}
		int index = piece.tileIndex + dir;
		while (board.Contains(index))
		{
			Tile tile = (*board.GetTiles())[index];
			if (tile.GetPiece()->tileIndex != -1)
			{
				if (tile.GetPiece()->color == piece.color) break;
				else
				{
					legalMoves.push_back(Move(start, index, piece.index, tile.GetPiece()->index));
					break;
				}
			}
			legalMoves.push_back(Move(start, index, piece.index, tile.GetPiece()->index));
			if (dir == 9 || dir == 1 || dir == -7)
			{
				if (IsEighthRank(index)) break;
			}
			else if (dir == -1 || dir == 7 || dir == -9)
			{
				if (IsFirstRank(index)) break;
			}
			index += dir;
		}
	}

	return legalMoves;
}

bool MoveGeneration::Contains(int index, std::vector<Move> moves)
{
	for (Move move : moves) if (move.end == index) return true;
	return false;
}