#include <map>
#include <string>
#include <cctype>
#include <cstring>

#include "Fen.h"

/// <summary>
/// Reads a fen and places pieces on the board
/// </summary>
/// <param name="fen"></param>
void ReadFen(std::string fen, Board *board)
{
	std::vector<std::string> fenParts = Split(fen, ' ');
	std::string base = fenParts[0];

    std::map<char, Board::PieceType> pieces{ {'k', Board::King} };

    int file = 0, rank = 0;

    for(char symbol : base)
    {
        if (symbol == '/')
        {
            file = 0;
            rank++;
        }
        else
        {
            if (std::isdigit(symbol))
                file += std::stoi(std::string(1, symbol));
            else
            {
                int index = rank * 8 + file;

                bool pieceColor = isupper(symbol);
                Board::PieceType type = pieces[tolower(symbol)];

                board->PlacePiece(type, &(*board->GetTiles())[index], pieceColor, symbol);
                file++;
            }
        }
    }
}