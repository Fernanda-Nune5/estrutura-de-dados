#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct do item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Função para cadastrar item
void inserirItem(Item mochila[], int *total) {

    if(*total >= 10) {
        printf("\nMochila cheia!\n");
        return;
    }

    printf("\n=== CADASTRO DE ITEM ===\n");

    printf("Nome do item: ");
    scanf(" %[^\n]", mochila[*total].nome);

    printf("Tipo do item: ");
    scanf(" %[^\n]", mochila[*total].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);

    (*total)++;

    printf("\nItem cadastrado com sucesso!\n");
}

// Função para listar itens
void listarItens(Item mochila[], int total) {

    if(total == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    printf("\n======= ITENS DA MOCHILA =======\n");

    for(int i = 0; i < total; i++) {

        printf("\nItem %d\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
}

// Função de busca sequencial
void buscarItem(Item mochila[], int total) {

    char nomeBusca[30];
    int encontrado = 0;

    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", nomeBusca);

    for(int i = 0; i < total; i++) {

        if(strcmp(mochila[i].nome, nomeBusca) == 0) {

            printf("\n=== ITEM ENCONTRADO ===\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);

            encontrado = 1;
            break;
        }
    }

    if(!encontrado) {
        printf("\nItem nao encontrado!\n");
    }
}

// Função para remover item
void removerItem(Item mochila[], int *total) {

    char nomeRemover[30];
    int encontrado = 0;

    printf("\nDigite o nome do item para remover: ");
    scanf(" %[^\n]", nomeRemover);

    for(int i = 0; i < *total; i++) {

        if(strcmp(mochila[i].nome, nomeRemover) == 0) {

            // Move os itens para trás
            for(int j = i; j < *total - 1; j++) {

                mochila[j] = mochila[j + 1];
            }

            (*total)--;

            printf("\nItem removido com sucesso!\n");

            encontrado = 1;
            break;
        }
    }

    if(!encontrado) {
        printf("\nItem nao encontrado!\n");
    }
}

int main() {

    Item mochila[10];

    int totalItens = 0;
    int opcao;

    do {

        printf("\n======= MENU =======\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:
                inserirItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;

            case 2:
                removerItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;

            case 3:
                listarItens(mochila, totalItens);
                break;

            case 4:
                buscarItem(mochila, totalItens);
                break;

            case 0:
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}