#include <stdio.h>
#include <string.h>

// Criando a struct Territorio
// Essa estrutura agrupa informações relacionadas a um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {

    // Vetor para armazenar 5 territórios
    Territorio territorios[5];

    int i;

    // Entrada de dados dos territórios
    for(i = 0; i < 5; i++) {

        printf("\n=== Cadastro do Territorio %d ===\n", i + 1);

        // Leitura do nome do território
        printf("Digite o nome do territorio: ");
        scanf(" %[^\n]", territorios[i].nome);

        // Leitura da cor do exército
        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].cor);

        // Leitura da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos dados cadastrados
    printf("\n======= TERRITORIOS CADASTRADOS =======\n");

    // Laço para mostrar todos os territórios cadastrados
    for(i = 0; i < 5; i++) {

        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}