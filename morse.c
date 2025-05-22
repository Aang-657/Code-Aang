#include "NB_Tree.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void InitMorseTree(Isi_Tree X) {
    Create_tree(X, jml_maks);
    
    struct {
        int index;
        char info;
        int fs;  // Anak kiri (*)
        int nb;  // Anak kanan (~)
        int pr;
    } nodes[] = {
        {1, '\0', 2, 3, 0},   // Root: fs = kiri (*), nb = kanan (~)
        {2, 'V', 4, 5, 1},   // fs = S (*), nb = Z (~)
        {3, 'U', 6, 7, 1},   // fs = K (*), nb = Y (~)
        {4, 'S', 8, 9, 2},    // fs = B (*), nb = E (~)
        {5, 'Z', 10, 11, 2}, // fs = D (*), nb = N (~)
        {6, 'K', 12, 13, 3},  // fs = W (*), nb = F (~)
        {7, 'Y', 14, 15, 3},  // fs = Q (*), nb = L (~)
        {8, 'B', 16, 17, 4},  // fs = O (*), nb = P (~)
        {9, 'E', 18, 19, 4},  // fs = C (*), nb = I (~)
        {10, 'D', 20, 21, 5},// fs = A (*), nb = H (~)
        {11, 'N', 22, 23, 5}, // fs = G (*), nb = M (~)
        {12, 'W', 24, 25, 6}, // fs = J (*), nb = T (~)
        {13, 'F', 26, 27, 6}, // fs = R (*), nb = X (~)
        {14, 'Q', 28, 29, 7}, // fs = 8 (*), nb = 9 (~)
        {15, 'L', 30, 31, 7}, // fs = 5 (*), nb = 2 (~)
        {16, 'O', 32, 33, 8}, // fs = 4 (*), nb = 0 (~)
        {17, 'P', 0, 0, 8},   // daun
        {18, 'C', 34, 0, 9},  // fs = 3 (*)
        {19, 'I', 0, 0, 9},   // daun
        {20, 'A', 0, 0, 10},  // daun
        {21, 'H', 0, 0, 10},  // daun
        {22, 'G', 0, 0, 11},  // daun
        {23, 'M', 0, 0, 11},  // daun
        {24, 'J', 0, 0, 12},  // daun
        {25, 'T', 0, 0, 12},  // daun
        {26, 'R', 0, 0, 13},  // daun
        {27, 'X', 35, 36, 13},// fs = 1 (*), nb = 7 (~)
        {28, '8', 0, 0, 14},  // daun
        {29, '9', 37, 0, 14}, // fs = spasi (*)
        {30, '5', 0, 0, 15},  // daun
        {31, '2', 0, 0, 15},  // daun
        {32, '4', 0, 0, 16},  // daun
        {33, '0', 0, 0, 16},  // daun
        {34, '3', 0, 0, 18},  // daun
        {35, '1', 0, 0, 27},  // daun
        {36, '7', 0, 0, 27},  // daun
        {37, ' ', 0, 38, 29}, // nb = 6 (~)
        {38, '6', 0, 0, 29}   // daun
    };

    for (int i = 0; i < 38; i++) {
        X[nodes[i].index].info = nodes[i].info;
        X[nodes[i].index].ps_fs = nodes[i].fs;
        X[nodes[i].index].ps_nb = nodes[i].nb;
        X[nodes[i].index].ps_pr = nodes[i].pr;
    }
    X[0].ps_fs = 1; // Inisialisasi root
}

void GetMorseCode(Isi_Tree X, char c, char *morse, int *len) {
    c = toupper(c);
    if (c == ' ') c = ' ';
    else if (c < '0' || (c > '9' && c < 'A') || c > 'Z') return;

    int idx = 0;
    for (int i = 1; i <= jml_maks; i++) {
        if (X[i].info == c) {
            idx = i;
            break;
        }
    }

    *len = 0;
    while (idx != 0 && X[idx].ps_pr != 0) {
        if (X[X[idx].ps_pr].ps_fs == idx) {
            morse[(*len)++] = '*'; // Anak kiri = titik
        } else {
            morse[(*len)++] = '~'; // Anak kanan = garis
        }
        idx = X[idx].ps_pr;
    }

    for (int i = 0; i < *len / 2; i++) {
        char temp = morse[i];
        morse[i] = morse[*len - 1 - i];
        morse[*len - 1 - i] = temp;
    }
    morse[*len] = '\0';
}

void StringToMorse(Isi_Tree X, const char *str, char *result) {
    result[0] = '\0';
    char morse[10];
    int len;

    for (int i = 0; str[i]; i++) {
        GetMorseCode(X, str[i], morse, &len);
        if (len > 0) {
            strcat(result, morse);
            if (str[i+1]) strcat(result, "  ");
        }
    }
}

