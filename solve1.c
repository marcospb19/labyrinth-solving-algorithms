#include <stdbool.h>
#include <stdio.h>

/*
0 1 1 1 1 1 1
0 0 1 1 0 1 1
1 0 0 0 0 1 1
1 1 1 1 0 0 1
1 1 1 1 1 0 0
*/

bool is_there_path_at(int altura, int largura, int labirinto[altura][largura], int i, int j) {
    return 0 <= i && i < altura && 0 <= j && j < largura && labirinto[i][j] == 0;
}

void traverse(int altura, int largura, int labirinto[altura][largura],
              bool visited[altura][largura], int i, int j) {
    if (visited[i][j]) {
        return;
    }
    visited[i][j] = true;

    if (is_there_path_at(altura, largura, labirinto, i - 1, j)) {
        traverse(altura, largura, labirinto, visited, i - 1, j);
    }
    if (is_there_path_at(altura, largura, labirinto, i + 1, j)) {
        traverse(altura, largura, labirinto, visited, i + 1, j);
    }
    if (is_there_path_at(altura, largura, labirinto, i, j + 1)) {
        traverse(altura, largura, labirinto, visited, i, j + 1);
    }
    if (is_there_path_at(altura, largura, labirinto, i, j - 1)) {
        traverse(altura, largura, labirinto, visited, i, j - 1);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "erro: especifique um arquivo.\n");
        return 1;
    }

    FILE *arquivo = fopen(argv[1], "r");
    if (!arquivo) {
        fprintf(stderr, "erro: arquivo nao encontrado.\n");
        return 2;
    }

    int altura = 5;
    int largura = 7;
    int labirinto[altura][largura];
    bool visited[altura][largura];
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            fscanf(arquivo, "%d", &labirinto[i][j]);
            visited[i][j] = false;
        }
    }
    fclose(arquivo);

    // Traverse everything possible from (0, 0)
    traverse(altura, largura, labirinto, visited, 0, 0);

    // If the target was visited, we did it!
    if (visited[altura - 1][largura - 1]) {
        puts("True");
    } else {
        puts("False");
    }

    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            printf("%d", visited[i][j]);
        }
        puts("");
    }
}
