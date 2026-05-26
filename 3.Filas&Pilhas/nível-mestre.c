#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

// ======================= STRUCT PEÇA =======================

typedef struct {
    char nome;
    int id;
} Peca;

// ======================= STRUCT FILA =======================

typedef struct {
    Peca itens[MAX_FILA];
    int inicio;
    int fim;
    int total;
} Fila;

// ======================= STRUCT PILHA =======================

typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

// ======================= GERAR PEÇA =======================

Peca gerarPeca(int id) {

    char tipos[] = {'I', 'O', 'T', 'L'};

    Peca nova;

    nova.nome = tipos[rand() % 4];
    nova.id = id;

    return nova;
}

// ======================= FILA =======================

void inicializarFila(Fila *f) {

    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(Fila *f) {

    return f->total == MAX_FILA;
}

int filaVazia(Fila *f) {

    return f->total == 0;
}

void enqueue(Fila *f, Peca p) {

    if (filaCheia(f)) {
        printf("Fila cheia!\n");
        return;
    }

    f->itens[f->fim] = p;

    f->fim = (f->fim + 1) % MAX_FILA;

    f->total++;
}

Peca dequeue(Fila *f) {

    Peca vazio = {'X', -1};

    if (filaVazia(f)) {
        return vazio;
    }

    Peca removida = f->itens[f->inicio];

    f->inicio = (f->inicio + 1) % MAX_FILA;

    f->total--;

    return removida;
}

void mostrarFila(Fila *f) {

    printf("\nFila de peças:\n");

    int idx = f->inicio;

    for (int i = 0; i < f->total; i++) {

        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);

        idx = (idx + 1) % MAX_FILA;
    }

    printf("\n");
}

// ======================= PILHA =======================

void inicializarPilha(Pilha *p) {

    p->topo = -1;
}

int pilhaCheia(Pilha *p) {

    return p->topo == MAX_PILHA - 1;
}

int pilhaVazia(Pilha *p) {

    return p->topo == -1;
}

void push(Pilha *p, Peca nova) {

    if (pilhaCheia(p)) {
        printf("Pilha cheia!\n");
        return;
    }

    p->topo++;

    p->itens[p->topo] = nova;
}

Peca pop(Pilha *p) {

    Peca vazio = {'X', -1};

    if (pilhaVazia(p)) {
        return vazio;
    }

    Peca removida = p->itens[p->topo];

    p->topo--;

    return removida;
}

void mostrarPilha(Pilha *p) {

    printf("\nPilha de reserva (Topo -> Base):\n");

    for (int i = p->topo; i >= 0; i--) {

        printf("[%c %d] ", p->itens[i].nome, p->itens[i].id);
    }

    printf("\n");
}

// ======================= TROCAR PEÇA ATUAL =======================

void trocarAtual(Fila *f, Pilha *p) {

    if (filaVazia(f) || pilhaVazia(p)) {

        printf("Fila ou pilha vazia!\n");
        return;
    }

    Peca temp;

    temp = f->itens[f->inicio];

    f->itens[f->inicio] = p->itens[p->topo];

    p->itens[p->topo] = temp;

    printf("Troca realizada!\n");
}

// ======================= TROCA MÚLTIPLA =======================

void trocaMultipla(Fila *f, Pilha *p) {

    if (f->total < 3 || p->topo < 2) {

        printf("Não há peças suficientes!\n");
        return;
    }

    for (int i = 0; i < 3; i++) {

        int idxFila = (f->inicio + i) % MAX_FILA;

        Peca temp;

        temp = f->itens[idxFila];

        f->itens[idxFila] = p->itens[p->topo - i];

        p->itens[p->topo - i] = temp;
    }

    printf("Troca múltipla realizada!\n");
}

// ======================= MAIN =======================

int main() {

    srand(time(NULL));

    Fila fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int contadorID = 0;

    // Preencher fila inicial

    for (int i = 0; i < MAX_FILA; i++) {

        enqueue(&fila, gerarPeca(contadorID));

        contadorID++;
    }

    int opcao;

    do {

        printf("\n============================\n");

        mostrarFila(&fila);

        mostrarPilha(&pilha);

        printf("\n1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("4 - Trocar peça atual\n");
        printf("5 - Troca múltipla\n");
        printf("0 - Sair\n");

        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: {

                Peca jogada = dequeue(&fila);

                printf("\nPeça jogada: [%c %d]\n", jogada.nome, jogada.id);

                enqueue(&fila, gerarPeca(contadorID));

                contadorID++;

                break;
            }

            case 2: {

                if (pilhaCheia(&pilha)) {

                    printf("\nPilha cheia!\n");
                    break;
                }

                Peca reservada = dequeue(&fila);

                push(&pilha, reservada);

                printf("\nPeça reservada: [%c %d]\n",
                       reservada.nome,
                       reservada.id);

                enqueue(&fila, gerarPeca(contadorID));

                contadorID++;

                break;
            }

            case 3: {

                if (pilhaVazia(&pilha)) {

                    printf("\nPilha vazia!\n");
                    break;
                }

                Peca usada = pop(&pilha);

                printf("\nPeça usada: [%c %d]\n",
                       usada.nome,
                       usada.id);

                break;
            }

            case 4: {

                trocarAtual(&fila, &pilha);

                break;
            }

            case 5: {

                trocaMultipla(&fila, &pilha);

                break;
            }

            case 0:

                printf("\nEncerrando...\n");

                break;

            default:

                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}