void MorseToString(Isi_Tree X, const char *morse, char *result) {
    result[0] = '\0';
    char temp[10];
    int temp_idx = 0;
    int result_idx = 0;
    int idx;

    printf("Debug: Mulai traversal untuk kode %s\n", morse);
    for (int i = 0; morse[i]; i++) {
        if (morse[i] == ' ') {
            if (temp_idx > 0) {
                temp[temp_idx] = '\0';
                idx = 1; // Reset ke root
                printf("Debug: Memproses kode %s\n", temp);
                for (int j = 0; temp[j]; j++) {
                    printf("Debug: Karakter %c, indeks saat ini: %d\n", temp[j], idx);
                    if (temp[j] == '*') {
                        idx = X[idx].ps_fs; // Anak kiri
                        printf("Debug: Bergerak ke first son (kiri), indeks baru: %d\n", idx);
                    } else if (temp[j] == '~') {
                        idx = X[idx].ps_nb; // Anak kanan
                        printf("Debug: Bergerak ke next brother (kanan), indeks baru: %d\n", idx);
                    } else {
                        printf("Debug: Karakter %c tidak valid\n", temp[j]);
                        return;
                    }
                    if (idx == 0) {
                        printf("Debug: Kode %s tidak valid, mencapai indeks 0\n", temp);
                        return;
                    }
                }
                printf("Debug: Mencapai node dengan info: %c\n", X[idx].info);
                result[result_idx++] = X[idx].info;
                temp_idx = 0;
            }
            continue;
        }
        temp[temp_idx++] = morse[i];
    }

    // Proses kode terakhir
    if (temp_idx > 0) {
        temp[temp_idx] = '\0';
        idx = 1; // Reset ke root
        printf("Debug: Memproses kode %s\n", temp);
        for (int j = 0; temp[j]; j++) {
            printf("Debug: Karakter %c, indeks saat ini: %d\n", temp[j], idx);
            if (temp[j] == '*') {
                idx = X[idx].ps_fs;
                printf("Debug: Bergerak ke first son (kiri), indeks baru: %d\n", idx);
            } else if (temp[j] == '~') {
                idx = X[idx].ps_nb;
                printf("Debug: Bergerak ke next brother (kanan), indeks baru: %d\n", idx);
            } else {
                printf("Debug: Karakter %c tidak valid\n", temp[j]);
                return;
            }
            if (idx == 0) {
                printf("Debug: Kode %s tidak valid, mencapai indeks 0\n", temp);
                return;
            }
        }
        printf("Debug: Mencapai node dengan info: %c\n", X[idx].info);
        result[result_idx++] = X[idx].info;
    }
    result[result_idx] = '\0';
}

void ProcessFile(Isi_Tree X, const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    if (!in) {
        printf("Error: Tidak dapat membuka file input %s\n", inputFile);
        return;
    }
    FILE *out = fopen(outputFile, "w");
    if (!out) {
        printf("Error: Tidak dapat membuka file output %s\n", outputFile);
        fclose(in);
        return;
    }

    char line[256];
    char morseResult[1024];
    while (fgets(line, sizeof(line), in)) {
        line[strcspn(line, "\n")] = 0;
        StringToMorse(X, line, morseResult);
        fprintf(out, "%s\n", morseResult);
    }

    fclose(in);
    fclose(out);
}

int main() {
    Isi_Tree morseTree;
    
    // 1. Membuat binary tree Morse
    InitMorseTree(morseTree);
    PrintTree(morseTree); // Debugging: Periksa struktur pohon
    PrintTreeVisual(morseTree); // Tambahan debugging untuk visualisasi pohon

    // 2. Menampilkan semua node dengan traversal inorder
    printf("Inorder Traversal:\n");
    InOrder(morseTree);
    printf("\n\n");

    // 3. Mengkonversi string "JTK Politeknik Negeri Bandung" ke Morse
    char result[256];
    StringToMorse(morseTree, "JTK Politeknik Negeri Bandung", result);
    printf("Kode Morse untuk 'JTK Politeknik Negeri Bandung':\n%s\n\n", result);

    // 4. Mengkonversi kode Morse ke string
    char *morseCode = "*~** *~** *~~ *~~*"; // Kode untuk "aang"
    char morseResult[256];
    MorseToString(morseTree, morseCode, morseResult);
    printf("Kode Morse %s diterjemahkan ke: %s\n\n", morseCode, morseResult);

    // 5. Membaca input.txt dan menyimpan ke out.txt
    ProcessFile(morseTree, "input.txt", "out.txt");
    printf("Konversi file selesai. Hasil disimpan di out.txt\n");

    return 0;
}