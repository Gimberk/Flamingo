#include "Util/Util.h"
#include "Board/Board.h"
#include "Board/Fen.h"
#include "Piece/MoveGeneration.h"

#include<string>
#include <cstdlib>
using namespace std;

//const string baseFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
const string baseFen = "8/8/8/5Kk";

string title;

Move ParseNotation(string n, Board *board)
{
	/*
		These are the lengths of the different algebraic notations:
		1. Qe4
		2. Qxe4
		3. Qa4xe4
		4. Qa4e4
	*/
	const int t1 = 3;
	const int t2 = 4;
	const int t3 = 6;
	const int t4 = 5;
	int t = -1;

	// We need to determine the type of the notation based on the length of it:
	switch (n.size())
	{
	case t1:
		t = t1;
		break;
	case t2:
		t = t2;
		break;
	case t3:
		t = t3;
		break;
	case t4:
		t = t4;
		break;
	}

	std::vector<Piece> possibilities;

	char identifier = n[0];

	for (pair<int, Piece> pie : (*board->GetPieces())) if (pie.second.GetIdentifier() == identifier) possibilities.push_back(pie.second);

	if (t == t1)
	{
		int end = ParseSquare(n.substr(1));
		if (end == -1)
		{
			return Move(-1, -1, -1, -1);
		}

		if (possibilities.size() > 1 || possibilities.size() < 1)
		{
			cout << "Invalid Algebraic Notation" << endl;
			return Move(-1, -1, -1, -1);
		}

		if ((*board->GetTiles())[end].GetPiece()->tileIndex != -1)
		{
			cout << "Invalid Algebraic Notation" << endl;
			return Move(-1, -1, -1, -1);
		}

		Move ourMove = Move(possibilities[0].tileIndex, end, possibilities[0].index, -1);

		for (Move move : MoveGeneration::GeneratePsuedoLegalMoves(possibilities[0], (*board))) if (move.Equals(ourMove)) return ourMove;

		cout << "Illegal Move" << endl;
		return Move(-1, -1, -1, -1);
	}
	else if (t == t2)
	{
		int end = ParseSquare(n.substr(1));
		if (end == -1)
		{
			return Move(-1, -1, -1, -1);
		}

		if (possibilities.size() > 1 || possibilities.size() < 1)
		{
			cout << "Invalid Algebraic Notation" << endl;
			return Move(-1, -1, -1, -1);
		}

		if ((*board->GetTiles())[end].GetPiece()->tileIndex == -1)
		{
			cout << "Invalid Algebraic Notation" << endl;
			return Move(-1, -1, -1, -1);
		}

		Move ourMove = Move(possibilities[0].tileIndex, end, possibilities[0].index, (*board->GetTiles())[end].GetPiece()->index);

		for (Move move : MoveGeneration::GeneratePsuedoLegalMoves(possibilities[0], (*board))) if (move.Equals(ourMove)) return ourMove;

		cout << "Illegal Move" << endl;
		return Move(-1, -1, -1, -1);
	}

	cout << "Invalid Algebraic Notation" << endl;
	return Move(-1, -1, -1, -1);
}

int main()
{
	PrintTitle();

	Board board;
	Fen::ReadFen(baseFen, &board);
	board.PrintBoard();

	while (true)
	{
		cout << endl << "Enter Your Move: ";
		string input;
		cin >> input;
		Move move = ParseNotation(input, &board);
		if (move.end == -1) continue;
		cout << "Your Move End Destination Is: " << move.end << endl;
		cout << "Your Move Start Destination Is: " << move.start << endl;
		cout << "Your Move Piece Is: " << move.piece << endl;
		cout << "Your Move Taken Piece Is: " << move.takenPiece << endl;
		board.MakeMove(move);
	}

#ifdef NDEBUG
	system("pause");
#endif
	return 0;
}