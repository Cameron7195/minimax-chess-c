#include <stdio.h>
#include <stdlib.h>
#include "eval.c"
#include "minimax.h"

// white is 1, black is -1

static int totalNodes = 0;
static int totalLeaves = 0;
static int genMovesCalls = 0;
static int difficulty;

move minimax(board b, int bestScoreFound, int player, int depth, int *scoreReturn, PVTree *currentNode) {
   move *moves_7 = NULL;
   int numMoves_7;
   int i;
   int currentBest_7 = -2000*player;
   int treeDepth = 5;
   int j;
   int k;
   board firstCopy_7 = b;
   board copy_7;
   move chosenMove = {0,0,0,0,0,0,0,0};
   int temp;
   int first = 0;
   int lazy = 0;

   if (depth == 0) {minimax(b, bestScoreFound, player, depth + 1, scoreReturn, currentNode);}

   if (depth == difficulty) {*scoreReturn = evalCurrentBoard(b);totalLeaves += 1; return chosenMove;}

   if (currentNode->children == NULL) {
      moves_7 = efficientGenMoves(b, &numMoves_7);
      genMovesCalls += 1;
      totalNodes += numMoves_7;
   }
   else {
      moves_7 = sortFromNode(currentNode->children, currentNode->size, player);
      numMoves_7 = currentNode->size;
   }

   if (numMoves_7 == 0) {
      *scoreReturn = -2000*player;
      return chosenMove;
   }


   if (depth <= treeDepth && currentNode->children == NULL) {
      int l;
      currentNode->children = pvArrInit(137);
      currentNode->size = 0;
      for (l=0;l<numMoves_7;l++) {
         ((currentNode->children))[l].m = moves_7[l];
         ((currentNode->children))[l].score = (-500-l)*player;
         currentNode->size += 1;
      }
      first = 1;
   }

   if (numMoves_7 == 0) {
      printf("no moves");
   }
   else {
      movePiece(&firstCopy_7, moves_7[0], 0);
      if (depth < treeDepth) {
         minimax(firstCopy_7, -2000*(player), -1*player, depth + 1, &currentBest_7, &(currentNode->children[0]));
      }
      else {
         minimax(firstCopy_7, -2000*(player), -1*player, depth + 1, &currentBest_7, pvArrInit(1));
      }
      chosenMove = moves_7[0];
      for (i=1;i<numMoves_7;i++) {
         int currentBest_6;
         copy_7 = b;
         if (depth == 1 && first == 0 && lazy == 1) {
            if (currentNode->children[i].score <= -500*player) {break;}
         }
         if (depth <= 1) {
            if (isMoveSafe(b, moves_7[i]) == 0) {
               continue;
            }
         }
         movePiece(&copy_7, moves_7[i], 0);
         if (depth < treeDepth) {
            minimax(copy_7, currentBest_7, -1*player, depth + 1, &currentBest_6, &(currentNode->children[i]));
         }
         else {
            minimax(copy_7, currentBest_7, -1*player, depth + 1, &currentBest_6, pvArrInit(1));
         }
         if (player*currentBest_6 > player*currentBest_7) {
            currentBest_7 = currentBest_6;
            chosenMove = moves_7[i];
         }
         if (player == 1) {
            if (currentBest_6 >= bestScoreFound) {break; temp = currentBest_6;}
         }
         else {
            if (currentBest_6 <= bestScoreFound) {break; temp = currentBest_6;}
         }
      }
   }
   free(moves_7);

   *scoreReturn = currentBest_7;
   currentNode->score = currentBest_7;
   return chosenMove;
}

move *sortFromNode(PVTree *children, int size, int player) {
   move *output = (move *)malloc(size*sizeof(move));   
   move temp;
   PVTree pTemp;
   int *scoreArray = (int *)malloc(size*sizeof(int));
   int i, key, j;
   

   for (i=0;i<size;i++) {
      output[i] = children[i].m;
      scoreArray[i] = children[i].score;
   }

   for (i = 1; i < size; i++) { 
      key = scoreArray[i]; 
      temp = output[i];
      pTemp = children[i];
      j = i - 1;
      while (j >= 0 && player*scoreArray[j] < player*key) { 
         output[j+1] = output[j];
         scoreArray[j+1] = scoreArray[j];
         children[j+1] = children[j];
         j = j - 1; 
      } 
      scoreArray[j+1] = key;
      output[j+1] = temp;
      children[j+1] = pTemp;
   }
   free(scoreArray);
   return output;
}


