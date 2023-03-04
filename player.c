#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "board.c"
#include "minimax.c"
#include <time.h>
#include "pv.c"

/* Find some creative way of storing the best moves already generated, for the next run. */

//static int totalNodes = 0;
//static int totalLeaves = 0;

int main(void) {
   board b = init();
   move *moves = (move *)malloc(137*sizeof(move));
   move *first;
   move undo = {-1,-1,-1,-1,-1,-1,-1,-1};
   int assign = 1;
   int size;
   int i;
   int best;
   int moveNum = 1;
   int player = 10;
   uint8_t boardIsFlipped = 0;
   char (key[])[10] = {"Pawn", "Knight", "Bishop", "Rook", "Queen", "King"};
   PVTree initNode = pvInit();
   PVTree *root = &initNode;
   moves = efficientGenMoves(b, &size);
   
  while (1) {
      char in[10];
      printf("Would you like to be white or black? (Type 'w' or 'b' and press enter!\n");
      scanf("%s",in);
      if (in == NULL) {continue;}
      if (in[0] == 119 || in[0] == 98) {
         if (in[0] == 98) {
            player = 20;
            boardIsFlipped = 1;
         }
         break;
      }
      else {
         continue;
      }
   }

   while (1) {
      char in[10];
      printf("Enter a difficulty: 1=easiest, 7=hardest (warning, difficulty = 7 can take over 300s to move):\n");
      scanf("%s",in);
      if (in == NULL) {continue;}
      if (in[0]>= 49 && in[0] <= 56) {
         difficulty = in[0] - 48;
         break;
      }
      else {
         continue;
      }
   }


   while (b.gameState == 0) {
      char input[100];
      int size;
      int i;
      clock_t start;
      clock_t end;
      move blackMove;
      move whiteMove;
      printf("\n");
      printBoard(b, boardIsFlipped);
      printf("Current Board Evaluation: %d\n", evalCurrentBoard(b));
/*      printf("Please wait a moment\n");
      start = clock();
      if (moveNum != 1) {minimax(b, 2000, 1, 1, &best, root);}
      end = clock();
      printf("Thank you, you waited %fs press enter once to continue.\n", (double) (end-start)/CLOCKS_PER_SEC);
*/      getchar();
      if (moveNum != 1 || player == 10) {
      whiteMove = movePerson(b);
//      whiteMove = minimax(b, 2000, 1, 0, &best, root);
      if (whiteMove.from == -1) {
         PVTree newInitNode = pvInit();
         PVTree *newRoot = &newInitNode;
         undoMove(&b);
         freeAll(root);
         root = newRoot;
         continue;
      }
      movePiece(&b, whiteMove, 1);
      root = cleanUpTree(root, whiteMove);
      printBoard(b, boardIsFlipped);
      printf("Current Board Evaluation: %d\n", evalCurrentBoard(b));
      getchar();
      getchar();
      }
      start = clock();
//      blackMove = movePerson(b);
      if (player == 10) {
         blackMove = minimax(b, -2000, -1, 0, &best, root);
      }
      else {
         blackMove = minimax(b, 2000, 1, 0, &best, root);
      }
//      blackMove = sixLookMin(b);

 //     printf("'BEST' is %d\n", best);
      end = clock();
      printf("Computer moved %s from %c%c to %c%c in %f seconds.\n",key[b.store[blackMove.from]%10],-blackMove.from%8+104, blackMove.from/8+49, -blackMove.to%8+104, blackMove.to/8+49, (double) (end-start)/CLOCKS_PER_SEC);
      printf("Total paths explored: %d\n", totalNodes);

      movePiece(&b, blackMove, 1);
      root = cleanUpTree(root, blackMove);
      moveNum += 1;
      totalNodes = 0;
      totalLeaves = 0;
      genMovesCalls = 0;
   } 
}
