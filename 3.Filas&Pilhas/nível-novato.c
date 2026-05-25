#include <stdio.h>
#include <stdlib.h>

#define MAX 5

//Struct da peça 
typedef struct {
    char nome;
    int id;
}Peca;

//Struct da fila
typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
}Fila;

//Incicializar a fila
void InicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

//Verificra se a fila esta cheia
int filaCheia(Fila *f) {
    return f->total == MAX;
}

//Verificar se a fila esta vazia
int filaVazia(Fila *f) {
    return f->total == 0;
}

//Gera peça automática
Peca gerarPeca(int id) {
    Peca p;

    char tipos[] = {'I', '0', 'T', 'L'};

    p.nome = tipos[rand() % 4];
    p.id = id;

    return p;
}

//Inserir peça na fila (enqueue)
void Inserir(Fila *f, Peca p){

    if(filaCheia(f)){
        printf("\nFila cheia! Não é possível inserir.\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

//Remover peça da fila (dequeue)
Peca remover(Fila *f){
    Peca vazio = {'X', -1};

    if(filaVazia(f)){
        printf("\nFila vazia!\n");
        return vazio;
    }
    Peca removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    return removida;
}

//Mostrar fila
void mostrarFila(Fila *f){
    printf("\n=== FILA DE PEÇAS ===\n");

    if(filaVazia(f)){
        printf("Fila vazia.\n");
        return;
    }

    int i;
    int indice = f->inicio;

    for (i = 0; i < f->total; i++){
        
        printf("[%c %d]",
                f->itens[indice].nome,
                f->itens[indice].id);
        
        indice = (indice + 1) % MAX;
    }

    printf("\n");
}

int main(){

    Fila fila;
    InicializarFila(&fila);
    int contadorID = 0;

    //Preencher fila inicial
    for (int i = 0; i < MAX; i++){
        Inserir(&fila, gerarPeca(contadorID));

        contadorID++;
    }
    int opcao;

    do{
        mostrarFila(&fila);
        
        printf("\n1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("0 - Sair\n");

        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao){

            case 1:{
                Peca removida = remover(&fila);

                if(removida.id != -1){
                    printf("\nPeça removida: [%c %d]\n",
                            removida.nome,
                            removida.id);

                }
                break;
            }
            case 2: {

                Peca nova = gerarPeca(contadorID);

                Inserir(&fila, nova);

                contadorID++;

                break;
            }

            case 0:

                printf("\nSaindo do jogo...\n");

                break;

            default:

                printf("\nOpcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}