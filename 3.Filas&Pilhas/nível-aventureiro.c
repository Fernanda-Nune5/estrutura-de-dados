#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

//Struct da peça
typedef struct {
    char nome;
    int id;
}Peca;

//Struct da fila
typedef struct {
    Peca itens[MAX_FILA];
    int inicio;
    int fim;
    int total;
}Fila;

//Struct da pilha
typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
}Pilha;

//Inicializa a fila
void inicializarFila(Fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

//Inicializa a pilha
void inicializarPilha(Pilha *p){
    p->topo = -1;
}

//Verificar fila vazia
int filaVazia(Fila *f){
    return f->total == 0;
}

//Verficar fila cheia
int filaCheia(Fila *f){
    return f->total == MAX_FILA;
}

//Verificar pilha vazia
int pilhaVazia(Pilha *p){
    return p->topo == -1;
}

//Verificar pilha cheia
int pilhaCheia(Pilha *p){
    return p->topo == MAX_PILHA - 1;
}

//Gera peça aleatória
Peca gerarPeca(int id){
    Peca p;

    char tipos[rand() % 4];
    p.id = id;

    return p;
}

//Inserir na fila
void enqueue(Fila *f, Peca p){
    if(filaCheia(f)){
        printf("Fila cheia!\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

//Remover da fila
Peca dequeue(Fila *f){
    Peca vazio = {'x', -1};

    if(filaVazia(f)){
        printf("Fila vazia!\n");
        return vazio;
    }

    Peca removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;
    return removida;
}

//Push na pilha
void push(Pilha *p, Peca nova){

    if(pilhaCheia(p)){
        printf("Pilha cheia!\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = nova;
}

//Pop na pilha
Peca pop(Pilha *p){
    Peca vazio = {'X', -1};

    if(pilhaVazia(p)){
        printf("Pilha vazia!\n");
        return vazio;
    }
    
    Peca removida = p->itens[p->topo];
    p->topo--;
    return removida;
}
// Mostrar fila
void mostrarFila(Fila *f) {

    printf("Fila: ");

    for (int i = 0, idx = f->inicio; i < f->total; i++) {

        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);

        idx = (idx + 1) % MAX_FILA;
    }

    printf("\n");
}

// Mostrar pilha
void mostrarPilha(Pilha *p) {

    printf("Pilha (Topo -> Base): ");

    for (int i = p->topo; i >= 0; i--) {

        printf("[%c %d] ", p->itens[i].nome, p->itens[i].id);
    }

    printf("\n");
}

int main() {

    srand(time(NULL));

    Fila fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int contadorId = 0;

    // Preenche fila inicial
    for (int i = 0; i < MAX_FILA; i++) {

        enqueue(&fila, gerarPeca(contadorId));

        contadorId++;
    }

    int opcao;

    do {

        printf("\n===== TETRIS STACK =====\n");

        mostrarFila(&fila);

        mostrarPilha(&pilha);

        printf("\n1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");

        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1: {

                Peca jogada = dequeue(&fila);

                if (jogada.id != -1) {

                    printf("\nPeça jogada: [%c %d]\n",
                           jogada.nome,
                           jogada.id);

                    enqueue(&fila, gerarPeca(contadorId));

                    contadorId++;
                }

                break;
            }

            case 2: {

                if (pilhaCheia(&pilha)) {

                    printf("\nPilha de reserva cheia!\n");

                } else {

                    Peca reservada = dequeue(&fila);

                    if (reservada.id != -1) {

                        push(&pilha, reservada);

                        printf("\nPeça reservada: [%c %d]\n",
                               reservada.nome,
                               reservada.id);

                        enqueue(&fila, gerarPeca(contadorId));

                        contadorId++;
                    }
                }

                break;
            }

            case 3: {

                Peca usada = pop(&pilha);

                if (usada.id != -1) {

                    printf("\nPeça usada da reserva: [%c %d]\n",
                           usada.nome,
                           usada.id);
                }

                break;
            }

            case 0:
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while(opcao != 0);

    return 0;
}