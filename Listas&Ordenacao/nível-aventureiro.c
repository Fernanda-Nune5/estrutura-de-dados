#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

// ===================== STRUCT ITEM =====================

struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// ===================== LISTA ENCADEADA =====================

struct No {
    struct Item dados;
    struct No* proximo;
};

// ===================== VARIÁVEIS GLOBAIS =====================

// Vetor
struct Item mochilaVetor[MAX];
int totalItens = 0;

// Lista encadeada
struct No* inicio = NULL;

// Contadores
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ===================== FUNÇÕES DO VETOR =====================

// Inserir item no vetor
void inserirItemVetor() {

    if (totalItens >= MAX) {
        printf("\nMochila cheia!\n");
        return;
    }

    printf("\nNome do item: ");
    scanf(" %[^\n]", mochilaVetor[totalItens].nome);

    printf("Tipo do item: ");
    scanf(" %[^\n]", mochilaVetor[totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochilaVetor[totalItens].quantidade);

    totalItens++;

    printf("\nItem inserido com sucesso!\n");
}

// Listar itens do vetor
void listarItensVetor() {

    if (totalItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    printf("\n===== ITENS NO VETOR =====\n");

    for (int i = 0; i < totalItens; i++) {

        printf("\nItem %d\n", i + 1);
        printf("Nome: %s\n", mochilaVetor[i].nome);
        printf("Tipo: %s\n", mochilaVetor[i].tipo);
        printf("Quantidade: %d\n", mochilaVetor[i].quantidade);
    }
}

// Remover item do vetor
void removerItemVetor() {

    char nome[30];
    int encontrado = 0;

    printf("\nDigite o nome do item para remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < totalItens; i++) {

        if (strcmp(mochilaVetor[i].nome, nome) == 0) {

            encontrado = 1;

            // Desloca os elementos
            for (int j = i; j < totalItens - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }

            totalItens--;

            printf("\nItem removido!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem nao encontrado!\n");
    }
}

// Busca sequencial no vetor
void buscarSequencialVetor() {

    char nome[30];
    int encontrado = 0;

    comparacoesSequencial = 0;

    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < totalItens; i++) {

        comparacoesSequencial++;

        if (strcmp(mochilaVetor[i].nome, nome) == 0) {

            encontrado = 1;

            printf("\n===== ITEM ENCONTRADO =====\n");
            printf("Nome: %s\n", mochilaVetor[i].nome);
            printf("Tipo: %s\n", mochilaVetor[i].tipo);
            printf("Quantidade: %d\n", mochilaVetor[i].quantidade);

            break;
        }
    }

    if (!encontrado) {
        printf("\nItem nao encontrado!\n");
    }

    printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
}

// Ordenar vetor por nome (Bubble Sort)
void ordenarVetor() {

    struct Item temp;

    for (int i = 0; i < totalItens - 1; i++) {

        for (int j = 0; j < totalItens - 1 - i; j++) {

            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {

                temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }

    printf("\nItens ordenados com sucesso!\n");
}

// Busca binária no vetor
void buscaBinariaVetor() {

    char nome[30];

    int inicioBusca = 0;
    int fim = totalItens - 1;
    int encontrado = 0;

    comparacoesBinaria = 0;

    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", nome);

    while (inicioBusca <= fim) {

        comparacoesBinaria++;

        int meio = (inicioBusca + fim) / 2;

        int resultado = strcmp(mochilaVetor[meio].nome, nome);

        if (resultado == 0) {

            encontrado = 1;

            printf("\n===== ITEM ENCONTRADO =====\n");
            printf("Nome: %s\n", mochilaVetor[meio].nome);
            printf("Tipo: %s\n", mochilaVetor[meio].tipo);
            printf("Quantidade: %d\n", mochilaVetor[meio].quantidade);

            break;
        }

        else if (resultado < 0) {
            inicioBusca = meio + 1;
        }

        else {
            fim = meio - 1;
        }
    }

    if (!encontrado) {
        printf("\nItem nao encontrado!\n");
    }

    printf("Comparacoes realizadas: %d\n", comparacoesBinaria);
}

// ===================== FUNÇÕES DA LISTA =====================

// Inserir item na lista
void inserirItemLista() {

    struct No* novo = (struct No*) malloc(sizeof(struct No));

    printf("\nNome do item: ");
    scanf(" %[^\n]", novo->dados.nome);

    printf("Tipo do item: ");
    scanf(" %[^\n]", novo->dados.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = inicio;
    inicio = novo;

    printf("\nItem inserido na lista!\n");
}

// Listar itens da lista
void listarItensLista() {

    struct No* atual = inicio;

    if (inicio == NULL) {
        printf("\nLista vazia!\n");
        return;
    }

    printf("\n===== ITENS DA LISTA =====\n");

    while (atual != NULL) {

        printf("\nNome: %s\n", atual->dados.nome);
        printf("Tipo: %s\n", atual->dados.tipo);
        printf("Quantidade: %d\n", atual->dados.quantidade);

        atual = atual->proximo;
    }
}

// Buscar item na lista
void buscarItemLista() {

    char nome[30];

    struct No* atual = inicio;

    int encontrado = 0;
    int comparacoes = 0;

    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", nome);

    while (atual != NULL) {

        comparacoes++;

        if (strcmp(atual->dados.nome, nome) == 0) {

            encontrado = 1;

            printf("\n===== ITEM ENCONTRADO =====\n");
            printf("Nome: %s\n", atual->dados.nome);
            printf("Tipo: %s\n", atual->dados.tipo);
            printf("Quantidade: %d\n", atual->dados.quantidade);

            break;
        }

        atual = atual->proximo;
    }

    if (!encontrado) {
        printf("\nItem nao encontrado!\n");
    }

    printf("Comparacoes realizadas: %d\n", comparacoes);
}

// Remover item da lista
void removerItemLista() {

    char nome[30];

    printf("\nDigite o nome do item para remover: ");
    scanf(" %[^\n]", nome);

    struct No* atual = inicio;
    struct No* anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {

        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {

        printf("\nItem nao encontrado!\n");
        return;
    }

    // Remove primeiro nó
    if (anterior == NULL) {
        inicio = atual->proximo;
    }

    // Remove do meio/final
    else {
        anterior->proximo = atual->proximo;
    }

    free(atual);

    printf("\nItem removido da lista!\n");
}

// ===================== MENU =====================

int main() {

    int opcao;

    do {

        printf("\n========== MENU ==========\n");

        printf("\n--- VETOR ---\n");
        printf("1 - Inserir item no vetor\n");
        printf("2 - Remover item do vetor\n");
        printf("3 - Listar itens do vetor\n");
        printf("4 - Busca sequencial no vetor\n");
        printf("5 - Ordenar vetor\n");
        printf("6 - Busca binaria no vetor\n");

        printf("\n--- LISTA ENCADEADA ---\n");
        printf("7 - Inserir item na lista\n");
        printf("8 - Remover item da lista\n");
        printf("9 - Listar itens da lista\n");
        printf("10 - Buscar item na lista\n");

        printf("\n0 - Sair\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:
                inserirItemVetor();
                break;

            case 2:
                removerItemVetor();
                break;

            case 3:
                listarItensVetor();
                break;

            case 4:
                buscarSequencialVetor();
                break;

            case 5:
                ordenarVetor();
                break;

            case 6:
                buscaBinariaVetor();
                break;

            case 7:
                inserirItemLista();
                break;

            case 8:
                removerItemLista();
                break;

            case 9:
                listarItensLista();
                break;

            case 10:
                buscarItemLista();
                break;

            case 0:
                printf("\nEncerrando programa...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}