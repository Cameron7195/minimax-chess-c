#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "move.c"
#include "minimax.h"

board init(void) {
   board b = { {13,11,12,15,14,12,11,13,
                10,10,10,10,10,10,10,10,
                 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0,
                20,20,20,20,20,20,20,20, 
                23,21,22,25,24,22,21,23},
                 1,
                 1,
                 1,
                 1,
                 0,
                 0,
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                 10,
                 0,
                 0,
                {0,0,0,0,0,0,0,0},
                 NULL,  };
   return b;
}

int printBoard(board inputBoard, uint8_t flipped) {
   int i;
   int j;
   int k;
   board b;
   printf(" ");

   if (flipped == 1) {
      b = inputBoard;
   }
   else {
      int l;
      b = init();
      for (l=0;l<64;l++) {
         b.store[l] = inputBoard.store[63-l];
      }
   }


   for (i=0;i<8;i++) {
      if (flipped == 1) {
         printf("   %c  ", 104-i);
      }
      else {
         printf("   %c  ", 97+i);
      }
   }
   printf("\n");
   for (i=0;i<8;i++) {
   for (k=0;k<3;k++) {
      if (k%3 == 1) {
          if (flipped == 1) {printf("%d ", i+1);}
          else {printf("%d ", -i+8);}
      }
      else {printf("  ");}
      for (j=0;j<8;j++) {
         if (b.store[i*8 + j] == 0) {
            if (i%2==j%2) {
               printf("\u2591\u2591\u2591\u2591\u2591\u2591");
            }
            else {
            printf("      ");
            }
         }
         else { 
            if (k%3 ==1) {
               if (i%2==j%2) {
                  if (b.store[i*8 + j] == 10) {printf("\u2591\u2591WP\u2591\u2591");}
                  else if (b.store[i*8 + j] == 11) {printf("\u2591\u2591WN\u2591\u2591");}
                  else if (b.store[i*8 + j] == 12) {printf("\u2591\u2591WB\u2591\u2591");}
                  else if (b.store[i*8 + j] == 13) {printf("\u2591\u2591WR\u2591\u2591");}
                  else if (b.store[i*8 + j] == 14) {printf("\u2591\u2591WQ\u2591\u2591");}
                  else if (b.store[i*8 + j] == 15) {printf("\u2591\u2591WK\u2591\u2591");}
                  else if (b.store[i*8 + j] == 20) {printf("\u2591\u2591BP\u2591\u2591");}
                  else if (b.store[i*8 + j] == 21) {printf("\u2591\u2591BN\u2591\u2591");}
                  else if (b.store[i*8 + j] == 22) {printf("\u2591\u2591BB\u2591\u2591");}
                  else if (b.store[i*8 + j] == 23) {printf("\u2591\u2591BR\u2591\u2591");}
                  else if (b.store[i*8 + j] == 24) {printf("\u2591\u2591BQ\u2591\u2591");}
                  else if (b.store[i*8 + j] == 25) {printf("\u2591\u2591BK\u2591\u2591");}
               }
               else {
                  if (b.store[i*8 + j] == 10) {printf("  WP  ");}
                  else if (b.store[i*8 + j] == 11) {printf("  WN  ");}
                  else if (b.store[i*8 + j] == 12) {printf("  WB  ");}
                  else if (b.store[i*8 + j] == 13) {printf("  WR  ");}
                  else if (b.store[i*8 + j] == 14) {printf("  WQ  ");}
                  else if (b.store[i*8 + j] == 15) {printf("  WK  ");}
                  else if (b.store[i*8 + j] == 20) {printf("  BP  ");}
                  else if (b.store[i*8 + j] == 21) {printf("  BN  ");}
                  else if (b.store[i*8 + j] == 22) {printf("  BB  ");}
                  else if (b.store[i*8 + j] == 23) {printf("  BR  ");}
                  else if (b.store[i*8 + j] == 24) {printf("  BQ  ");}
                  else if (b.store[i*8 + j] == 25) {printf("  BK  ");}
               }
            }
            else {
               if (i%2==j%2) {printf("\u2591\u2591\u2591\u2591\u2591\u2591");}
               else {printf("      ");}
            }
         }
      }
      printf("\n");
   }
   }
   return 1;
}

