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

void executarSRT(Processo processos[], int quantidade) {
    int tempo = 0, concluidos = 0;
    puts("\n========== TIMELINE SRT ==========");
    while (concluidos < quantidade) {
        int escolhido = -1;
        for (int i = 0; i < quantidade; i++) {
            if (processos[i].tempoChegada > tempo || processos[i].tempoRestante == 0) continue;
            if (escolhido == -1 ||
                processos[i].tempoRestante < processos[escolhido].tempoRestante ||
                (processos[i].tempoRestante == processos[escolhido].tempoRestante &&
                 processos[i].tempoChegada < processos[escolhido].tempoChegada)) {
                escolhido = i;
            }
        }
        if (escolhido == -1) {
            printf("Tempo [%d - %d] | CPU: Ociosa\n", tempo, tempo + 1);
            mostrarProntosSRT(processos, quantidade, tempo, -1);
        } else {
            printf("Tempo [%d - %d] | CPU: %s (restante antes: %d)\n",
                   tempo, tempo + 1, processos[escolhido].nome,
                   processos[escolhido].tempoRestante);
            mostrarProntosSRT(processos, quantidade, tempo, escolhido);
            processos[escolhido].tempoRestante--;
            if (processos[escolhido].tempoRestante == 0) {
                concluidos++;
                printf("  -> %s finalizado no tempo %d\n",
                       processos[escolhido].nome, tempo + 1);
            }
        }
        tempo++;
    }
    printf("SRT concluido no tempo %d.\n", tempo);
}

/* Fila circular com capacidade suficiente para todos os processos. */
typedef struct {
    int itens[MAX_PROCESSOS + 1];
    int inicio, fim;
} Fila;

int filaVazia(const Fila *fila) { return fila->inicio == fila->fim; }

void enfileirar(Fila *fila, int indice) {
    int proximo = (fila->fim + 1) % (MAX_PROCESSOS + 1);
    if (proximo == fila->inicio) {
        puts("Erro: fila cheia.");
        exit(EXIT_FAILURE);
    }
    fila->itens[fila->fim] = indice;
    fila->fim = proximo;
}

int desenfileirar(Fila *fila) {
    int indice = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % (MAX_PROCESSOS + 1);
    return indice;
}

void mostrarFila(const Fila *fila, const Processo processos[]) {
    printf("Prontos (ordem da fila): ");
    if (filaVazia(fila)) {
        puts("Nenhum");
        return;
    }
    for (int pos = fila->inicio; pos != fila->fim;
         pos = (pos + 1) % (MAX_PROCESSOS + 1)) {
        int i = fila->itens[pos];
        printf("%s(%d) ", processos[i].nome, processos[i].tempoRestante);
    }
    putchar('\n');
}

/* Insere os processos chegados no instante informado, na ordem de cadastro. */
void adicionarChegadas(Processo processos[], int quantidade, int tempo,
                      int entrou[], Fila *fila) {
    for (int i = 0; i < quantidade; i++) {
        if (!entrou[i] && processos[i].tempoChegada <= tempo) {
            enfileirar(fila, i);
            entrou[i] = 1;
        }
    }
}

void executarRoundRobin(Processo processos[], int quantidade, int quantum) {
    Fila fila = {{0}, 0, 0};
    int entrou[MAX_PROCESSOS] = {0};
    int tempo = 0, concluidos = 0;
    printf("\n========== TIMELINE ROUND-ROBIN (quantum = %d) ==========\n", quantum);
    adicionarChegadas(processos, quantidade, tempo, entrou, &fila);

    while (concluidos < quantidade) {
        if (filaVazia(&fila)) {
            printf("Tempo [%d - %d] | CPU: Ociosa\n", tempo, tempo + 1);
            mostrarFila(&fila, processos);
            tempo++;
            adicionarChegadas(processos, quantidade, tempo, entrou, &fila);
            continue;
        }

        int atual = desenfileirar(&fila);
        int fatia = processos[atual].tempoRestante < quantum
                    ? processos[atual].tempoRestante : quantum;

        for (int passo = 0; passo < fatia; passo++) {
            printf("Tempo [%d - %d] | CPU: %s (restante antes: %d)\n",
                   tempo, tempo + 1, processos[atual].nome,
                   processos[atual].tempoRestante);
            mostrarFila(&fila, processos);
            processos[atual].tempoRestante--;
            tempo++;
            adicionarChegadas(processos, quantidade, tempo, entrou, &fila);
        }

        if (processos[atual].tempoRestante == 0) {
            concluidos++;
            printf("  -> %s finalizado no tempo %d\n", processos[atual].nome, tempo);
        } else {
            enfileirar(&fila, atual);
        }
    }
    printf("Round-Robin concluido no tempo %d.\n", tempo);
}

int main(void) {
    Processo processos[MAX_PROCESSOS];
    int opcao, quantidade;

    do {
        puts("\n====================================");
        puts(" SIMULADOR DE ESCALONAMENTO DE CPU");
        puts("====================================");
        puts("1 - Shortest Remaining Time (SRT)");
        puts("2 - Round-Robin (RR)");
        puts("0 - Sair");
        opcao = lerInteiro("Escolha uma opcao: ", 0, 2);
        if (opcao == 0) break;

        quantidade = lerInteiro("Quantidade de processos (1 a 100): ", 1, MAX_PROCESSOS);
        cadastrarProcessos(processos, quantidade);
        listarProcessos(processos, quantidade);

        if (opcao == 1) {
            executarSRT(processos, quantidade);
        } else {
            int quantum = lerInteiro("Quantum (maior que zero): ", 1, 100000);
            executarRoundRobin(processos, quantidade, quantum);
        }
    } while (1);

    puts("\nEncerrando o simulador...");
    return 0;
}