// move sevenLookMax(board b) {
//    move *moves_7;
//    int numMoves_7;
//    int i;
//    int currentBest_7 = -2000;
//    board firstCopy_7 = b;
//    board copy_7;
//    move chosenMove;

//    moves_7 = genLegalMoves(b, &numMoves_7);

//    if (numMoves_7 == 0) {
//       printf("no moves");
//    }
//    else {
//       movePiece(&firstCopy_7, moves_7[0], 0);
//       currentBest_7 = sixLookMinScore(firstCopy_7, -2000);
//       chosenMove = moves_7[0];
//       for (i=0;i<numMoves_7;i++) {
//          int currentBest_6;
//          copy_7 = b;
//          movePiece(&copy_7, moves_7[i], 0);
//          currentBest_6 = sixLookMinScore(copy_7, currentBest_7);
//          if (currentBest_6 >= currentBest_7) {
//             currentBest_7 = currentBest_6;
//             chosenMove = moves_7[i];
//          }
//       }
//    }
//    free(moves_7);
//    return chosenMove;
// }


// int fillInPVs(board b, move **first, int depth) {
//    int i;
//    board copy = b;
//    move *moves;
//    int numMoves;
   
//    *first = (move *)malloc(200*sizeof(move));
//    for (i=depth;i>0;i--) {
//       moves = genLegalMoves_unsorted(copy, &numMoves);
//       (*first)[i] = moves[0];
//       movePiece(&copy, moves[0], 0);
//       printf("hi");
//       free(moves);
//    }

//    return 0;
// }

// move sixLookMin(board b) {
//    move *moves_6;
//    int numMoves_6;
//    int i;
//    int currentBest_6 = 2000;
//    move chosenMove;
//    board firstCopy_6 = b;
//    board copy_6;

//    printf("test");

   
//    moves_6 = genLegalMoves(b, &numMoves_6);

//    if (numMoves_6 == 0) {
//       printf("no moves");
//    }
//    else {
//       movePiece(&firstCopy_6, moves_6[0], 0);
//       currentBest_6 = fiveLookMaxScore(firstCopy_6, 2000);
//       chosenMove = moves_6[0];
//       for (i=0;i<numMoves_6;i++) {
//          int currentBest_5;
//          copy_6 = b;
//          printf("%.2f ", (float)(i)/(float)(numMoves_6));
//          movePiece(&copy_6, moves_6[i], 0);
//          currentBest_5 = fiveLookMaxScore(copy_6, currentBest_6);
//          if (currentBest_5 < currentBest_6) {
//             currentBest_6 = currentBest_5;
//             chosenMove = moves_6[i];
//          }
//       }
//    }
//    printf("\n");
//    free(moves_6);
//    return chosenMove;
// }

// int sixLookMinScore(board b, int currentBest, move *first) {
//    move *moves_6;
//    int numMoves_6;
//    int i;
//    int currentBest_6 = 2000;
//    board firstCopy_6 = b;
//    board copy_6;

//    moves_6 = genLegalMoves_unsorted(b, &numMoves_6);

//    if (numMoves_6 == 0) {
//       if (!isPlayerInCheck(b) && evalCurrentBoard(b) > 0) {
//          currentBest_6 = -1900;
//       }
//    }
//    else {
//       movePiece(&firstCopy_6, moves_6[0], 0);
//       currentBest_6 = fiveLookMaxScore(firstCopy_6, -2000, &(*first));
//       for (i=0;i<numMoves_6;i++) {
//          int currentBest_5;
//          copy_6 = b;
//          movePiece(&copy_6, moves_6[i], 0);
//          currentBest_5 = fiveLookMaxScore(copy_6, currentBest_6);
//          if (currentBest_5 < currentBest_6) {
//             currentBest_6 = currentBest_5;
//          }
//          if (currentBest_5 < currentBest) {break;}
//       }
//    }
//    free(moves_6);
//    return currentBest_6;
// }

// move fiveLookMax(board b, move *first) {
//    move *moves_5;
//    int numMoves_5;
//    int i;
//    int currentBest_5 = -2000;
//    board firstCopy_5 = b;
//    board copy_5;
//    move chosenMove;

//    moves_5 = genLegalMoves(b, &numMoves_5);

