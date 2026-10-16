#include <stdio.h>

#define MAX_PROCESSOS 100

// Estrutura que armazena os dados de um processo
typedef struct {
    char nome[20];
    int tempoChegada;
    int tempoExecucao;
    int tempoRestante;
} Processo;

// Funcao responsavel pelo cadastro dos processos
void cadastrarProcessos(Processo processos[], int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\n--- Processo %d ---\n", i + 1);

        printf("Nome do processo: ");
        scanf("%19s", processos[i].nome);

        do {
            printf("Tempo de chegada: ");
            scanf("%d", &processos[i].tempoChegada);

            if (processos[i].tempoChegada < 0) {
                printf("O tempo de chegada nao pode ser negativo!\n");
            }
        } while (processos[i].tempoChegada < 0);

        do {
            printf("Tempo de execucao (Burst Time): ");
            scanf("%d", &processos[i].tempoExecucao);

            if (processos[i].tempoExecucao <= 0) {
                printf("O tempo de execucao deve ser maior que zero!\n");
            }
        } while (processos[i].tempoExecucao <= 0);

        // Inicializa o tempo restante
        processos[i].tempoRestante = processos[i].tempoExecucao;
    }
}

// Funcao que exibe os processos cadastrados
void listarProcessos(Processo processos[], int quantidade) {
    printf("\n========== PROCESSOS CADASTRADOS ==========\n");

    printf("%-12s %-12s %-12s %-12s\n",
           "Processo", "Chegada", "Execucao", "Restante");

    for (int i = 0; i < quantidade; i++) {
        printf("%-12s %-12d %-12d %-12d\n",
               processos[i].nome,
               processos[i].tempoChegada,
               processos[i].tempoExecucao,
               processos[i].tempoRestante);
    }
}

// Funcao que exibe os processos que estao prontos
void mostrarProntos(Processo processos[], int quantidade, int tempoAtual, int executando) {
    int encontrou = 0;

    printf("Prontos: ");

    for (int i = 0; i < quantidade; i++) {
        if (processos[i].tempoChegada <= tempoAtual &&
            processos[i].tempoRestante > 0 &&
            i != executando) {

            printf("%s(%d) ",
                   processos[i].nome,
                   processos[i].tempoRestante);

            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        printf("Nenhum");
    }

    printf("\n");
}

// Algoritmo Shortest Remaining Time (SRT)
void executarSRT(Processo processos[], int quantidade) {
    int tempoAtual = 0;
    int concluidos = 0;

    printf("\n========== EXECUCAO SRT ==========\n");

    while (concluidos < quantidade) {
        int menor = -1;

        // Procura o processo pronto com menor tempo restante
        for (int i = 0; i < quantidade; i++) {
            if (processos[i].tempoChegada <= tempoAtual &&
                processos[i].tempoRestante > 0) {

                if (menor == -1 ||
                    processos[i].tempoRestante <
                    processos[menor].tempoRestante) {
                    menor = i;
                }
            }
        }

        // Nenhum processo disponivel
        if (menor == -1) {
            printf("Tempo %d: CPU ociosa\n", tempoAtual);
            tempoAtual++;
            continue;
        }

        // Executa o processo por uma unidade de tempo
        printf("Tempo %d: Executando %s\n",
               tempoAtual, processos[menor].nome);

        mostrarProntos(processos, quantidade, tempoAtual, menor);
        processos[menor].tempoRestante--;
        tempoAtual++;

        // Verifica se o processo terminou
        if (processos[menor].tempoRestante == 0) {
            concluidos++;

            printf("Processo %s finalizado no tempo %d\n",
                   processos[menor].nome, tempoAtual);
        }
    }

    printf("\nTodos os processos foram finalizados!\n");
}

// Funcao principal
int main() {
    Processo processos[MAX_PROCESSOS];
    int quantidade;
    int opcao;

    do {
        printf("\n====================================\n");
        printf(" SIMULADOR DE ESCALONAMENTO DE CPU\n");
        printf("====================================\n");
        printf("1 - Shortest Remaining Time (SRT)\n");
        printf("2 - Round-Robin (RR)\n");
        printf("0 - Sair\n");
        printf("------------------------------------\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada invalida!\n");
            return 1;
        }

        switch (opcao) {
            case 1:
            case 2:
                do {
                    printf("\nQuantidade de processos (1 a %d): ",
                           MAX_PROCESSOS);

                    if (scanf("%d", &quantidade) != 1) {
                        printf("Entrada invalida!\n");
                        return 1;
                    }

                    if (quantidade < 1 || quantidade > MAX_PROCESSOS) {
                        printf("Quantidade invalida!\n");
                    }

                } while (quantidade < 1 || quantidade > MAX_PROCESSOS);

                cadastrarProcessos(processos, quantidade);
                listarProcessos(processos, quantidade);

                if (opcao == 1) {
                    executarSRT(processos, quantidade);
                } else {
                    printf("\nRound-Robin em desenvolvimento...\n");
                }
                break;

            case 0:
                printf("\nEncerrando o programa...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
