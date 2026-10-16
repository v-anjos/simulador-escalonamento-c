# 🖥️ Simulador de Algoritmos de Escalonamento de Processos

![Linguagem C](https://img.shields.io/badge/Linguagem-C-00599C?logo=c&logoColor=white)
![GCC](https://img.shields.io/badge/Compilador-GCC-blue)
![Commits](https://img.shields.io/github/commit-activity/t/v-anjos/simulador-escalonamento-c?label=Commits&color=brightgreen)
![Status](https://img.shields.io/badge/Status-Conclu%C3%ADdo-success)

## 📌 Sobre o projeto

Este repositório apresenta um simulador de algoritmos de escalonamento de processos, desenvolvido em **linguagem C** como trabalho avaliativo da disciplina de **Sistemas Operacionais**.

O objetivo é demonstrar como diferentes algoritmos gerenciam o uso da CPU, permitindo acompanhar a execução dos processos, seus tempos restantes e a fila de prontos por meio de uma timeline no terminal.

O projeto implementa dois algoritmos:

- **Shortest Remaining Time (SRT)**
- **Round-Robin (RR)**

## 🎯 Funcionalidades

- [x] Menu interativo de seleção dos algoritmos.
- [x] Cadastro manual de processos.
- [x] Configuração dos tempos de chegada e execução.
- [x] Implementação do SRT preemptivo.
- [x] Implementação do Round-Robin.
- [x] Configuração do quantum.
- [x] Exibição da execução a cada unidade de tempo.
- [x] Visualização dos processos prontos e tempos restantes.
- [x] Identificação de períodos com CPU ociosa.
- [x] Indicação da conclusão dos processos.

## ⚙️ Algoritmos implementados

### 1. Shortest Remaining Time (SRT)

O SRT é um algoritmo de escalonamento **preemptivo** que seleciona o processo com o menor tempo de execução restante.

A cada unidade de tempo, o escalonador verifica os processos disponíveis e seleciona aquele que possui o menor tempo restante, podendo interromper o processo atual.

**Características:**

- Escalonamento preemptivo.
- Priorização do menor tempo restante.
- Consideração dos tempos de chegada.
- Reavaliação da CPU a cada unidade de tempo.

### 2. Round-Robin (RR)

O Round-Robin é um algoritmo de escalonamento **preemptivo** baseado em uma fila de processos prontos.

Cada processo recebe uma fatia de tempo denominada **quantum**. Caso não finalize nesse intervalo, retorna ao final da fila.

**Características:**

- Utilização de fila circular.
- Distribuição do tempo de CPU.
- Quantum configurável.
- Respeito à ordem da fila de prontos.
- Revezamento entre os processos.

## 📥 Entradas do sistema

| Entrada | Descrição |
|---|---|
| Nome do processo | Identificador, como P1 ou P2 |
| Burst Time | Tempo total de execução |
| Arrival Time | Instante de chegada |
| Quantum | Tempo máximo por turno no Round-Robin |

Todos os dados são configurados antes da simulação.

## 📊 Timeline de execução

O simulador apresenta a evolução dos processos a cada unidade de tempo, identificando o processo em execução na CPU e os processos aguardando na fila de prontos.

### Exemplo de SRT

| Processo | Chegada | Execução |
|---|---:|---:|
| P1 | 0 | 8 |
| P2 | 2 | 4 |
| P3 | 4 | 2 |

**Sequência de execução:**

```text
Tempo 0-2:   P1
Tempo 2-6:   P2
Tempo 6-8:   P3
Tempo 8-14:  P1
```

### Exemplo de Round-Robin

Considerando quantum igual a 2:

| Processo | Chegada | Execução |
|---|---:|---:|
| P1 | 0 | 5 |
| P2 | 0 | 3 |
| P3 | 0 | 2 |

**Sequência de execução:**

```text
Tempo 0-2:   P1
Tempo 2-4:   P2
Tempo 4-6:   P3
Tempo 6-8:   P1
Tempo 8-9:   P2
Tempo 9-10:  P1
```

## 🛠️ Tecnologias utilizadas

- **Linguagem:** C
- **Compilador:** GCC
- **Interface:** Terminal
- **Versionamento:** Git
- **Repositório:** GitHub

## 📂 Estrutura do repositório

```text
simulador-escalonamento-c/
│
├── simulador.c    # Código-fonte completo
└── README.md      # Documentação do projeto
```

Todo o simulador foi desenvolvido em um único arquivo `.c`, utilizando funções para organizar o cadastro, o escalonamento e a exibição dos resultados.

## 🚀 Como executar

### Pré-requisitos

É necessário possuir o compilador GCC instalado.

### 1. Clonar o repositório

```bash
git clone https://github.com/v-anjos/simulador-escalonamento-c.git
```

### 2. Acessar a pasta

```bash
cd simulador-escalonamento-c
```

### 3. Compilar

**Linux:**

```bash
gcc -Wall -Wextra -std=c11 simulador.c -o simulador
```

**Windows:**

```bash
gcc -Wall -Wextra -std=c11 simulador.c -o simulador.exe
```

### 4. Executar

**Linux:**

```bash
./simulador
```

**Windows:**

```bash
.\simulador.exe
```

### 5. Utilizar o simulador

O programa apresentará um menu:

```text
====================================
 SIMULADOR DE ESCALONAMENTO DE CPU
====================================
1 - Shortest Remaining Time (SRT)
2 - Round-Robin (RR)
0 - Sair
------------------------------------
Escolha uma opcao:
```

Selecione o algoritmo, cadastre os processos e acompanhe a execução no terminal.

## 📈 Histórico de desenvolvimento

O desenvolvimento foi realizado de forma incremental, utilizando Git e GitHub para registrar as alterações no código.

O contador de commits exibido no início deste README é atualizado automaticamente pelo serviço de badges.

**[📜 Visualizar histórico completo de commits](https://github.com/v-anjos/simulador-escalonamento-c/commits/main/)**

## 🎥 Vídeo de apresentação

O vídeo apresenta a estrutura do código-fonte, a implementação dos algoritmos e demonstrações práticas das simulações.

**▶️ [Assistir à apresentação no YouTube](https://www.youtube.com/watch?v=VRuTR_Uqvq4)**

## 👥 Integrantes

- Kaiky Otavio Brito Oliveira
- Douglas Ruan Corrêa
- Vinicius de Araujo dos Anjos

## 📚 Informações acadêmicas

**Disciplina:** Sistemas Operacionais  
**Trabalho avaliativo:** Algoritmos de Escalonamento  
**Linguagem:** C  
**Data de entrega:** 16/10/2026

## 📄 Licença

Projeto desenvolvido para fins acadêmicos e educacionais.