//    if (numMoves_5 == 0) {
//       printf("no moves");
//    }
//    else {
//       movePiece(&firstCopy_5, first[5], 0);
//       currentBest_5 = threeLookMaxScore(firstCopy_5, 2000);
//       chosenMove = moves_5[0];
//       for (i=0;i<numMoves_5;i++) {
//          int currentBest_4;
//          copy_5 = b;
//          movePiece(&copy_5, moves_5[i], 0);
//          currentBest_4 = fourLookMinScore(copy_5, currentBest_5);
//          if (currentBest_4 > currentBest_5) {
//             currentBest_5 = currentBest_4;
//             chosenMove = moves_5[i];
//          }
//       }
//    }
//    return chosenMove;
// }

// int fiveLookMaxScore(board b, int currentBest) {
//    move *moves_5;
//    int numMoves_5;
//    int i;
//    int currentBest_5 = -2000;
//    board firstCopy_5 = b;
//    board copy_5;

//    moves_5 = genLegalMoves(b, &numMoves_5);

//    if (numMoves_5 == 0) {
//       if (!isPlayerInCheck(b) && evalCurrentBoard(b) < 0) {
//          currentBest_5 = 1900;
//          printf("triggered stalemate avoidance L5\n");
//       }
//    }
//    else {
//       movePiece(&firstCopy_5, moves_5[0], 0);
//       currentBest_5 = fourLookMinScore(firstCopy_5, -2000);
//       for (i=0;i<numMoves_5;i++) {
//          int currentBest_4;
//          copy_5 = b;
//          movePiece(&copy_5, moves_5[i], 0);
//          currentBest_4 = fourLookMinScore(copy_5, currentBest_5);
//          if (currentBest_4 >= currentBest_5) {
//             currentBest_5 = currentBest_4;
//          }
//          if (currentBest_4 >= currentBest) {break;}
//       }
//    }
//    free(moves_5);
//    return currentBest_5;
// }

// move fourLookMin(board b) {
//    move *moves_4;
//    int numMoves_4;
//    int i;
//    int currentBest_4 = 2000;
//    move chosenMove;
//    board firstCopy_4 = b;
//    board copy_4;

//    moves_4 = genLegalMoves(b, &numMoves_4);

//    if (numMoves_4 == 0) {
//       printf("no moves");
//    }
//    else {
//       movePiece(&firstCopy_4, moves_4[0], 0);
//       currentBest_4 = threeLookMaxScore(firstCopy_4, 2000);
//       chosenMove = moves_4[0];
//       for (i=0;i<numMoves_4;i++) {
//          int currentBest_3;
//          copy_4 = b;
//          movePiece(&copy_4, moves_4[i], 0);
//          currentBest_3 = threeLookMaxScore(copy_4, currentBest_4);
//          if (currentBest_3 < currentBest_4) {
//             currentBest_4 = currentBest_3;
//             chosenMove = moves_4[i];
//          }
//       }
//    }
//    return chosenMove;
// }

// int fourLookMinScore(board b, int currentBest) {
//    move *moves_4;
//    int numMoves_4;
//    int i;
//    int currentBest_4 = 2000;
//    board firstCopy_4 = b;
//    board copy_4;

//    moves_4 = efficientGenMoves(b, &numMoves_4);

//    if (numMoves_4 == 0) {
//       if (!isPlayerInCheck(b) && evalCurrentBoard(b) > 0) {
//          currentBest_4 = -1900;
//       }
//    }
//    else {
//       movePiece(&firstCopy_4, moves_4[0], 0);
//       currentBest_4 = threeLookMaxScore(firstCopy_4, 2000);
//       for (i=0;i<numMoves_4;i++) {
//          int currentBest_3;
//          copy_4 = b;
//          movePiece(&copy_4, moves_4[i], 0);
//          currentBest_3 = threeLookMaxScore(copy_4, currentBest_4);
//          if (currentBest_3 < currentBest_4) {
//             currentBest_4 = currentBest_3;
//          }
//          if (currentBest_3 <= currentBest) {break;}
//       }
//    }
//    free(moves_4);
//    return currentBest_4;
// }

// move threeLookMax(board b) {
//    move *moves_3 = (move *)malloc(137*sizeof(move));
//    int numMoves_3;
//    int i;
//    int currentBest_3;
//    move chosenMove;
//    board firstCopy_3 = b;
//    board copy_3;

//    moves_3 = genLegalMoves(b, &numMoves_3);

