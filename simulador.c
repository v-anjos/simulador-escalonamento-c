#include <stdio.h>

typedef struct {
    char nome[25];
    int tempoChegada;
    int tempoExec;
    int tempoRestante;
} Processo;

int main() {
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
