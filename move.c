
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "move.h"

move movePerson(board b) {
   int from = -1;
   int to;
   int size;
   int i;
   int moveFound = 0;
   move chosenMove;
   move *moves;
   char (key[])[10] = {"Pawn", "Knight", "Bishop", "Rook", "Queen", "King"};

   moves = genLegalMoves(b, &size);
   while (1) {
      char in[10];
      scanf("");
      printf("Select piece index:\n");
      scanf("%s",in);
      if (in[0]>= 97 && in[0] <= 104) {
         if (in[1]>= 49 && in[1] <= 58) {
            from = (in[1]-49)*8+104-in[0];
         }
         else {
            printf("Enter a valid index!");
         }
         if (from >= 0 && from <= 63) {
            if (b.store[from]/10 == b.turn/10) {
               int noMoves = 1;
               for (i=0;i<size;i++) {
                  if (moves[i].from == from) {
                     noMoves = 0;
                  }
               }
               if (noMoves == 0) {
                  printf("You selected your %s!\n", key[b.store[from]%10]);
                  while (1) {
                     scanf("");
                     printf("Select index to move to: (type 'm' for moves, 'q' to go back) \n");
                     scanf("%s", in);
                     if (in[0] == 'q') {break;}
                     if (in[0] == 'U') {if (in[1] == 'N') {if (in[2] == 'D') {if (in[3] == 'O') {
                        //Undo last move
                        move undo = {-1,-1,-1,-1,-1,-1,-1,-1};
                        free(moves);
                        return undo;
                     }}}}
                     if (in[0] == 'm') {printMoves(b, moves, from, size); continue;}
                     if (in[0] >= 97 && in[0] <= 104) {
                        if (in[1]>= 48 && in[1] <= 57) {
                           to = (in[1]-49)*8+104-in[0];
                        }
                        else {
                           printf("Enter a valid index or 'q'!");
                        }
                        if (to >= 0 && to <= 63) {
                           int noMoves_1 = 1;
                           for (i=0;i<size;i++) {
                              if (moves[i].from == from && moves[i].to == to) {
                                 chosenMove = moves[i];
                                 noMoves_1 = 0;
                                 moveFound = 1;
                                 break;
                              }
                           }
                           if (noMoves_1 == 0) {
                              break;
                           }
                           else {
                              printf("Not a valid move, try again \n");
                           }
                        }
                        else {
                           printf("Index out of range, try again \n");
                        }
                     }
                     else {
                        printf("Enter a valid index or 'q'! \n");
                     }
                  }
                  if (moveFound == 1) {
                     break;
                  }
               }
               else {
                  printf("That piece has no moves, try again \n");
               }
            }
            else {
               printf("That's not your piece, try again \n");
            }
         }
         else {
            printf("Index out of range, try again \n");
         }
      }
      else {
         printf("Enter a valid index! \n");
      }
   }
   free(moves);
   return chosenMove;
}

int printMoves(board b, move *moves, int from, int size) {
   int j;
   int pieceSearch = 0;
   char (key[])[10] = {"Pawn", "Knight", "Bishop", "Rook", "Queen", "King"};

   for (j=0;j<size;j++) {
      if (moves[j].from == from) {
         printf("[%c%c->%c%c] ", moves[j].from%8+97, moves[j].from/8+48, moves[j].to%8+97, moves[j].to/8+48);
      }
   }
   printf("\n");
   return 1;
}