move *genLegalMoves(board b, int *size) {
   move *moves;
   move *safeMoves;
   int s;
   int i;
   int cnt = 0;
   safeMoves = (move *)malloc(137*sizeof(move));
   moves = genAllMoves(b, &s, 0);
   for (i=0;i<s;i++) {
      if (isMoveSafe(b, moves[i]) == 1) {
         safeMoves[cnt] = moves[i];
         cnt += 1;
      }
   }
   *size = cnt;
   if (cnt != 0) {
      sortMoves(b, &safeMoves, cnt);
   }
   free(moves);
   return safeMoves;
}

move *genLegalMoves_unsorted(board b, int *size) {
   move *moves;
   move *safeMoves;
   int s;
   int i;
   int cnt = 0;
   safeMoves = (move *)malloc(137*sizeof(move));
   moves = genAllMoves(b, &s, 0);
   for (i=0;i<s;i++) {
      if (isMoveSafe(b, moves[i]) == 1) {
         safeMoves[cnt] = moves[i];
         cnt += 1;
      }
   }
   *size = cnt;
   if (cnt != 0) {
      sortMoves(b, &safeMoves, cnt);
   }
   free(moves);
   return safeMoves;
}

move *efficientGenMoves(board b, int *size) {
   move *moves;
   int s;
   int i;
   int cnt = 0;
   moves = genAllMoves(b, &cnt, 0);
   *size = cnt;
   if (cnt != 0) {
      sortMoves(b, &moves, cnt);
   }
   return moves;
}

int sortMoves(board b, move **moves, int size) {
   int i;
   move *sortedMoves;
   int zeroCnt = 1;
   int nonZeroCnt = 0;
   int sorted = 0;
   sortedMoves = (move *)malloc(size*sizeof(move));

   for (i=0; i<size; i++) {
      if ((*moves)[i].taking == 0) {
         sortedMoves[size-zeroCnt] = (*moves)[i];
         zeroCnt += 1;
      }
      else {
         sortedMoves[nonZeroCnt] = (*moves)[i];
         nonZeroCnt += 1;
      }
   }
   while (sorted == 0) {
      sorted = 1;
      for (i=0;i<nonZeroCnt-2;i++) {
         if (sortedMoves[i].taking < sortedMoves[i+1].taking) {
            move temp = sortedMoves[i];
            sortedMoves[i] = sortedMoves[i+1];
            sortedMoves[i+1] = temp;
            sorted = 0;
         }
      }
   }
   sorted = 0;
   while (sorted == 0) {
      sorted = 1;
      for (i=size-zeroCnt+1;i<size-1;i++) {
         if (b.store[sortedMoves[i].from] < b.store[sortedMoves[i+1].from]) {
            move temp = sortedMoves[i];
            sortedMoves[i] = sortedMoves[i+1];
            sortedMoves[i+1] = temp;
            sorted = 0;
         }
      }
   }
   free(*moves);
   *moves = sortedMoves;
   return 1;
}

// int improved_sortMoves(board b, move **moves, int size) {
//    int *scores;
//    int i;
//    int sorted = 0;   

//    scores = (int *)malloc(size*sizeof(int));
//    for (i=0;i<size;i++) {
//       board copy = b;
//       movePiece(&copy, (*moves)[i], 0);
//       if (b.turn == 10) {
//          scores[i] = twoLookScore(copy);
//       }
//       else if (b.turn == 20) {
//          scores[i] = (-1) * twoLookScore(copy);
//       }
//    }

//    while (sorted == 0) {
//       sorted = 1;
//       for (i=0;i<size-1;i++) {
//          if (scores[i+1] > scores[i]) {
//             int temp = scores[i];
//             move mtemp = (*moves)[i];
            
//             scores[i] = scores[i+1];
//             scores[i+1] = temp;
            
//             (*moves)[i] = (*moves)[i+1];
//             (*moves)[i+1] = mtemp;
//             sorted = 0;
//          }
//       }
//    }
//    free(scores);
//    return 1;
// }

