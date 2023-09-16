#include "Util/Util.h"
#include "Board/Board.h"
#include "Board/Fen.h"
#include <cstdlib>

using namespace std;

//const string baseFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
const string baseFen = "4K";

int main()
{
	Board board;
	ReadFen(baseFen, &board);
	board.PrintBoard();

#ifdef NDEBUG
	system("pause");
#endif
	return 0;
}