int movePiece(board *b, move m, uint8_t saveBoardHistory) {
   int i;
   board *copy;

   if (saveBoardHistory == 1) {
      copy = (board *)malloc(1*sizeof(board));
      *copy = *b;
      b->previousBoard = copy;
      b->previousMove = m;
   }

   b->turn = (b->turn-15)*(-1)+15;
   b->turnNumber += 1;

   b->store[m.to] = b->store[m.from];
   b->store[m.from] = 0;

   if (m.castle == 1) {
      if (b->turn == 20) {
         b->wHasCastled = 1;
      }
      else if (b->turn == 10) {
         b->bHasCastled = 1;
      }

      if (m.to == 6) {
         b->store[5] = 13;
         b->store[7] = 0;
         b->wCastleL = 0;
         b->wCastleR = 0;
         return 1;
      }
      else if (m.to == 5) {
         b->store[4] = 13;
         b->store[7] = 0;
         b->wCastleL = 0;
         b->wCastleR = 0;
         return 1;
      }
      else if (m.to == 1) {
         b->store[2] = 13;
         b->store[0] = 0;
         b->wCastleL = 0;

         b->wCastleR = 0;
         return 1;
      }
      else if (m.to == 2) {
         b->store[3] = 13;
         b->store[0] = 0;
         b->wCastleL = 0;
         b->wCastleR = 0;
         return 1;
      }
      else if (m.to == 62) {
         b->store[61] = 13;
         b->store[63] = 0;
         b->bCastleL = 0;
         b->bCastleR = 0;
         return 1;
      }
      else if (m.to == 61) {
         b->store[60] = 13;
         b->store[63] = 0;
         b->bCastleL = 0;
         b->bCastleR = 0;
         return 1;
      }
      else if (m.to == 57) {
         b->store[58] = 13;
         b->store[56] = 0;
         b->bCastleL = 0;
         b->bCastleR = 0;
         return 1;
      }
      else if (m.to == 58) {
         b->store[59] = 13;
         b->store[56] = 0;
         b->bCastleL = 0;
         b->bCastleR = 0;
         return 1;
      }
   }

   if (b->store[m.to] == 13 && m.from == 0) {
      b->wCastleL = 0;
   }
   else if (b->store[m.to] == 13 && m.from == 7) {
      b->wCastleR = 0;
   }
   else if (b->store[m.to] == 23 && m.from == 56) {
      b->bCastleL = 0;
   }
   else if (b->store[m.to] == 23 && m.from == 63) {
      b->bCastleR = 0;
   }

   if (b->store[m.to] == 15) {
      b->wCastleL = 0;
      b->wCastleR = 0;
   }
   if (b->store[m.to] == 25) {
      b->bCastleL = 0;
      b->bCastleR = 0;
   }

   if (m.passingL == 1 || m.passingR == 1) {
      if (b->store[m.to] == 10) {
         b->store[m.to-8] = 0;
         return 1;
      }
      else if (b->store[m.to] == 20) {
         b->store[m.to+8] = 0;
         return 1;
      }
   }

   for (i=0;i<8;i++) {
      b->bPawns[i] = 0;
      b->wPawns[i] = 0;
   }
   
   if ((m.to - m.from == 16 || m.to - m.from == -16)) {
      if (b->store[m.to] == 10) {
         b->wPawns[m.to%8] = 1;
      }
      else if (b->store[m.to] == 20) {
         b->bPawns[m.to%8] = 1;
      }
   }


   if (m.queen == 1) {
      if (b->store[m.to] == 10) {
         b->store[m.to] = 14;
      }
      else if (b->store[m.to] == 20) {
         b->store[m.to] = 24;
      }
   }

   if (b->store[m.to] == 10 && m.from/8 == 3) {
      b->wPawns[m.from%8] = 0;
   }
   if (b->store[m.to] == 20 && m.from/8 == 5) {
      b->bPawns[m.from%8] = 0;
   }

   return 1;

}

int undoMove(board *b) {
   board *temp;
   board *temp2;
   if (b == NULL) {return -1;}
   if (b->turnNumber <= 1) {return 0;}

   //Called twice to put the game 2 moves back.
   temp = b->previousBoard;
   *b = *(b->previousBoard);
   free(temp);

   temp2 = b->previousBoard;
   *b = *(b->previousBoard);
   free(temp2);
   
   return 1;
}
