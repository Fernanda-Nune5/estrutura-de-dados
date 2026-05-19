#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct que representa um território do jogo
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio *mapa, int quantidade) {

    for(int i = 0; i < quantidade; i++) {

        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Nome do território: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir o mapa
void exibirMapa(Territorio *mapa, int quantidade) {

    printf("\n===== MAPA DO JOGO =====\n");

    for(int i = 0; i < quantidade; i++) {

        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// Função que realiza o ataque entre territórios
void atacar(Territorio *atacante, Territorio *defensor) {

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n===== BATALHA =====\n");

    printf("%s tirou: %d\n", atacante->nome, dadoAtacante);
    printf("%s tirou: %d\n", defensor->nome, dadoDefensor);

    // Se o atacante vencer
    if(dadoAtacante > dadoDefensor) {

        printf("\n%s conquistou %s!\n",
               atacante->nome,
               defensor->nome);

        // Copia a cor do atacante para o defensor
        strcpy(defensor->cor, atacante->cor);

        // Atualiza tropas do defensor
        defensor->tropas = atacante->tropas / 2;
    }

    // Se o defensor vencer
    else {

        printf("\n%s defendeu o território!\n",
               defensor->nome);

        atacante->tropas--;

        // Evita tropas negativas
        if(atacante->tropas < 0) {
            atacante->tropas = 0;
        }
    }
}

// Função para atribuir missão ao jogador
void atribuirMissao(char *destino,
                    char *missoes[],
                    int totalMissoes) {

    int sorteio = rand() % totalMissoes;

    // Copia a missão sorteada
    strcpy(destino, missoes[sorteio]);
}

// Função para exibir missão
void exibirMissao(char *missao) {

    printf("\n===== SUA MISSÃO =====\n");
    printf("%s\n", missao);
}

// Função para verificar missão
int verificarMissao(char *missao,
                    Territorio *mapa,
                    int tamanho) {

    int contador = 0;

    // Missão simples:
    // conquistar pelo menos 3 territórios azuis

    if(strcmp(missao,
              "Conquistar 3 territorios azuis") == 0) {

        for(int i = 0; i < tamanho; i++) {

            if(strcmp(mapa[i].cor, "Azul") == 0) {
                contador++;
            }
        }

        if(contador >= 3) {
            return 1;
        }
    }

    // Outra missão simples:
    // possuir 5 territórios

    if(strcmp(missao,
              "Conquistar 5 territorios") == 0) {

        if(tamanho >= 5) {
            return 1;
        }
    }

    return 0;
}

// Função para liberar memória
void liberarMemoria(Territorio *mapa,
                    char *missaoJogador) {

    free(mapa);
    free(missaoJogador);
}

int main() {

    srand(time(NULL));

    int quantidade;

    printf("Quantidade de territorios: ");
    scanf("%d", &quantidade);

    // Alocação dinâmica do mapa
    Territorio *mapa =
    (Territorio*)calloc(quantidade,
                        sizeof(Territorio));

    // Verifica se a memória foi alocada
    if(mapa == NULL) {

        printf("Erro de memória!\n");
        return 1;
    }

    // Vetor de missões
    char *missoes[] = {

        "Conquistar 3 territorios azuis",
        "Conquistar 5 territorios",
        "Eliminar exercito vermelho",
        "Dominar metade do mapa",
        "Conquistar 2 territorios seguidos"
    };

    int totalMissoes = 5;

    // Alocação dinâmica da missão do jogador
    char *missaoJogador =
    (char*)malloc(100 * sizeof(char));

    // Atribui missão aleatória
    atribuirMissao(missaoJogador,
                   missoes,
                   totalMissoes);

    // Mostra missão apenas uma vez
    exibirMissao(missaoJogador);

    // Cadastro dos territórios
    cadastrarTerritorios(mapa, quantidade);

    // Mostra mapa inicial
    exibirMapa(mapa, quantidade);

    int atacante;
    int defensor;

    printf("\n===== ESCOLHA O ATAQUE =====\n");

    // Lista territórios
    for(int i = 0; i < quantidade; i++) {

        printf("%d - %s (%s)\n",
               i,
               mapa[i].nome,
               mapa[i].cor);
    }

    printf("\nEscolha o território atacante: ");
    scanf("%d", &atacante);

    printf("Escolha o território defensor: ");
    scanf("%d", &defensor);

    // Verifica se estão atacando mesma cor
    if(strcmp(mapa[atacante].cor,
              mapa[defensor].cor) == 0) {

        printf("\nNao pode atacar territórios da mesma cor!\n");
    }

    else {

        atacar(&mapa[atacante],
                &mapa[defensor]);

        // Exibe mapa atualizado
        exibirMapa(mapa, quantidade);

        // Verifica missão
        if(verificarMissao(missaoJogador,
                           mapa,
                           quantidade)) {

            printf("\n===== MISSÃO CUMPRIDA =====\n");
            printf("Jogador venceu o jogo!\n");
        }
    }

    // Libera memória
    liberarMemoria(mapa,
                   missaoJogador);

    return 0;
}