#include <stdio.h>
#include <stdlib.h>


PVTree pvInit() {
   move m = {0,0,0,0,0,0,0,0};
   PVTree out = {0, 0, m, NULL};
   return out;
}

PVTree *pvArrInit(int size) {
   move m = {0,0,0,0,0,0,0,0};
   PVTree element = {0,0,m,NULL};
   PVTree *out;
   int i;

   out = (PVTree *)malloc(size*sizeof(PVTree));

   for (i=0;i<size;i++) {
      out[i] = element;
   }
   return out;
}

PVTree *cleanUpTree(PVTree *node, move m) {
   int size = node->size;
   int i;
   PVTree temp = pvInit();
   PVTree *out;
   if (node == NULL) {return node;}
   if (node->children == NULL) {return node;}

   for (i=0;i<size; i++) {
      if ((m.from == node->children[i].m.from) && (m.to == node->children[i].m.to)) {
         temp.score = node->children[i].score;
         temp.size = node->children[i].size;
         temp.m = node->children[i].m;
         temp.children = node->children[i].children;
      }
      else {
         freeAll(&(node->children[i]));

      }
   }

   out = (PVTree *)malloc(1*sizeof(PVTree));
   *out = temp;

   return out;
}

void freeAll(PVTree *node) {
   int size = node->size;
   int i;

   if (node->children == NULL) {return;}
   for (i=0;i<size;i++) {
      freeAll(&(node->children[i]));
   }
   free(node->children);
   return;
}


int printOneTreeBranch(PVTree *node) {
   if (node != NULL) {
      printf("[%d->%d; %d]\n", node->m.from, node->m.to, node->score);
      printOneTreeBranch(&(node->children[0]));
   }
   return 1;
}



