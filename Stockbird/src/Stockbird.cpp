#include "Util/Util.h"
#include "Board/Board.h"
#include "Board/Fen.h"
#include "Piece/MoveGeneration.h"

#include <cstdlib>

using namespace std;

//const string baseFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
const string baseFen = "8/8/8/K";

int main()
{
	Board board;
	Fen::ReadFen(baseFen, &board);
	//board.PrintBoard();
	Piece piece = (*board.GetPieces())[0];
	vector<Move> moves = MoveGeneration::GeneratePsuedoLegalMoves(piece, board);
	board.PrintBoardWithMoves(moves);

#ifdef NDEBUG
	system("pause");
#endif
	return 0;
}