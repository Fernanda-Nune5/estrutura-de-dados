#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   ESTRUTURA DAS SALAS
========================= */

typedef struct Sala {
    char nome[50];
    char pista[100];

    struct Sala* esquerda;
    struct Sala* direita;

} Sala;

/* =========================
   ESTRUTURA DA BST
========================= */

typedef struct PistaNode {
    char pista[100];

    struct PistaNode* esquerda;
    struct PistaNode* direita;

} PistaNode;

/* =========================
   CRIAR SALA
========================= */

Sala* criarSala(char nome[], char pista[]) {

    Sala* nova = (Sala*) malloc(sizeof(Sala));

    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);

    nova->esquerda = NULL;
    nova->direita = NULL;

    return nova;
}

/* =========================
   CRIAR NÓ DA BST
========================= */

PistaNode* criarPista(char pista[]) {

    PistaNode* novo = (PistaNode*) malloc(sizeof(PistaNode));

    strcpy(novo->pista, pista);

    novo->esquerda = NULL;
    novo->direita = NULL;

    return novo;
}

/* =========================
   INSERIR PISTA NA BST
========================= */

PistaNode* inserirPista(PistaNode* raiz, char pista[]) {

    if (raiz == NULL) {
        return criarPista(pista);
    }

    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    }

    else if (strcmp(pista, raiz->pista) > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }

    return raiz;
}

/* =========================
   EXIBIR PISTAS EM ORDEM
========================= */

void exibirPistas(PistaNode* raiz) {

    if (raiz != NULL) {

        exibirPistas(raiz->esquerda);

        printf("- %s\n", raiz->pista);

        exibirPistas(raiz->direita);
    }
}

/* =========================
   EXPLORAR SALAS
========================= */

void explorarSalasComPistas(Sala* atual, PistaNode** arvorePistas) {

    char opcao;

    while (atual != NULL) {

        printf("\n========================\n");
        printf("Voce esta em: %s\n", atual->nome);

        /* verifica se existe pista */
        if (strlen(atual->pista) > 0) {

            printf("Pista encontrada: %s\n", atual->pista);

            *arvorePistas = inserirPista(*arvorePistas, atual->pista);
        }

        printf("\nEscolha:\n");
        printf("(e) esquerda\n");
        printf("(d) direita\n");
        printf("(s) sair\n");

        printf("Opcao: ");
        scanf(" %c", &opcao);

        if (opcao == 's') {
            break;
        }

        else if (opcao == 'e') {

            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            }

            else {
                printf("\nNao existe sala a esquerda.\n");
            }
        }

        else if (opcao == 'd') {

            if (atual->direita != NULL) {
                atual = atual->direita;
            }

            else {
                printf("\nNao existe sala a direita.\n");
            }
        }

        else {
            printf("\nOpcao invalida.\n");
        }
    }
}

/* =========================
   MAIN
========================= */

int main() {

    /* arvore da mansao */

    Sala* hall = criarSala(
        "Hall de Entrada",
        "Pegadas de lama"
    );

    Sala* biblioteca = criarSala(
        "Biblioteca",
        "Livro rasgado"
    );

    Sala* cozinha = criarSala(
        "Cozinha",
        "Faca suja"
    );

    Sala* quarto = criarSala(
        "Quarto",
        "Lencol manchado"
    );

    Sala* jardim = criarSala(
        "Jardim",
        "Chave perdida"
    );

    /* ligacoes da arvore */

    hall->esquerda = biblioteca;
    hall->direita = cozinha;

    biblioteca->esquerda = quarto;
    cozinha->direita = jardim;

    /* BST das pistas */

    PistaNode* arvorePistas = NULL;

    /* exploracao */

    explorarSalasComPistas(hall, &arvorePistas);

    /* exibir pistas */

    printf("\n========================\n");
    printf("PISTAS COLETADAS:\n\n");

    exibirPistas(arvorePistas);

    return 0;
}