//    if (numMoves_3 == 0) {
//       printf("no moves");
//    }
//    else {
//       movePiece(&firstCopy_3, moves_3[0], 0);
//       currentBest_3 = twoLookMinScore(firstCopy_3, -2000);
//       chosenMove = moves_3[0];
//       for (i=0;i<numMoves_3;i++) {
//          int currentBest_2;
//          copy_3 = b;
//          movePiece(&copy_3, moves_3[i], 0);
//          currentBest_2 = twoLookMinScore(copy_3, currentBest_3);
//          if (currentBest_2 > currentBest_3) {
//             currentBest_3 = currentBest_2;
//             chosenMove = moves_3[i];
//          }
//          //printf("[%d, %d], value: %d, current Best Move Value: %d \n", moves_3[i].from, moves_3[i].to, currentBest_2, currentBest_3);
//       }
//    }
//    return chosenMove;

// }

// int threeLookMaxScore(board b,int currentBest) {
//    move *moves_3;
//    int numMoves_3;
//    int i;
//    int currentBest_3 = -2000;
//    board firstCopy_3 = b;
//    board copy_3 = b;

//    moves_3 = efficientGenMoves(b, &numMoves_3);
//    if (numMoves_3 == 0) {
//       if (!isPlayerInCheck(b) && evalCurrentBoard(b) < 0) {
//          currentBest_3 = 1900;
//       }
//    }
//    else {
//       movePiece(&firstCopy_3, moves_3[0], 0);
//       currentBest_3 = twoLookMinScore(firstCopy_3, -2000);
//       for (i=0;i<numMoves_3;i++) {
//          int currentBest_2;
//          copy_3 = b;
//          movePiece(&copy_3, moves_3[i], 0);
//          currentBest_2 = twoLookMinScore(copy_3, currentBest_3);
//          if (currentBest_2 > currentBest_3) {
//             currentBest_3 = currentBest_2;
//          }
//          if (currentBest_2 >= currentBest) {break;}
//          //printf("[%d, %d], value: %d, current Best Move Value: %d \n", moves_3[i].from, moves_3[i].to, currentBest_2, currentBest_3);
//       }
//    }
//    free(moves_3);
//    return currentBest_3;

// }

// move twoLookMin(board b) {
//    move *moves_2 = (move *)malloc(137*sizeof(move));
//    int numMoves_2;
//    int i;
//    int currentBest_2;
//    move chosenMove;
//    board firstCopy_2 = b;
//    board copy_2;

//    moves_2 = efficientGenMoves(b, &numMoves_2);

//    if (numMoves_2 == 0) {
//    }
//    else {
//       movePiece(&firstCopy_2,moves_2[0], 0);
//       currentBest_2 = evalCurrentBoard(firstCopy_2);
//       chosenMove = moves_2[0];
//       for (i=0;i<numMoves_2;i++) {
//          move *moves_1 = (move *)malloc(137*sizeof(move));
//          int numMoves_1;
//          int j;
//          int currentBest_1;
//          board firstCopy_1;

//          copy_2 = b;
//          movePiece(&copy_2,moves_2[i], 0);
//          firstCopy_1 = copy_2;

//          moves_1 = efficientGenMoves(copy_2, &numMoves_1);
//          if (numMoves_1 == 0) {
//          }
//          else {
//             movePiece(&firstCopy_1, moves_1[0], 0);
//             currentBest_1 = evalCurrentBoard(firstCopy_1);
//             for (j=0;j<numMoves_1;j++) {
//                int copyEval;
//                board copy_1 = copy_2;
//                movePiece(&copy_1,moves_1[j], 0);
//                copyEval = evalCurrentBoard(copy_1);
//                //printf("[%d, %d], [%d, %d] Eval: %d \n", moves_2[i].from, moves_2[i].to, moves_1[j].from, moves_1[j].to, copyEval);
//                if (copyEval > currentBest_2) {break;}
//                if (copyEval > currentBest_1) {
//                   currentBest_1 = copyEval;
//                }
//             }
//          }
//          if (currentBest_1 < currentBest_2) {
//             currentBest_2 = currentBest_1;
//             chosenMove = moves_2[i];
//             //printf("new best move: [%d, %d] \n", moves_2[i].from, moves_2[i].to);
//          }
//          free(moves_1);
//       }
//    free(moves_2);
//    return chosenMove;
//    }
// }