move *genAllMoves(board b, int *size, int stopRecur){
   move *moves;
   int pieceNumMoves[6] = {4,8,13,14,27,8};
   int i;
   int j;
   int cnt = 0;

   moves = (move *)malloc(137*sizeof(move));

   for (i=0;i<64;i++) {
      if (b.store[i]/10 == b.turn/10) {
         int s;
         move *temp;
         temp = genPieceMoves(b, i, &s, stopRecur);
         for (j=0;j<s;j++) {
            if (temp[j].valid == 1) {
               moves[cnt] = temp[j];
               cnt += 1;
            }
         }
         free(temp);
      }
   }
   *size = cnt;
   return moves;
   
}

move *genPieceMoves(board b, int index, int *size, int stopRecur) {
   move *moves;
   int s;
   if (b.store[index]%10 == 0) {moves = pawnLegal(b, index, index%8, &s);}
   else if (b.store[index]%10 == 1) {moves = knightLegal(b,index, &s); }
   else if (b.store[index]%10 == 2) {moves = bishopLegal(b,index, &s); }
   else if (b.store[index]%10 == 3) {moves = rookLegal(b,index, &s); }
   else if (b.store[index]%10 == 4) {moves = queenLegal(b,index, &s); }
   else if (b.store[index]%10 == 5) {moves = kingLegal(b,index, &s, stopRecur); }

   *size = s;
   return moves;
}

int isMoveSafe(board b, move m) {
   int size;
   int i;
   move *moves;
   board copy = b;

   movePiece(&copy, m, 0);

   moves = genAllMoves(copy, &size, 1);
   if (size != 0) {
      for (i=0;i<size;i++) {
         if (moves[i].taking == b.turn + 5) {free(moves); return 0;}
      }
   }
   free(moves);
   return 1;
}

int isPlayerInCheck(board b) {
   move *moves;
   board copy = b;
   int check = 0;
   int size;
   int i;

   copy.turn = (copy.turn-15)*(-1)+15;

   moves = genAllMoves(copy, &size, 1);
   if (size != 0) {
      for (i=0;i<size;i++) {
         if (moves[i].taking%10 == 5) {
            check = 1;
         }
      }
   }
   free(moves);
   return check;
}

