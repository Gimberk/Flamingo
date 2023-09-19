#include <string>
#include <stdlib.h>
#include <algorithm>

#include "../Piece/MoveGeneration.h"
#include "Board.h"

/// <summary>
/// Initializes the board; Assigns indices
/// </summary>
/// <returns></returns>
std::vector<Tile> Board::SetBoard()
{
	std::vector<Tile> tiles;
	for (int i = 0; i < 64; i++)
	{
		Tile tile(i);
		tiles.push_back(tile);
	}
	return tiles;
}

/// <summary>
/// Prints the board to the console
/// </summary>
void Board::PrintBoard()
{
	//system("cls");

	std::string board;

	int file = 0;
	int index = 7;
	board += "8 ";
	for (Tile tile : tiles)
	{
		if (file > 7)
		{
			file = 0;
			board += "\n";
			board += std::to_string(index) + " ";
			index--;
		}
		board += tile.ToString();
		//board += std::to_string(tile.GetIndex());
		board += " ";
		file++;
	}

	board += "\n  a b c d e f g h";

	std::cout << board << std::endl << std::endl;
}

/// <summary>
/// Prints the board to the console with moves being highlighted
/// </summary>
/// <param name="moves"></param>
void Board::PrintBoardWithMoves(std::vector<Move> moves)
{
	//system("cls");

	std::string board;

	int file = 0;
	for (Tile tile : tiles)
	{
		if (file > 7)
		{
			file = 0;
			board += "\n";
		}

		if (MoveGeneration::Contains(tile.GetIndex(), moves)) board += "@";
		else board += tile.ToString();

		//board += std::to_string(tile.GetIndex());

		board += " ";
		file++;
	}

	std::cout << board << std::endl;
}

/// <summary>
/// Places a piece respective to the type and color on the specified tile
/// </summary>
/// <param name="type"></param>
/// <param name="tile"></param>
/// <param name="color"></param>
/// <param name="identifier"></param>
/// <returns></returns>
Piece Board::PlacePiece(Board::PieceType type, Tile *tile, bool color, char identifier)
{
	std::vector<int> directions;

	if (type == King) directions = { -9, -8, -7, -1, 1, 7, 8, 9 };
	else if (type == Knight) directions = { -17, -15, -10, -6, 6, 10, 15, 17 };
	else if (type == Queen) directions = { -9, -8, -7, -1, 1, 7, 8, 9 };
	else if (type == Rook) directions = { -8, -1, 1, 8 };
	else if (type == Bishop) directions = { -9, -7, 7, 9 };

	Piece piece(static_cast<int>(pieces.size()), color, type, identifier, directions, tile->GetIndex());
	(*tile->GetPiece()) = piece;
	tile->occupied = true;

	pieces.insert(pieces.begin(), std::pair<int, Piece>(pieces.size(), piece));
	return piece;

}

/// <summary>
/// Checks to see if the index exists in the tile vector
/// </summary>
/// <param name="index"></param>
/// <returns>True if it is a valid index</returns>
bool Board::Contains(int index)
{
	for (Tile t : tiles)
		if (t.GetIndex() == index) return true;
	return false;
}

void Board::MakeMove(Move move)
{
	if (pieces[move.piece].color != turn)
	{
		std::cout << "Not your turn!" << std::endl;
		return;
	}

	tiles[move.start].occupied = false;
	(*tiles[move.start].GetPiece()) = Piece();
	tiles[move.end].occupied = true;
	(*tiles[move.end].GetPiece()) = pieces[move.piece];

	pieces[move.piece].tileIndex = move.end;
	pieces[move.piece].moved = true;

	if (move.castle == 1)
	{
		int rookTile = static_cast<std::vector<Tile, std::allocator<Tile>>::size_type>(move.start) + 3;
		int rook = tiles[rookTile].GetPiece()->index;
		(*tiles[move.start + 1].GetPiece()) = pieces[tiles[rookTile].GetPiece()->index];
		tiles[rookTile].occupied = false;
		(*tiles[rookTile].GetPiece()) = Piece();

		tiles[move.start + 1].occupied = true;

		pieces[rook].tileIndex = move.start + 1;
		pieces[rook].moved = true;
	}
	else if (move.castle == 2)
	{
		int rookTile = static_cast<std::vector<Tile, std::allocator<Tile>>::size_type>(move.start) - 4;
		int rook = tiles[rookTile].GetPiece()->index;
		(*tiles[move.start - 1].GetPiece()) = pieces[tiles[rookTile].GetPiece()->index];
		tiles[rookTile].occupied = false;
		(*tiles[rookTile].GetPiece()) = Piece();

		tiles[move.start - 1].occupied = true;


		pieces[rook].tileIndex = move.start -1;
		pieces[rook].moved = true;
	}

	// There was a taken piece
	if (move.takenPiece != -1)
	{
		pieces[move.takenPiece].moved = true;
		pieces.erase(move.takenPiece);
	}

	turn = !turn;

	system("cls");
	PrintTitle();
	PrintBoard();
}

void Board::UnMakeMove (Move move)
{

}

Piece Board::GetWhiteKing()
{
	for (std::pair<int, Piece> pair : pieces)
	{
		Piece piece = pair.second;
		if (piece.GetIdentifier() == 'K') return piece;
	}
	return Piece();
}

Piece Board::GetBlackKing()
{
	for (std::pair<int, Piece> pair : pieces)
	{
		Piece piece = pair.second;
		if (piece.GetIdentifier() == 'k') return piece;
	}
	return Piece();
}