#include <stdio.h>
#define MAX_PROCESSOS 100

typedef struct {
    char nome[25];
    int tempoChegada;
    int tempoExecucao;
    int tempoRestante;
} Processo;

void listarProcessos(Processo processos[], int quantidade) {
    printf("\n========== PROCESSOS CADASTRADOS ==========\n");
    printf("%-12s %-12s %-12s %-12s\n", "Processo", "Chegada", "Execucao", "Restante");

    for (int i = 0; i < quantidade; i++) {
        printf("%-12s %-12d %-12d %-12d\n",
               processos[i].nome,
               processos[i].tempoChegada,
               processos[i].tempoExecucao,
               processos[i].tempoRestante);
    }
}

void cadastrarProcessor(Processo processos[], int quantidade) {
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
        }while (processos[i].tempoExecucao <= 0);

        processos[i].tempoRestante = processos[i].tempoExecucao;
    }
}

int main() {
    int opcao, quantidade;
    Processo processos[MAX_PROCESSOS]; 
    
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
                printf("\nAlgoritmo SRT selecionado.\n");
                printf("Em desenvolvimento...\n");
                break;

            case 2:
                printf("\nAlgoritmo Round-Robin selecionado.\n");
                printf("Em desenvolvimento...\n");
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
