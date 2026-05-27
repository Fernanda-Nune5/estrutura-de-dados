#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de cada sala da mansão
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Função para criar uma sala dinamicamente
Sala* criarSala(char nome[]) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));

    strcpy(nova->nome, nome);

    nova->esquerda = NULL;
    nova->direita = NULL;

    return nova;
}

// Função para explorar a mansão
void explorarSalas(Sala *atual) {
    char escolha;

    while (atual != NULL) {

        printf("\nVoce esta em: %s\n", atual->nome);

        // Verifica se chegou em uma folha
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Nao existem mais caminhos.\n");
            printf("Fim da exploracao!\n");
            break;
        }

        // Mostra caminhos disponíveis
        if (atual->esquerda != NULL) {
            printf("Esquerda (e): %s\n", atual->esquerda->nome);
        }

        if (atual->direita != NULL) {
            printf("Direita (d): %s\n", atual->direita->nome);
        }

        printf("Digite e para esquerda, d para direita ou s para sair: ");
        scanf(" %c", &escolha);

        if (escolha == 's') {
            printf("Exploracao encerrada.\n");
            break;
        }

        else if (escolha == 'e') {

            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Nao existe caminho para esquerda!\n");
            }
        }

        else if (escolha == 'd') {

            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Nao existe caminho para direita!\n");
            }
        }

        else {
            printf("Opcao invalida!\n");
        }
    }
}

// Função para liberar memória da árvore
void liberarSalas(Sala *raiz) {

    if (raiz != NULL) {

        liberarSalas(raiz->esquerda);
        liberarSalas(raiz->direita);

        free(raiz);
    }
}

int main() {

    // Criação do mapa da mansão
    Sala *raiz = criarSala("Hall de Entrada");

    raiz->esquerda = criarSala("Sala de Estar");
    raiz->direita = criarSala("Biblioteca");

    raiz->esquerda->esquerda = criarSala("Cozinha");
    raiz->esquerda->direita = criarSala("Jardim");

    raiz->direita->esquerda = criarSala("Escritorio");
    raiz->direita->direita = criarSala("Quarto Secreto");

    // Inicia exploração
    explorarSalas(raiz);

    // Libera memória
    liberarSalas(raiz);

    return 0;
}