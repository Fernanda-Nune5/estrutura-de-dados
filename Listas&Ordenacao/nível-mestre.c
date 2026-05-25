#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

// ================= STRUCT =================

typedef struct
{
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ================= VARIAVEIS GLOBAIS =================

int comparacoes = 0;

// ================= FUNCAO PARA REMOVER \n =================

void removerEnter(char texto[])
{
    texto[strcspn(texto, "\n")] = '\0';
}

// ================= MOSTRAR COMPONENTES =================

void mostrarComponente(Componente vetor[], int tamanho){

    printf("\n======= COMPONENTES ======\n");

    for (int i = 0; i < tamanho; i++){

        printf("\nComponente %d\n", i + 1);
        printf("Nome: %s\n", vetor[i].nome);
        printf("Tipo: %s\n", vetor[i].tipo);
        printf("Prioridade: %d\n", vetor[i].prioridade);
    }
}

// ================= BUBBLE SORT POR NOME =================

void bubbleSortNome(Componente vetor[], int tamanho)
{

    comparacoes = 0;

    for (int i = 0; i < tamanho - 1; i++)
    {

        for (int j = 0; j < tamanho - 1 - i; j++)
        {

            comparacoes;

            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0)
            {

                Componente temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
    printf("\nBubble Sort realizado com sucesso!\n");
    printf("Comparacoes: %d\n", comparacoes);
}

// ================= INSERTION SORT POR TIPO =================

void insertionSortTipo(Componente vetor[], int tamanho){
    
    comparacoes = 0;

    for (int i = 1; i < tamanho; i++)
    {
        Componente chave = vetor[i];

        int j = i - 1;

        while (j >= 0)
        {

            comparacoes++;

            if (strcmp(vetor[j].tipo, chave.tipo) > 0){

                vetor[j + 1] = vetor[j];
                j--;

            }else{
                break; 
            }
        }
        
        vetor[j + 1] = chave;
    }
    printf("\nInsertion Sort realizado com sucesso!\n");
    printf("Comparacoes: %d\n", comparacoes);
}

// ================= SELECTION SORT POR PRIORIDADE =================

void selectionSortPrioridade(Componente vetor[], int tamanho)
{

    comparacoes = 0;

    for (int i = 0; i < tamanho - 1; i++)
    {

        int indiceMenor = i;

        for (int j = i + 1; j < tamanho; j++)
        {

            comparacoes++;

            if (vetor[j].prioridade < vetor[indiceMenor].prioridade)
            {

                indiceMenor = j;
            }
        }

        Componente temp = vetor[i];
        vetor[i] = vetor[indiceMenor];
        vetor[indiceMenor] = temp;
    }
    printf("\nSelection Sort realizado com sucesso!\n");
    printf("Comparacoes: %d\n", comparacoes);
}

// ================= BUSCA BINARIA =================

int buscaBinariaPorNome(Componente vetor[], int tamanho, char busca[])
{

    int inicio = 0;
    int fim = tamanho - 1;

    comparacoes = 0;

    while (inicio <= fim)
    {

        int meio = (inicio + fim) / 2;

        comparacoes++;

        int resultado = strcmp(vetor[meio].nome, busca);

        if (resultado == 0)
        {

            return meio;
        }
        else if (resultado > 0)
        {

            fim = meio - 1;
        }
        else
        {

            inicio = meio + 1;
        }
    }
    return -1;
}

// ================= MEDIR TEMPO =================

void medirTempo(void (*algoritimo)(Componente[], int),
                Componente vetor[],
                int tamanho)
{

    clock_t inicio, fim;

    inicio = clock;

    algoritimo(vetor, tamanho);

    fim = clock;

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Tempo de execução: %.6f segundos\n", tempo);
}

// ================= MAIN =================

int main()
{

    Componente componente[MAX];

    int quantidade;

    printf("Quantos componentes deseja cadastrar? ");
    scanf("%d", &quantidade);

    getchar(); // Limpar buffer

    // ================= CADASTRO =================

    for (int i = 0; i < quantidade; i++)
    {

        printf("Nome: ");
        fgets(componente[i].nome, 30, stdin);
        removerEnter(componente[i].nome);

        printf("Prioridade (1 a 10): ");
        scanf("%d", &componente[i].prioridade);

        getchar(); // Limpar buffer
    }

    int opcao;

    do
    {

        printf("\n======= MENU =======\n");
        printf("1 - Mostrar Componentes\n");
        printf("2 - Bubble Sort por Nome\n");
        printf("3 - Insertion Sort por Tipo\n");
        printf("4 - Selection Sort por Prioridade\n");
        printf("5 - Busca Binaria por Nome\n");
        printf("0 - Sair\n");

        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao){

            case 1: 

            mostrarComponentes(componente, quantidade);
            break;

            case 2:
            
              medirTempo(bubbleSortNome, componente, quantidade);

                mostrarComponentes(componente, quantidade);

                break;

            case 3:

                medirTempo(insertionSortTipo, componente, quantidade);

                mostrarComponentes(componente, quantidade);

                break;

            case 4:

                medirTempo(selectionSortPrioridade, componente, quantidade);

                mostrarComponentes(componente, quantidade);

                break;

            case 5:{

                char busca[30];

                printf("\nDigite o nome do componente: ");
                fgets(busca, 30, stdin);

                removerEnter(busca);

                int posicao =
                buscaBinariaPorNome(componente, quantidade,
                                    busca);

                if(posicao != -1){

                    printf("\nComponente encontrado!\n");

                    printf("Nome: %s\n", componente[posicao].nome);

                    printf("Tipo: %s\n", componente[posicao].tipo);

                    printf("Prioridade: %d\n", componente[posicao].prioridade);

                }
                else{

                    printf("\nComponente nao encontrado.\n");
                }

                printf("Comparacoes: %d\n",
                       comparacoes);

                break;
            }

            case 0:

                printf("\nEncerrando sistema...\n");
                break;

            default:

                printf("\nOpcao invalida.\n");
        }

    }while(opcao != 0);

    return 0;
}