// int twoLookMinScore(board b, int currentBest) {
//    move *moves_2;
//    int numMoves_2;
//    int i;
//    int currentBest_2 = 2000;
//    board firstCopy_2 = b;
//    board copy_2;

//    moves_2 = genLegalMoves_unsorted(b, &numMoves_2);

//    if (numMoves_2 == 0) {
//       if (!isPlayerInCheck(b) && evalCurrentBoard(b) > 0) {
//          free(moves_2);
//          return -1900;
//       }
//    }
//    else {
//       movePiece(&firstCopy_2, moves_2[0], 0);
//       currentBest_2 = oneLookMaxScore(firstCopy_2);
//       for (i=0;i<numMoves_2;i++) {
//          move *moves_1;
//          int numMoves_1;
//          int j;
//          int currentBest_1 = -2000;
//          board firstCopy_1;
//          copy_2 = b;
//          movePiece(&copy_2,moves_2[i], 0);
//          firstCopy_1 = copy_2;
//          moves_1 = genLegalMoves_unsorted(copy_2, &numMoves_1);
//          if (numMoves_1 == 0) {
//             if (!isPlayerInCheck(copy_2) && evalCurrentBoard(copy_2) < 0) {
//                currentBest_1 = 1900;
//             }
//          }
//          else {
//             movePiece(&firstCopy_1, moves_1[0], 0);
//             currentBest_1 = evalCurrentBoard(firstCopy_1);
//             for (j=0;j<numMoves_1;j++) {
//                int copyEval;
//                board copy_1 = copy_2;
//                movePiece(&copy_1,moves_1[j], 0);
//                copyEval = evalCurrentBoard(copy_1);
//                if (copyEval >= currentBest_2) {break;}
//                if (copyEval > currentBest_1) {
//                   currentBest_1 = copyEval;
//                }
//             }
//          }
//          free(moves_1);
//          if (currentBest_1 < currentBest_2) {
//             currentBest_2 = currentBest_1;
//          }
//          if (currentBest_1 <= currentBest) {break;}
//       }
//    }
//    free(moves_2);
//    return currentBest_2;
// }

// int twoLookMaxScore(board b, int currentBest) {
//    move *moves_2;
//    int numMoves_2;
//    int i;
//    int currentBest_2 = -2000;
//    board firstCopy_2 = b;
//    board copy_2;

//    moves_2 = genLegalMoves_unsorted(b, &numMoves_2);

//    if (numMoves_2 == 0) {
//       if (!isPlayerInCheck(b) && evalCurrentBoard(b) < 0) {
//          free(moves_2);
//          return 1900;
//       }
//    }
//    else {
//       movePiece(&firstCopy_2,moves_2[0], 0);
//       currentBest_2 = oneLookMinScore(firstCopy_2);
//       for (i=0;i<numMoves_2;i++) {
//          move *moves_1;
//          int numMoves_1;
//          int j;
//          int currentBest_1 = 2000;
//          board firstCopy_1;
//          copy_2 = b;
//          movePiece(&copy_2,moves_2[i], 0);
//          firstCopy_1 = copy_2;
//          moves_1 = genLegalMoves_unsorted(copy_2, &numMoves_1);
//          if (numMoves_1 == 0) {
//             if (!isPlayerInCheck(copy_2) && evalCurrentBoard(copy_2) > 0) {
//                currentBest_1 = -1900;
//             }
//          }
//          else {
//             movePiece(&firstCopy_1, moves_1[0], 0);
//             currentBest_1 = evalCurrentBoard(firstCopy_1);
//             for (j=0;j<numMoves_1;j++) {
//                int copyEval;
//                board copy_1 = copy_2;
//                movePiece(&copy_1,moves_1[j], 0);
//                copyEval = evalCurrentBoard(copy_1);
//                if (copyEval < currentBest_2) {break;}
//                if (copyEval < currentBest_1) {
//                   currentBest_1 = copyEval;
//                }
//             }
//          }
//          free(moves_1);
//          if (currentBest_1 > currentBest_2) {
//             currentBest_2 = currentBest_1;
//          }
//          if (currentBest_1 > currentBest) {break;}
//       }
//    }
//    free(moves_2);
//    return currentBest_2;
// }


// int threeLookScore(board b, move *first) {
//    if (b.turn == 20) {return twoLookMinScore(b, -2000);}
//    else if (b.turn == 10) {return twoLookMaxScore(b, 2000);}
// }

