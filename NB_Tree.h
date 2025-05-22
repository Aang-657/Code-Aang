#ifndef NB_Tree_h
#define NB_Tree_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define jml_maks 38
#define kebawah  1
#define keatas   2
#define kekanan  3
#define nil   0

typedef char infotype;
typedef int address;

typedef struct {
    infotype info;
    address ps_fs;  // first son (Right son)
    address ps_nb;  // next brother (Left son)
    address ps_pr;  // parent
} nbtree;

typedef nbtree Isi_Tree[jml_maks + 1];

void Create_tree(Isi_Tree X, int Jml_Node);
bool IsEmpty (Isi_Tree P);

void PreOrder (Isi_Tree P);
void InOrder (Isi_Tree P);
void PostOrder (Isi_Tree P);
void Level_order(Isi_Tree X, int Maks_node);
void PrintTree (Isi_Tree P);
void PrintTreeVisual(Isi_Tree P);

bool Search (Isi_Tree P, infotype X);

int nbElmt (Isi_Tree P);
int nbDaun (Isi_Tree P);
int Level (Isi_Tree P, infotype X);
int Depth (Isi_Tree P);
int Max (int a, int b);

#endif
