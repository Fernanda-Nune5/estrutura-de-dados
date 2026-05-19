#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct que representa um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio *mapa, int quantidade) {

    int i;

    for(i = 0; i < quantidade; i++) {

        printf("\n=== Cadastro do Territorio %d ===\n", i + 1);

        printf("Nome do territorio: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Cor do exercito: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir os territórios
void exibirTerritorios(Territorio *mapa, int quantidade) {

    int i;

    printf("\n======= MAPA DE TERRITORIOS =======\n");

    for(i = 0; i < quantidade; i++) {

        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// Função que simula o ataque
void atacar(Territorio *atacante, Territorio *defensor) {

    int dadoAtacante;
    int dadoDefensor;

    // Gera números aleatórios de 1 a 6
    dadoAtacante = (rand() % 6) + 1;
    dadoDefensor = (rand() % 6) + 1;

    printf("\n=== RESULTADO DO ATAQUE ===\n");

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    // Verifica quem venceu
    if(dadoAtacante > dadoDefensor) {
        

        printf("\nO atacante venceu a batalha!\n");

        // Defensor muda de cor
        strcpy(defensor->cor, atacante->cor);

        // Metade das tropas do atacante vai para o defensor
        defensor->tropas = atacante->tropas / 2;

    } else {

        printf("\nO defensor venceu a batalha!\n");

        // Atacante perde uma tropa
        atacante->tropas--;

        // Evita tropas negativas
        if(atacante->tropas < 0) {
            atacante->tropas = 0;
        }
    }
}

// Função para liberar memória dinâmica
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

int main() {

    int quantidade;
    int atacante;
    int defensor;

    // Inicializa números aleatórios
    srand(time(NULL));

    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &quantidade);

    // Alocação dinâmica de memória
    Territorio *mapa;

    mapa = (Territorio*) calloc(quantidade, sizeof(Territorio));

    // Verifica se a memória foi alocada
    if(mapa == NULL) {

        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Cadastro dos territórios
    cadastrarTerritorios(mapa, quantidade);

    // Exibe os territórios cadastrados
    exibirTerritorios(mapa, quantidade);

    printf("\n======= ATAQUE =======\n");

    // Mostra opções disponíveis
    for(int i = 0; i < quantidade; i++) {

        printf("%d - %s (%s)\n",
               i,
               mapa[i].nome,
               mapa[i].cor);
    }

    // Escolha do atacante
    printf("\nEscolha o territorio atacante: ");
    scanf("%d", &atacante);

    // Escolha do defensor
    printf("Escolha o territorio defensor: ");
    scanf("%d", &defensor);

    // Validação
    if(strcmp(mapa[atacante].cor,
              mapa[defensor].cor) == 0) {

        printf("\nNao e permitido atacar territorios da mesma cor.\n");

    } else {

        // Chama função de ataque usando ponteiros
        atacar(&mapa[atacante], &mapa[defensor]);

        // Exibe mapa atualizado
        exibirTerritorios(mapa, quantidade);
    }

    // Libera memória dinâmica
    liberarMemoria(mapa);

    return 0;
}