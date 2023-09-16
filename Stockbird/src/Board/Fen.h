#pragma once

#include "../Util/Util.h"
#include "Board.h"

class Fen
{
public:
	static void ReadFen(std::string fen, Board* board);
};