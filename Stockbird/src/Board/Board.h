#pragma once

#include "../Util/Util.h"

class Piece
{
	char identifier;
	std::vector<int> directions;

public:
	int index;
	bool color;
	int type;

	Piece()
	{
		identifier = ' ';
		index = -1;
		color = false;
		type = 0;
		directions = {};
	}

	Piece(int index, bool color, int type, char identifier, std::vector<int> directions)
	{
		this->index = index;
		this->color = color;
		this->type = type;
		this->identifier = identifier;
		this->directions = directions;
	}

	std::vector<int> GetDirections()
	{
		return directions;
	}

	char ToString()
	{
		return identifier;
	}
};

class Tile
{
	Piece piece;
	int index;
public:
	bool occupied;
	Tile(int index)
	{
		this->index=index;
		occupied = false;
	}

	Tile(int index, Piece piece)
	{
		this->index = index;
		this->piece = piece;

		occupied = true;
	}

	int GetIndex() { return index; }

	Piece* GetPiece() { return &piece; }

	char ToString()
	{
		return occupied ? piece.ToString() : '-';
	}
};

class Board
{
	std::vector<Tile> tiles;
	std::vector<Piece> pieces;
public:
	enum PieceType
	{
		King = 0
	};

	void PrintBoard();
	Piece PlacePiece(PieceType type, Tile *tile, bool color, char identifier);

	std::vector<Tile>* GetTiles() { return &tiles; }

	static std::vector<Tile> SetBoard();

	Board() { tiles = SetBoard(); }
};