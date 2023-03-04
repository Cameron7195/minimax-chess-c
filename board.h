#include <stdint.h>

struct {
   int8_t valid;
   int8_t from;
   int8_t to;

   int8_t castle;
   int8_t passingL;
   int8_t passingR;
   int8_t queen;
   int8_t taking;
} typedef move;

typedef struct board {
   uint8_t store[64];


   uint8_t wCastleL;
   uint8_t wCastleR;
   uint8_t bCastleL;
   uint8_t bCastleR;

   uint8_t wHasCastled;
   uint8_t bHasCastled;

   uint8_t wPawns[8];
   uint8_t bPawns[8];

   uint8_t turn;
   int turnNumber;

   uint8_t gameState;

   move previousMove;
   struct board *previousBoard;

} board;
/*
struct {
   int valid;
   int from;
   int to;

   int castle;
   int passingL;
   int passingR;
   int queen;
   int taking;
} typedef move;
*/
typedef struct PVTree {
   int score;
   int size;
   move m;
   struct PVTree *children;
} PVTree;

board init(void);
int printBoard(board b, uint8_t flipped);
move *genLegalMoves(board b, int *size);
move *genLegalMoves_unsorted(board b, int *size);
move *efficientGenMoves(board b, int *size);
int sortMoves(board b, move **moves, int size);
move *genAllMoves(board b, int *size, int stopRecur);
move *genPieceMoves(board b, int index, int *size, int stopRecur);
int isMoveSafe(board b, move m);
move *pawnLegal(board b, int index, int pawnIdx, int *size);
move *knightLegal(board b, int index, int *size);
move *bishopLegal(board b, int index, int *size);
move *rookLegal(board b, int index, int *size);
move *queenLegal(board b, int index, int *size);
move *kingLegal(board b, int index, int *size, int stopRecur);
move minimax(board b, int bestScoreFound, int player, int depth, int *scoreReturn, PVTree *currentNode);
move *sortFromNode(PVTree *children, int size, int player);
PVTree pvInit();
PVTree *pvArrInit(int size);
PVTree *cleanUpTree(PVTree *node, move m);
void freeAll(PVTree *node);