move *pawnLegal(board b, int index, int pawnIdx, int *size) {
   move *moves;
   int cnt = 0;
   int l;
   moves = (move *)malloc(4*sizeof(move));
   for (l=0;l<4;l++) {
      move m = {0,0,0,0,0,0,0,0};
      moves[l] = m;
   }

   if (b.store[index]==10) {
      if (index<=15) {
         if (b.store[index+8]==0) {
            moves[0].valid = 1;
            moves[0].from = index;
            moves[0].to = index+8;
            cnt += 1;
         }
         if (b.store[index+16]==0 && b.store[index+8] == 0) {
            moves[1].valid = 1;
            moves[1].from = index;
            moves[1].to = index+16;
            cnt += 1;
         }
         if (index%8!=7) {
            if (b.store[index+9]/10==2) {
               moves[3].valid = 1;
               moves[3].from = index;
               moves[3].to = index+9;
               moves[3].taking = b.store[index+9];
               cnt += 1;
            }
         }
         if (index%8!=0) {
            if (b.store[index+7]/10==2) {
               moves[2].valid = 1;
               moves[2].from = index;
               moves[2].to = index+7;
               moves[2].taking = b.store[index+7];
               cnt += 1;
            }
         }
      }
      else if (index<=47) {
         if (b.store[index+8]==0) {
            moves[0].valid = 1;
            moves[0].from = index;
            moves[0].to = index +8;
            cnt += 1;
         }
         if (index/8 == 4) {
            if (index%8!=7) {
               if (b.bPawns[pawnIdx+1] == 1 && b.store[index+9]==0 && b.store[index+1]/10==2) {
                  moves[3].valid = 1;
                  moves[3].from = index;
                  moves[3].to = index+9;
                  moves[3].passingR = 1;
                  moves[3].taking = b.store[index+1];
                  cnt += 1;
               }
            }
            if (index%8!=0) {
               if (b.bPawns[pawnIdx-1] == 1 && b.store[index+7]==0 && b.store[index-1]/10==2) {
                  moves[2].valid = 1;
                  moves[2].from = index;
                  moves[2].to = index+7;
                  moves[2].passingL = 1;
                  moves[2].taking = b.store[index-1];
                  cnt += 1;
               }
            }
         }
         if (index%8!=7) {
            if (b.store[index+9]/10==2) {
               moves[3].valid = 1;
               moves[3].from = index;
               moves[3].to = index+9;
               moves[3].taking = b.store[index+9];
               cnt += 1;
            }
         }
         if (index%8!=0) {
            if (b.store[index+7]/10==2) {
               moves[2].valid = 1;
               moves[2].from = index;
               moves[2].to = index+7;
               moves[2].taking = b.store[index+7];
               cnt += 1;
            }
         }
      }
      else if (index<=55) {
         if (b.store[index+8]==0) {
            moves[1].valid = 1;
            moves[1].from = index;
            moves[1].to = index+8;
            moves[1].queen = 1;
            cnt += 1;
         }
         if (index%8!=7) {
            if (b.store[index+9]/10==2) {
               moves[3].valid = 1;
               moves[3].from = index;
               moves[3].to = index+9;
               moves[3].queen = 1;
               moves[3].taking = b.store[index+9];
               cnt += 1;
            }
         }
         if (index%8!=0) {
            if (b.store[index+7]/10==2) {
               moves[2].valid = 1;
               moves[2].from = index;
               moves[2].to = index+7;
               moves[2].queen = 1;
               moves[2].taking = b.store[index+7];
               cnt += 1;
            }
         }
      }
   }
/* BLACK PAWNS */
   if (b.store[index]==20) {
      if (index>=48) {
         if (b.store[index-8]==0) {
            moves[0].valid = 1;
            moves[0].from = index;
            moves[0].to = index-8;
            cnt += 1;
         }
         if (b.store[index-16]==0 && b.store[index-8] == 0) {
            moves[1].valid = 1;
            moves[1].from = index;
            moves[1].to = index-16;
            cnt += 1;
         }
         if (index%8!=7) {
            if (b.store[index-7]/10==1) {
               moves[3].valid = 1;
               moves[3].from = index;
               moves[3].to = index-7;
               moves[3].taking = b.store[index-7];
               cnt += 1;
            }
         }
         if (index%8!=0) {
            if (b.store[index-9]/10==1) {
               moves[2].valid = 1;
               moves[2].from = index;
               moves[2].to = index-9;
               moves[2].taking = b.store[index-9];
               cnt += 1;
            }
         }
      }
      else if (index>=16) {
         if (b.store[index-8]==0) {
            moves[0].valid = 1;
            moves[0].from = index;
            moves[0].to = index-8;
            cnt += 1;
         }
         if (index/8 == 3) {
            if (index%8!=7) {
               if (b.wPawns[pawnIdx+1] == 1 && b.store[index-7]==0 && b.store[index+1]/10==1) {
                  moves[3].valid = 1;
                  moves[3].from = index;
                  moves[3].to = index-7;
                  moves[3].passingR = 1;
                  moves[3].taking = b.store[index+1];
                  cnt += 1;
               }
            }
            if (index%8!=0) {
               if (b.wPawns[pawnIdx-1] == 1 && b.store[index-9]==0 && b.store[index-1]/10==1) {
                  moves[2].valid = 1;
                  moves[2].from = index;
                  moves[2].to = index-9;
                  moves[2].passingL = 1;
                  moves[2].taking = b.store[index-1];
                  cnt += 1;
               }
            }
         }
         if (index%8!=7) {
            if (b.store[index-7]/10==1) {
               moves[3].valid = 1;
               moves[3].from = index;
               moves[3].to = index-7;
               moves[3].taking = b.store[index-7];
               cnt += 1;
            }
         }
         if (index%8!=0) {
            if (b.store[index-9]/10==1) {
               moves[2].valid = 1;
               moves[2].from = index;
               moves[2].to = index-9;
               moves[2].taking = b.store[index-9];
               cnt += 1;
            }
         }
      }
      else if (index>=8) {
         if (b.store[index-8]==0) {
            moves[1].valid = 1;
            moves[1].from = index;
            moves[1].to = index-8;
            moves[1].queen = 1;
            cnt += 1;
         }
         if (index%8!=7) {
            if (b.store[index-7]/10==1) {
               moves[3].valid = 1;
               moves[3].from = index;
               moves[3].to = index-7;
               moves[3].queen = 1;
               moves[3].taking = b.store[index-7];
               cnt += 1;
            }
         }
         if (index%8!=0) {
            if (b.store[index-9]/10==1) {
               moves[2].valid = 1;
               moves[2].from = index;
               moves[2].to = index-9;
               moves[2].queen = 1;
               moves[2].taking = b.store[index-9];
               cnt += 1;
            }
         }
      }
   }
   *size = 4;
   return moves;
}

