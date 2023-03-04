#include <stdio.h>
#include <stdlib.h>





int evalCurrentBoard(board b) {
   int sum = 0;
   int i;

   for (i=0;i<64;i++) {
      if (b.store[i] == 10) {
         sum += 10;

         if (i/8 == 6) {sum += 21;}
         else if (i/8 == 5) {sum += 8;}
         else if (i/8 == 4) {sum += 3;}
         else if (i/8 == 3) {sum += 1;}
      }
      else if (b.store[i] == 11) {
         sum += 30;

         if ((i%8 >= 2 && i%8 <= 5) && (i/8 >= 2 && i/8 <= 5)) {sum += 2;}
         else if ((i%8 >= 1 && i%8 <= 6) && (i/8 >= 1 && i/8 <= 6)) {sum += 1;}
      }
      else if (b.store[i] == 12) {
         sum += 30;

         if (i%8 == 3 || i%8 == 4) {sum += 2;}
         else if (i%8 == 2 || i%8 == 5) {sum += 1;}

         if (i/8 == 4) {sum += 2;}
         else if (i/8 == 5) {sum += 2;}
         else if (i/8 == 3 || i/8 == 2 || i/8 == 6) {sum += 1;}
      }
      else if (b.store[i] == 13) {
         sum += 50;
         if (i%8 == 3 || i%8 == 4) {sum += 3;}
         else if (i%8 == 2 || i%8 == 5) {sum += 2;}
         else if (i%8 == 1 || i*8 == 6) {sum += 1;}
      
         if (i/8 == 4) {sum += 3;}
         else if (i/8 == 5 || i/8 == 6) {sum += 2;}
         else if (i/8 == 3 || i/8 == 7) {sum += 1;}
         else if (i/8 == 2) {sum += 1;}
      }
      else if (b.store[i] == 14) {
         sum += 90;
         if (i%8 == 3 || i%8 == 4) {sum += 4;}
         else if (i%8 == 2 || i%8 == 5) {sum += 2;}
         else if (i%8 == 1 || i%8 == 6) {sum += 1;}

         if (i/8 == 4) {sum += 5;}
         else if (i/8 == 5) {sum += 4;}
         else if (i/8 == 3) {sum += 3;}
         else if (i/8 == 2) {sum += 2;}
         else if (i/8 == 1) {sum += 1;}

         //Penalty for moving queen early
         

      }
      else if (b.store[i] == 15) {sum += 900;}
      else if (b.store[i] == 20) {
         sum -= 10;

         if (i/8 == 1) {sum -= 21;}
         else if (i/8 == 2) {sum -= 8;}
         else if (i/8 == 3) {sum -= 3;}
         else if (i/8 == 4) {sum -= 1;}
      }
      else if (b.store[i] == 21) {
         sum -= 30;

         if ((i%8 >= 2 && i%8 <= 5) && (i/8 >= 2 && i/8 <= 5)) {sum -= 2;}
         else if ((i%8 >= 1 && i%8 <= 6) && (i/8 >= 1 && i/8 <= 6)) {sum -= 1;}
      }
      else if (b.store[i] == 22) {
         sum -= 30;

         if (i%8 == 3 || i%8 == 4) {sum -= 2;}
         else if (i%8 == 2 || i%8 == 5) {sum -= 1;}

         if (i/8 == 3) {sum -= 2;}
         else if (i/8 == 2) {sum -= 2;}
         else if (i/8 == 4 || i/8 == 5 || i/8 == 1) {sum -= 1;}
      }
      else if (b.store[i] == 23) {
         sum -= 50;

         if (i%8 == 3 || i%8 == 4) {sum -= 3;}
         else if (i%8 == 2 || i%8 == 5) {sum -= 2;}
         else if (i%8 == 1 || i*8 == 6) {sum -= 1;}

         if (i/8 == 3) {sum -= 3;}
         else if (i/8 == 2 || i/8 == 1) {sum -= 2;}
         else if (i/8 == 4 || i/8 == 0) {sum -= 1;}
         else if (i/8 == 5) {sum -= 1;}
      }
      else if (b.store[i] == 24) {
         sum -= 90;
         if (i%8 == 3 || i%8 == 4) {sum -= 4;}
         else if (i%8 == 2 || i%8 == 5) {sum -= 2;}
         else if (i%8 == 1 || i%8 == 6) {sum -= 1;}
      
         if (i/8 == 3) {sum -= 5;}
         else if (i/8 == 2) {sum -= 4;}
         else if (i/8 == 4) {sum -= 3;}
         else if (i/8 == 5) {sum -= 2;}
         else if (i/8 == 6) {sum -= 1;}

      }
      else if (b.store[i] == 25) {sum -= 900;}
   }
   if (b.wCastleL == 1) {sum += 2;}
   if (b.wCastleR == 1) {sum += 2;}
   if (b.bCastleL == 1) {sum -= 2;}
   if (b.bCastleR == 1) {sum -= 2;}
   
   if (b.wHasCastled == 1) {sum += 9;}
   if (b.bHasCastled == 1) {sum -= 9;}

   //sum += 2*earlyQueenPenalty(b, b.turnNumber);
   return sum;
}

//IDK how valuable this is for the increase in search time

int earlyQueenPenalty(board b, int turnNumber) {
   int i;
   board curBoard = b;
   move m;
   int accumulatedPenalty = 0;

   if (turnNumber > 10 || turnNumber < 3) {return 0;}

   //if (curBoard.previousBoard == NULL) {printf("IT IS NULL! AT TURN: %d\n", turnNumber);}
   //printf("now: %d\n", curBoard.previousBoard);

   //return 0;
   for (i=0;i<turnNumber;i++) {
      m = curBoard.previousMove;
      if (b.store[m.to] == 14) {
         //White moved queen, subtract points
         accumulatedPenalty -= 15-(turnNumber-i);
      }
      else if (b.store[m.to] == 24) {
         //Black moved queen, add points
         accumulatedPenalty += 15-(turnNumber-i);
      }
      curBoard = *(curBoard.previousBoard);
   }
   return accumulatedPenalty;
}
