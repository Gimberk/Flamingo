#pragma once

#include "../Util/Util.h"
#include <map>

class Piece
{
	char identifier;
	std::vector<int> directions;

public:
	int index;
	int tileIndex;
	bool moved;
	bool color;
	int type;

	Piece()
	{
		moved = false;
		tileIndex = -1;
		identifier = ' ';
		index = -1;
		color = false;
		type = 0;
		directions = {};
	}

	Piece(int index, bool color, int type, char identifier, std::vector<int> directions, int tileIndex)
	{
		moved = false;
		this->index = index;
		this->color = color;
		this->type = type;
		this->identifier = identifier;
		this->directions = directions;
		this->tileIndex = tileIndex;
	}

	std::vector<int> GetDirections()
	{
		return directions;
	}

	char GetIdentifier() { return identifier; }

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

	Tile()
	{
		index = -1;
		occupied = false;
	}

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

class Move
{
public:
	int start;
	int end;

	int piece;
	int takenPiece;

	int castle;

	Move(int start, int end, int piece, int takenPiece, int castle = 0)
	{
		this->start = start;
		this->end = end;
		this->piece = piece;
		this->takenPiece = takenPiece;
		this->castle = castle;
	}

	bool Equals(Move other)
	{
		return other.end == end && other.start == start && other.piece == piece;
	}

	void ToString()
	{
		std::cout << start << std::endl;
		std::cout << end << std::endl;
		std::cout << piece << std::endl;
	}
};

class Board
{
	std::vector<Tile> tiles;
	std::map<int, Piece> pieces;

	bool turn = true;
public:
	enum PieceType
	{
		King = 0, Knight = 1, Queen = 2, Rook = 3, Bishop = 4
	};

	void PrintBoard();
	void PrintBoardWithMoves(std::vector<Move> moves);

	bool GetTurn() { return turn; }

	Piece PlacePiece(PieceType type, Tile *tile, bool color, char identifier);

	std::vector<Tile>* GetTiles() { return &tiles; }

	std::map<int, Piece>* GetPieces() { return &pieces; }

	bool Contains(int index);

	static std::vector<Tile> SetBoard();

	void MakeMove(Move move);
	void UnMakeMove(Move move);

	Piece GetWhiteKing();
	Piece GetBlackKing();

	Board() { tiles = SetBoard(); }
};