move *knightLegal(board b, int index, int *size) {
   move *moves;
   int cnt = 0;
   int l;
   moves = (move *)malloc(8*sizeof(move));
   for (l=0;l<8;l++) {
      move m = {0,0,0,0,0,0,0,0};
      moves[l] = m;
   }

   if (index >= 16 && index%8 >=1) {
      if (b.store[index-17]/10 != b.store[index]/10) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = index-17;
         moves[cnt].taking = b.store[index-17];
         cnt += 1;
      }
   }
   if (index >= 16 && index%8 <=6) {
      if (b.store[index-15]/10 != b.store[index]/10) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = index-15;
         moves[cnt].taking = b.store[index-15];
         cnt += 1;
      }
   }
   if (index >= 8 && index%8 <=5) {
      if (b.store[index-6]/10 != b.store[index]/10) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = index-6;
         moves[cnt].taking = b.store[index-6];
         cnt += 1;
      }
   }
   if (index <= 55 && index%8 <=5) {
      if (b.store[index+10]/10 != b.store[index]/10) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = index+10;
         moves[cnt].taking = b.store[index+10];
         cnt += 1;
      }
   }
   if (index <= 47 && index%8 <=6) {
      if (b.store[index+17]/10 != b.store[index]/10) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = index+17;
         moves[cnt].taking = b.store[index+17];
         cnt += 1;
      }
   }
   if (index <= 47 && index%8 >=1) {
      if (b.store[index+15]/10 != b.store[index]/10) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = index+15;
         moves[cnt].taking = b.store[index+15];
         cnt += 1;
      }
   }
   if (index <= 55 && index%8 >=2) {
      if (b.store[index+6]/10 != b.store[index]/10) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = index+6;
         moves[cnt].taking = b.store[index+6];
         cnt += 1;
      }
   }
   if (index >= 8 && index%8 >=2) {
      if (b.store[index-10]/10 != b.store[index]/10) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = index-10;
         moves[cnt].taking = b.store[index-10];
         cnt += 1;
      }
   }
   *size = cnt;
   return moves;
}

