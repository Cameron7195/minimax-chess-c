move movePerson(board b);
int printMoves(board b, move *moves, int from, int size);
int movePiece(board *b, move m, uint8_t saveBoardHistory);
int undoMove(board *b);