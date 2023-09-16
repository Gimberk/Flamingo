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
	system("cls");

	std::string board;

	int file = 0;
	for (Tile tile : tiles)
	{
		if (file > 7)
		{
			file = 0;
			board += "\n";
		}
		board += tile.ToString();
		board += " ";
		file++;
	}

	std::cout << board << std::endl;
}

/// <summary>
/// Prints the board to the console with moves being highlighted
/// </summary>
/// <param name="moves"></param>
void Board::PrintBoardWithMoves(std::vector<Move> moves)
{
	system("cls");

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

	if (type == King)
	{
		directions = { -9, -8, -7, -1, 1, 7, 8, 9 };
	}

	Piece piece(0, color, type, identifier, directions, tile->GetIndex());
	(*tile->GetPiece()) = piece;
	tile->occupied = true;

	pieces.push_back(piece);
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