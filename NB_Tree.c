#include "NB_Tree.h"

void Create_tree(Isi_Tree X, int Jml_Node) {
    for (int i = 0; i <= jml_maks; i++) {
        X[i].info = '\0'; // Inisialisasi dengan '\0' untuk node kosong
        X[i].ps_fs = nil;
        X[i].ps_nb = nil;
        X[i].ps_pr = nil;
    }
}

bool IsEmpty(Isi_Tree P) {
    return (P[0].ps_fs == nil);
}

/*** Traversal ***/

void PreOrderNode(Isi_Tree P, int idx) {
    if (idx != nil && P[idx].info != '\0') {
        printf("%c ", P[idx].info);
        PreOrderNode(P, P[idx].ps_fs);  // Anak kiri
        PreOrderNode(P, P[idx].ps_nb);  // Anak kanan
    }
}
void PreOrder(Isi_Tree P) {
    printf("Debug: Memulai PreOrder, ps_fs[0] = %d\n", P[0].ps_fs);
    if (!IsEmpty(P)) {
        PreOrderNode(P, P[0].ps_fs);
    } else {
        printf("Debug: Pohon kosong\n");
    }
}

void InOrderNode(Isi_Tree P, int idx) {
    if (idx != nil && P[idx].info != '\0') {
        InOrderNode(P, P[idx].ps_fs);   // Anak kiri
        printf("%c ", P[idx].info);
        InOrderNode(P, P[idx].ps_nb);   // Anak kanan
    }
}
void InOrder(Isi_Tree P) {
    printf("Debug: Memulai InOrder, ps_fs[0] = %d\n", P[0].ps_fs);
    if (!IsEmpty(P)) {
        InOrderNode(P, P[0].ps_fs);
    } else {
        printf("Debug: Pohon kosong\n");
    }
}

void PostOrderNode(Isi_Tree P, int idx) {
    if (idx != nil && P[idx].info != '\0') {
        PostOrderNode(P, P[idx].ps_fs);  // Anak kiri
        PostOrderNode(P, P[idx].ps_nb);  // Anak kanan
        printf("%c ", P[idx].info);
    }
}
void PostOrder(Isi_Tree P) {
    printf("Debug: Memulai PostOrder, ps_fs[0] = %d\n", P[0].ps_fs);
    if (!IsEmpty(P)) {
        PostOrderNode(P, P[0].ps_fs);
    } else {
        printf("Debug: Pohon kosong\n");
    }
}

void Level_order(Isi_Tree X, int Maks_node) {
    for (int i = 1; i <= Maks_node; i++) {
        if (X[i].info != '\0') {
            printf("%c ", X[i].info);
        }
    }
}

void PrintTree(Isi_Tree P) {
    printf("Seluruh Node pada Binary Tree Morse:\n\n");

    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].info != '\0') {
            printf("--> Indeks ke-%d\n", i);
            printf("--------------------------------------------------\n");
            printf("info array ke %d        : %c\n", i, P[i].info);
            printf("first son (kiri) ke %d  : %d\n", i, P[i].ps_fs);
            printf("next brother (kanan) ke %d: %d\n", i, P[i].ps_nb);
            printf("parent array ke %d      : %d\n", i, P[i].ps_pr);
            printf("--------------------------------------------------\n\n");
        }
    }
}

/*** Search ***/

bool SearchNode(Isi_Tree P, int idx, infotype X) {
    if (idx == nil || P[idx].info == '\0') return false;
    if (P[idx].info == X) return true;
    return SearchNode(P, P[idx].ps_fs, X) || SearchNode(P, P[idx].ps_nb, X);
}

bool Search(Isi_Tree P, infotype X) {
    if (IsEmpty(P)) return false;
    return SearchNode(P, P[0].ps_fs, X);
}

/*** Fungsi Lain ***/

int CountAll(Isi_Tree P, int idx) {
    if (idx == nil || P[idx].info == '\0') return 0;
    return 1 + CountAll(P, P[idx].ps_fs) + CountAll(P, P[idx].ps_nb);
}

int nbElmt(Isi_Tree P) {
    if (IsEmpty(P)) return 0;
    return CountAll(P, P[0].ps_fs);
}

int CountLeaves(Isi_Tree P, int idx) {
    if (idx == nil || P[idx].info == '\0') return 0;
    if (P[idx].ps_fs == nil && P[idx].ps_nb == nil) return 1;
    return CountLeaves(P, P[idx].ps_fs) + CountLeaves(P, P[idx].ps_nb);
}

int nbDaun(Isi_Tree P) {
    if (IsEmpty(P)) return 0;
    return CountLeaves(P, P[0].ps_fs);
}

int LevelNode(Isi_Tree P, int idx, infotype X, int current_level) {
    if (idx == nil || P[idx].info == '\0') return -1;
    if (P[idx].info == X) return current_level;

    int child_result = LevelNode(P, P[idx].ps_fs, X, current_level + 1);
    if (child_result != -1) return child_result;

    return LevelNode(P, P[idx].ps_nb, X, current_level);
}

int Level(Isi_Tree P, infotype X) {
    if (IsEmpty(P)) return -1;
    return LevelNode(P, P[0].ps_fs, X, 0);
}

int DepthNode(Isi_Tree P, int idx) {
    if (idx == nil || P[idx].info == '\0') return -1;

    int left_depth = DepthNode(P, P[idx].ps_fs);
    int right_depth = DepthNode(P, P[idx].ps_nb);
    return 1 + (left_depth > right_depth ? left_depth : right_depth);
}

int Depth(Isi_Tree P) {
    if (IsEmpty(P)) return -1;
    return DepthNode(P, P[0].ps_fs);
}

int Max(int a, int b) {
    return (a > b) ? a : b;
}

void PrintVisual(Isi_Tree P, int idx, char *prefix, bool isLast) {
    if (idx == nil || P[idx].info == '\0') return;

    printf("%s", prefix);

    if (isLast) {
        printf("`-");
    } else {
        printf("|-");
    }

    printf("%c\n", P[idx].info);

    // Buat prefix baru untuk anak-anak
    char newPrefix[100];
    sprintf(newPrefix, "%s%s", prefix, isLast ? "  " : "| ");

    // Cetak anak kiri dan kanan
    PrintVisual(P, P[idx].ps_fs, newPrefix, P[idx].ps_nb == nil);
    PrintVisual(P, P[idx].ps_nb, newPrefix, true);
}

void PrintTreeVisual(Isi_Tree P) {
    printf("Visualisasi Pohon Biner Morse:\n");
    if (!IsEmpty(P)) {
        PrintVisual(P, P[0].ps_fs, "", true);
    } else {
        printf("Pohon kosong\n");
    }
}