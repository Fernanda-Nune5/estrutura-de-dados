#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABELA 10

// ==========================
// ESTRUTURA DAS SALAS
// ==========================

typedef struct Sala {
    char nome[50];
    char pista[100];

    struct Sala* esquerda;
    struct Sala* direita;

} Sala;

// ==========================
// BST DAS PISTAS
// ==========================

typedef struct PistaNode {
    char pista[100];

    struct PistaNode* esquerda;
    struct PistaNode* direita;

} PistaNode;

// ==========================
// HASH DOS SUSPEITOS
// ==========================

typedef struct NodoHash {

    char pista[100];
    char suspeito[50];

    struct NodoHash* proximo;

} NodoHash;

NodoHash* tabelaHash[TAMANHO_TABELA];

// ==========================
// FUNÇÃO HASH
// ==========================

int funcaoHash(char* chave) {

    int soma = 0;

    for(int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }

    return soma % TAMANHO_TABELA;
}

// ==========================
// INSERIR NA HASH
// ==========================

void inserirNaHash(char* pista, char* suspeito) {

    int indice = funcaoHash(pista);

    NodoHash* novo = (NodoHash*) malloc(sizeof(NodoHash));

    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);

    novo->proximo = tabelaHash[indice];
    tabelaHash[indice] = novo;
}

// ==========================
// BUSCAR SUSPEITO
// ==========================

char* encontrarSuspeito(char* pista) {

    int indice = funcaoHash(pista);

    NodoHash* atual = tabelaHash[indice];

    while(atual != NULL) {

        if(strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }

        atual = atual->proximo;
    }

    return NULL;
}

// ==========================
// CRIAR SALA
// ==========================

Sala* criarSala(char* nome, char* pista) {

    Sala* nova = (Sala*) malloc(sizeof(Sala));

    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);

    nova->esquerda = NULL;
    nova->direita = NULL;

    return nova;
}

// ==========================
// INSERIR PISTA NA BST
// ==========================

PistaNode* inserirPista(PistaNode* raiz, char* pista) {

    if(raiz == NULL) {

        PistaNode* novo = (PistaNode*) malloc(sizeof(PistaNode));

        strcpy(novo->pista, pista);

        novo->esquerda = NULL;
        novo->direita = NULL;

        return novo;
    }

    if(strcmp(pista, raiz->pista) < 0) {

        raiz->esquerda = inserirPista(raiz->esquerda, pista);

    } else if(strcmp(pista, raiz->pista) > 0) {

        raiz->direita = inserirPista(raiz->direita, pista);
    }

    return raiz;
}

// ==========================
// EXIBIR PISTAS EM ORDEM
// ==========================

void exibirPistas(PistaNode* raiz) {

    if(raiz != NULL) {

        exibirPistas(raiz->esquerda);

        printf("- %s\n", raiz->pista);

        exibirPistas(raiz->direita);
    }
}

// ==========================
// CONTAR PISTAS DO SUSPEITO
// ==========================

int contarPistasSuspeito(PistaNode* raiz, char* suspeito) {

    if(raiz == NULL) {
        return 0;
    }

    int contador = 0;

    char* suspeitoEncontrado = encontrarSuspeito(raiz->pista);

    if(
        suspeitoEncontrado != NULL &&
        strcmp(suspeitoEncontrado, suspeito) == 0
    ) {
        contador++;
    }

    contador += contarPistasSuspeito(raiz->esquerda, suspeito);

    contador += contarPistasSuspeito(raiz->direita, suspeito);

    return contador;
}

// ==========================
// EXPLORAR SALAS
// ==========================

void explorarSalas(Sala* atual, PistaNode** arvorePistas) {

    char opcao;

    while(atual != NULL) {

        printf("\n========================\n");
        printf("Voce esta em: %s\n", atual->nome);

        if(strlen(atual->pista) > 0) {

            printf("Pista encontrada: %s\n", atual->pista);

            *arvorePistas = inserirPista(
                *arvorePistas,
                atual->pista
            );
        }

        printf("\nEscolha:\n");
        printf("[e] Ir para esquerda\n");
        printf("[d] Ir para direita\n");
        printf("[s] Sair\n");

        scanf(" %c", &opcao);

        if(opcao == 'e' || opcao == 'E') {

            if(atual->esquerda != NULL) {

                atual = atual->esquerda;

            } else {

                printf("Nao existe sala a esquerda.\n");
            }

        } else if(opcao == 'd' || opcao == 'D') {

            if(atual->direita != NULL) {

                atual = atual->direita;

            } else {

                printf("Nao existe sala a direita.\n");
            }

        } else if(opcao == 's' || opcao == 'S') {

            break;

        } else {

            printf("Opcao invalida.\n");
        }
    }
}

// ==========================
// VERIFICAR SUSPEITO FINAL
// ==========================

void verificarSuspeitoFinal(PistaNode* arvorePistas) {

    char suspeito[50];

    printf("\n========================\n");
    printf("PISTAS COLETADAS:\n");

    exibirPistas(arvorePistas);

    printf("\nDigite o nome do suspeito: ");
    scanf(" %[^\n]", suspeito);

    int quantidade = contarPistasSuspeito(
        arvorePistas,
        suspeito
    );

    printf("\n");

    if(quantidade >= 2) {

        printf(
            "Suspeito %s possui %d pistas.\n",
            suspeito,
            quantidade
        );

        printf("Acusacao valida!\n");

    } else {

        printf(
            "Suspeito %s possui apenas %d pista(s).\n",
            suspeito,
            quantidade
        );

        printf("Evidencias insuficientes.\n");
    }
}

// ==========================
// MAIN
// ==========================

int main() {

    // Inicializa tabela hash

    for(int i = 0; i < TAMANHO_TABELA; i++) {
        tabelaHash[i] = NULL;
    }

    // ==========================
    // INSERINDO PISTAS E SUSPEITOS
    // ==========================

    inserirNaHash("Pegadas de lama", "Jardineiro");

    inserirNaHash("Faca ensanguentada", "Cozinheiro");

    inserirNaHash("Livro rasgado", "Mordomo");

    inserirNaHash("Carta escondida", "Mordomo");

    inserirNaHash("Janela quebrada", "Jardineiro");

    // ==========================
    // CRIANDO SALAS
    // ==========================

    Sala* hall = criarSala(
        "Hall de Entrada",
        ""
    );

    Sala* biblioteca = criarSala(
        "Biblioteca",
        "Livro rasgado"
    );

    Sala* cozinha = criarSala(
        "Cozinha",
        "Faca ensanguentada"
    );

    Sala* escritorio = criarSala(
        "Escritorio",
        "Carta escondida"
    );

    Sala* jardim = criarSala(
        "Jardim",
        "Pegadas de lama"
    );

    // ==========================
    // MONTANDO ARVORE
    // ==========================

    hall->esquerda = biblioteca;
    hall->direita = cozinha;

    biblioteca->esquerda = escritorio;

    cozinha->direita = jardim;

    // ==========================
    // BST DAS PISTAS
    // ==========================

    PistaNode* arvorePistas = NULL;

    // ==========================
    // INICIAR EXPLORACAO
    // ==========================

    explorarSalas(
        hall,
        &arvorePistas
    );

    // ==========================
    // JULGAMENTO FINAL
    // ==========================

    verificarSuspeitoFinal(arvorePistas);

    return 0;
}