move *bishopLegal(board b, int index, int *size) {
   move *moves;
   int curIndex = index;
   int cnt = 0;
   int l;
   moves = (move *)malloc(13*sizeof(move));
   for (l=0;l<13;l++) {
      move m = {0,0,0,0,0,0,0,0};
      moves[l] = m;
   }
   
   if (index%8!=0) {
      curIndex = index - 9;
      while (curIndex >= 0 && b.store[curIndex] == 0) {
         if (curIndex%8 != 0) {
            moves[cnt].valid = 1;
            moves[cnt].from = index;
            moves[cnt].to = curIndex;
            moves[cnt].taking = b.store[curIndex];
            cnt += 1;
            curIndex -= 9;
         }
         else { break; }
      }
      if (curIndex >= 0) {
         if (b.store[curIndex]/10 != b.store[index]/10) {
            moves[cnt].valid = 1;
            moves[cnt].from = index;
            moves[cnt].to = curIndex;
            moves[cnt].taking = b.store[curIndex];
            cnt += 1;
         }
      }
   }

   if (index%8!=7) {
      curIndex = index - 7;
      while (curIndex >= 0 && b.store[curIndex] == 0) {
         if (curIndex%8 != 7) {
            moves[cnt].valid = 1;
            moves[cnt].from = index;
            moves[cnt].to = curIndex;
            moves[cnt].taking = b.store[curIndex];
            cnt += 1;
            curIndex -= 7;
         }
         else { break; }
      }
      if (curIndex >= 0) {
         if (b.store[curIndex]/10 != b.store[index]/10) {
            moves[cnt].valid = 1;
            moves[cnt].from = index;
            moves[cnt].to = curIndex;
            moves[cnt].taking = b.store[curIndex];
            cnt += 1;
         }
      }
   }

   if (index%8!=7) {
      curIndex = index + 9;
      while (curIndex <= 63 && b.store[curIndex] == 0) {
         if (curIndex%8 != 7) {
            moves[cnt].valid = 1;
            moves[cnt].from = index;
            moves[cnt].to = curIndex;
            moves[cnt].taking = b.store[curIndex];
            cnt += 1;
            curIndex += 9;
         }
         else { break; }
      }
      if (curIndex <= 63) {
         if (b.store[curIndex]/10 != b.store[index]/10) {
            moves[cnt].valid = 1;
            moves[cnt].from = index;
            moves[cnt].to = curIndex;
            moves[cnt].taking = b.store[curIndex];
            cnt += 1;
         }
      }
   }

   if (index%8!=0) {
      curIndex = index + 7;
      while (curIndex <= 63 && b.store[curIndex] == 0) {
         if (curIndex%8 != 0) {
            moves[cnt].valid = 1;
            moves[cnt].from = index;
            moves[cnt].to = curIndex;
            moves[cnt].taking = b.store[curIndex];
            cnt += 1;
            curIndex += 7;
         }
         else { break; }
      }
      if (curIndex <= 63) {
         if (b.store[curIndex]/10 != b.store[index]/10) {
            moves[cnt].valid = 1;
            moves[cnt].from = index;
            moves[cnt].to = curIndex;
            moves[cnt].taking = b.store[curIndex];
            cnt += 1;
         }
      }
   }
   *size = cnt;
   return moves;
}

move *rookLegal(board b, int index, int *size) {
   move *moves;
   int cnt = 0;
   int curIndex;
   int l;
   moves = (move *)malloc(14*sizeof(move));
   for (l=0;l<14;l++) {
      move m = {0,0,0,0,0,0,0,0};
      moves[l] = m;
   }

   curIndex = index - 8;
   while (curIndex >= 0 && b.store[curIndex] == 0) {
      moves[cnt].valid = 1;
      moves[cnt].from = index;
      moves[cnt].to = curIndex;
      moves[cnt].taking = b.store[curIndex];
      cnt += 1;
      curIndex -= 8;
   }
   if (curIndex >= 0) {
      if (b.store[curIndex]/10 != b.store[index]/10) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = curIndex;
         moves[cnt].taking = b.store[curIndex];
         cnt += 1;
      }
   }

   curIndex = index + 8;
   while (curIndex <= 63 && b.store[curIndex] == 0) {
      moves[cnt].valid = 1;
      moves[cnt].from = index;
      moves[cnt].to = curIndex;
      moves[cnt].taking = b.store[curIndex];
      cnt += 1;
      curIndex += 8;
   }
   if (curIndex <= 63) {
      if (b.store[curIndex]/10 != b.store[index]/10) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = curIndex;
         moves[cnt].taking = b.store[curIndex];
         cnt += 1;
      }
   }

   if (index%8 != 7) {
      curIndex = index + 1;
      while (curIndex%8!=7 && b.store[curIndex] == 0) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = curIndex;
         moves[cnt].taking = b.store[curIndex];
         cnt += 1;
         curIndex += 1;
      }
      if (b.store[curIndex]/10 != b.store[index]/10) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = curIndex;
         moves[cnt].taking = b.store[curIndex];
         cnt += 1;
      }
   }

   if (index%8 != 0) {
      curIndex = index - 1;
      while (curIndex%8!=0 && b.store[curIndex] == 0) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = curIndex;
         moves[cnt].taking = b.store[curIndex];
         cnt += 1;
         curIndex -= 1;
      }
      if (b.store[curIndex]/10 != b.store[index]/10) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = curIndex;
         moves[cnt].taking = b.store[curIndex];
         cnt += 1;
      }
   }
   //printf("rookCount: %d \n",cnt);
   *size = cnt;
   return moves;
}

