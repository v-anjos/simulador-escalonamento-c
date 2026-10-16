#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_PROCESSOS 100
#define TAM_NOME 20

typedef struct {
    char nome[TAM_NOME];
    int tempoChegada;
    int tempoExecucao;
    int tempoRestante;
} Processo;

int lerInteiro(const char *mensagem, int minimo, int maximo) {
    char linha[128], extra;
    int valor;
    while (1) {
        printf("%s", mensagem);
        if (!fgets(linha, sizeof(linha), stdin)) {
            puts("Entrada encerrada.");
            exit(EXIT_FAILURE);
        }
        if (strchr(linha, '\n') == NULL && !feof(stdin)) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            puts("Entrada muito longa. Tente novamente.");
            continue;
        }
        if (sscanf(linha, " %d %c", &valor, &extra) != 1 ||
            valor < minimo || valor > maximo) {
            printf("Digite um numero inteiro entre %d e %d.\n", minimo, maximo);
            continue;
        }
        return valor;
    }
}

void cadastrarProcessos(Processo processos[], int quantidade) {
    char linha[128], extra;
    for (int i = 0; i < quantidade; i++) {
        printf("\n--- Processo %d ---\n", i + 1);
        while (1) {
            printf("Nome do processo (sem espacos): ");
            if (!fgets(linha, sizeof(linha), stdin)) exit(EXIT_FAILURE);
            if (strchr(linha, '\n') == NULL && !feof(stdin)) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}
                puts("Nome muito longo.");
                continue;
            }
            if (sscanf(linha, " %19s %c", processos[i].nome, &extra) != 1) {
                puts("Informe um nome valido, com ate 19 caracteres e sem espacos.");
                continue;
            }
            int repetido = 0;
            for (int j = 0; j < i; j++) {
                if (strcmp(processos[j].nome, processos[i].nome) == 0) repetido = 1;
            }
            if (repetido) {
                puts("Esse nome ja foi cadastrado.");
                continue;
            }
            break;
        }
        processos[i].tempoChegada = lerInteiro("Tempo de chegada: ", 0, 100000);
        processos[i].tempoExecucao = lerInteiro("Tempo de execucao (Burst Time): ", 1, 100000);
        processos[i].tempoRestante = processos[i].tempoExecucao;
    }
}

void listarProcessos(const Processo processos[], int quantidade) {
    printf("\n========== PROCESSOS CADASTRADOS ==========\n");
    printf("%-20s %-10s %-10s %-10s\n", "Processo", "Chegada", "Execucao", "Restante");
    for (int i = 0; i < quantidade; i++) {
        printf("%-20s %-10d %-10d %-10d\n", processos[i].nome,
               processos[i].tempoChegada, processos[i].tempoExecucao,
               processos[i].tempoRestante);
    }
}

void mostrarProntosSRT(const Processo processos[], int quantidade, int tempo, int executando) {
    int encontrou = 0;
    printf("Prontos: ");
    for (int i = 0; i < quantidade; i++) {
        if (i != executando && processos[i].tempoChegada <= tempo &&
            processos[i].tempoRestante > 0) {
            printf("%s(%d) ", processos[i].nome, processos[i].tempoRestante);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("Nenhum");
    putchar('\n');
}