// int twoLookScore(board b) {
//    if (b.turn == 20) {return oneLookMinScore(b);}
//    else if (b.turn == 10) {return oneLookMaxScore(b);}
// }

// move oneLookMin(board b) {
//    move *moves_1;
//    int numMoves_1;
//    int i;
//    int currentBest_1;
//    board firstCopy = b;
//    move chosenMove;
//    board copy = b;

//    moves_1 = (move *)malloc(137*sizeof(move));
//    moves_1 = genLegalMoves(b,&numMoves_1);

//    movePiece(&firstCopy,moves_1[0], 0);
//    currentBest_1 = evalCurrentBoard(firstCopy);
//    chosenMove = moves_1[0];
//    for (i=0;i<numMoves_1;i++) {
//       int copyEval_1;
//       copy = b;
//       movePiece(&copy,moves_1[i], 0);
//       copyEval_1 = evalCurrentBoard(copy);
//       if (copyEval_1 < currentBest_1) {
//          currentBest_1 = copyEval_1;
//          chosenMove = moves_1[i];
//       }
//    }
//    return chosenMove;
// }

// move oneLookMax(board b) {
//    move *moves_1;
//    int numMoves_1;
//    int i;
//    int currentBest_1 = -2000;
//    board firstCopy = b;
//    move chosenMove;
//    board copy = b;
//    moves_1 = (move *)malloc(137*sizeof(move));
//    moves_1 = genLegalMoves(b,&numMoves_1);

//    movePiece(&firstCopy,moves_1[0], 0);
//    currentBest_1 = evalCurrentBoard(firstCopy);
//    chosenMove = moves_1[0];
//    for (i=0;i<numMoves_1;i++) {
//       int copyEval_1;
//       copy = b;
//       movePiece(&copy,moves_1[i], 0);
//       copyEval_1 = evalCurrentBoard(copy);
//       if (copyEval_1 > currentBest_1) {
//          currentBest_1 = copyEval_1;
//          chosenMove = moves_1[i];
//       }
//    }
//    return chosenMove;
// }


// int oneLookMaxScore(board b, int currentBest) {
//    move *moves_1;
//    int numMoves_1;
//    int i;
//    int currentBest_1 = -2000;
//    board firstCopy = b;
//    move chosenMove;
//    board copy = b;
//    moves_1 = efficientGenMoves(b,&numMoves_1);
//    if (numMoves_1 == 0) {
//       if (!isPlayerInCheck(copy) && evalCurrentBoard(copy) < 0) {
//          currentBest_1 = 1900;
//       }
//    }
//    else {
//       movePiece(&firstCopy,moves_1[0], 0);
//       currentBest_1 = evalCurrentBoard(firstCopy);
//       chosenMove = moves_1[0];
//       for (i=0;i<numMoves_1;i++) {
//          int copyEval_1;
//          copy = b;
//          movePiece(&copy,moves_1[i], 0);
//          copyEval_1 = evalCurrentBoard(copy);
//          if (copyEval_1 > currentBest_1) {
//             currentBest_1 = copyEval_1;
//             chosenMove = moves_1[i];
//          }
//          if (copyEval_1 >= currentBest) {break;}
//       }
//    }
//    free(moves_1);
//    return currentBest_1;
// }

// int oneLookMinScore(board b, int currentBest) {
//    move *moves_1;
//    int numMoves_1;
//    int i;
//    int currentBest_1 = 2000;
//    board firstCopy = b;
//    move chosenMove;
//    board copy = b;
//    moves_1 = efficientGenMoves(b,&numMoves_1);
//    if (numMoves_1 == 0) {
//       if (!isPlayerInCheck(copy) && evalCurrentBoard(copy) > 0) {
//          currentBest_1 = -1900;
//       }
//    }
//    else {
//       movePiece(&firstCopy,moves_1[0], 0);
//       currentBest_1 = evalCurrentBoard(firstCopy);
//       chosenMove = moves_1[0];
//       for (i=0;i<numMoves_1;i++) {
//          int copyEval_1;
//          copy = b;
//          movePiece(&copy,moves_1[i], 0);
//          copyEval_1 = evalCurrentBoard(copy);
//          if (copyEval_1 < currentBest_1) {
//             currentBest_1 = copyEval_1;
//             chosenMove = moves_1[i];
//          }
//          if (copyEval_1 <= currentBest) {break;}
//       }
//    }
//    free(moves_1);
//    return currentBest_1;
// }