move *queenLegal(board b, int index,int *size) {
   move *moves;
   move *bishopTemp;
   move *rookTemp;
   int i;
   int s1;
   int s2;
   int cnt = 0;
   moves = (move *)malloc(27*sizeof(move));
   rookTemp = rookLegal(b, index, &s1);
   bishopTemp = bishopLegal(b, index, &s2);
   for (i=0;i<s1;i++) {
      moves[i] = rookTemp[i];
      cnt +=1;
   }
   for (i=s1;i<s1+s2;i++) {
      moves[i] = bishopTemp[i-s1];
      cnt += 1;
   }
   *size = s1 + s2;
   free(bishopTemp);
   free(rookTemp);
   return moves;
}

move *kingLegal(board b, int index, int *size, int stopRecur) {
   move *moves;
   int cnt = 0;
   int l;
   move castleTest1;
   move castleTest2;
   moves = (move *)malloc(8*sizeof(move));
   for (l=0;l<8;l++) {
      move m = {0,0,0,0,0,0,0,0};
      moves[l] = m;
   }
   
   if (index >= 8 && index%8 >= 1) {
      if (b.store[index-9]/10 != b.store[index]/10) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = index-9;
         moves[cnt].taking = b.store[index-9];
         cnt += 1;
      }
   }
   if (index >= 8) {
      if (b.store[index-8]/10 != b.store[index]/10) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = index-8;
         moves[cnt].taking = b.store[index-8];
         cnt += 1;
      }
   }
   if (index >= 8 && index%8 <= 6) {
      if (b.store[index-7]/10 != b.store[index]/10) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = index-7;
         moves[cnt].taking = b.store[index-7];
         cnt += 1;
      }
   }
   if (index%8 <= 6) {
      if (b.store[index+1]/10 != b.store[index]/10) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = index+1;
         moves[cnt].taking = b.store[index+1];
         cnt += 1;
      }
   }
   if (index <= 55 && index%8 <= 6) {
      if (b.store[index+9]/10 != b.store[index]/10) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = index+9;
         moves[cnt].taking = b.store[index+9];
         cnt += 1;
      }
   }
   if (index <= 55) {
      if (b.store[index+8]/10 != b.store[index]/10) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = index+8;
         moves[cnt].taking = b.store[index+8];
         cnt += 1;
      }
   }
   if (index <= 55 && index%8 >= 1) {
      if (b.store[index+7]/10 != b.store[index]/10) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = index+7;
         moves[cnt].taking = b.store[index+7];
         cnt += 1;
      }
   }
   if (index%8 >= 1) {
      if (b.store[index-1]/10 != b.store[index]/10) {
         moves[cnt].valid = 1;
         moves[cnt].from = index;
         moves[cnt].to = index-1;
         moves[cnt].taking = b.store[index-1];
         cnt += 1;
      }
   }

   if (!stopRecur && b.store[index] == 15 && b.wCastleL == 1) {
      if (index == 3) {
         if (b.store[2] == 0 && b.store[1] == 0) {
            castleTest1.valid = 1;
            castleTest1.from = index;
            castleTest1.to = 2;

            if (isMoveSafe(b, castleTest1) && !isPlayerInCheck(b)) {
               moves[cnt].valid = 1;
               moves[cnt].from = index;
               moves[cnt].to = index-2;
               moves[cnt].castle = 1;
               cnt += 1;
            }
         }
      }
      else if (index == 4) {
         if (b.store[3] == 0 && b.store[2] == 0 && b.store[1] == 0) {
            castleTest1.valid = 1;
            castleTest1.from = index;
            castleTest1.to = 3;
            castleTest2.valid = 1;
            castleTest2.from = index;
            castleTest2.to = 2;

            if (isMoveSafe(b, castleTest1) && isMoveSafe(b, castleTest2) && !isPlayerInCheck(b)) {
               moves[cnt].valid = 1;
               moves[cnt].from = index;
               moves[cnt].to = index-2;
               moves[cnt].castle = 1;
               cnt += 1;
            }
         }
      }
   }
   if (!stopRecur && b.store[index] == 15 && b.wCastleR == 1) {
      if (index == 3) {
         if (b.store[4] == 0 && b.store[5] == 0 && b.store[6] == 0) {
            castleTest1.valid = 1;
            castleTest1.from = index;
            castleTest1.to = 4;
            castleTest2.valid = 1;
            castleTest2.from = index;
            castleTest2.to = 5;

            if (!isPlayerInCheck(b) && isMoveSafe(b, castleTest1) && isMoveSafe(b, castleTest2)) {
               moves[cnt].valid = 1;
               moves[cnt].from = index;
               moves[cnt].to = index + 2;
               moves[cnt].castle = 1;
               cnt += 1;
            }
         }
      }
      else if (index == 4) {
         if (b.store[5] == 0 && b.store[6] == 0) {
            castleTest1.valid = 1;
            castleTest1.from = index;
            castleTest1.to = 5;

            if (!isPlayerInCheck(b) && isMoveSafe(b, castleTest1)) {
               moves[cnt].valid = 1;
               moves[cnt].from = index;
               moves[cnt].to = index + 2;
               moves[cnt].castle = 1;
               cnt += 1;
            }
         }
      }
   }
   if (!stopRecur && b.store[index] == 25 && b.bCastleL == 1) {
      if (index == 59) {
         if (b.store[58] == 0 && b.store[57] == 0) {
            castleTest1.valid = 1;
            castleTest1.from = index;
            castleTest1.to = 58;

            if (!isPlayerInCheck(b) && isMoveSafe(b, castleTest1)) {
               moves[cnt].valid = 1;
               moves[cnt].from = index;
               moves[cnt].to = index - 2;
               moves[cnt].castle = 1;
               cnt += 1;
            }
         }
      }
      else if (index == 60) {
         if (b.store[59] == 0 && b.store[58] == 0 && b.store[57] == 0) {
            castleTest1.valid = 1;
            castleTest1.from = index;
            castleTest1.to = 59;
            castleTest2.valid = 1;
            castleTest2.from = index;
            castleTest2.to = 58;

            if (!isPlayerInCheck(b) && isMoveSafe(b,castleTest1) && isMoveSafe(b, castleTest2)) {
               moves[cnt].valid = 1;
               moves[cnt].from = index;
               moves[cnt].to = index - 3;
               moves[cnt].castle = 1;
               cnt += 1;
            }
         }
      }
   }
   if (!stopRecur && b.store[index] == 25 && b.bCastleR == 1) {
      if (index == 59) {
         if (b.store[60] == 0 && b.store[61] == 0 && b.store[62] == 0) {
            castleTest1.valid = 1;
            castleTest1.from = index;
            castleTest1.to = 60;
            castleTest2.valid = 1;
            castleTest2.from = index;
            castleTest2.to = 61;

            if (!isPlayerInCheck(b) && isMoveSafe(b,castleTest1) && isMoveSafe(b,castleTest2)) {
               moves[cnt].valid = 1;
               moves[cnt].from = index;
               moves[cnt].to = index + 3;
               moves[cnt].castle = 1;
               cnt += 1;
            }
         }
      }
      else if (index == 60) {
         if (b.store[61] == 0 && b.store[62] == 0) {
            castleTest1.valid = 1;
            castleTest1.from = index;
            castleTest1.to = 61;

            if (!isPlayerInCheck(b) && isMoveSafe(b,castleTest1)) {
               moves[cnt].valid = 1;
               moves[cnt].from = index;
               moves[cnt].to = index + 2;
               moves[cnt].castle = 1;
               cnt += 1;
            }
         }
      }
   }
   /*printf("king move count: %d\n", cnt);*/
   *size = cnt;
   return moves;

}

