# Simulador de Algoritmos de Escalonamento de Processos

## 📌 Sobre o projeto

Este repositório contém o desenvolvimento de um simulador de algoritmos de escalonamento de processos, implementado em **linguagem C**, como parte de um trabalho avaliativo da disciplina de Sistemas Operacionais.

O objetivo é simular o gerenciamento da CPU por diferentes algoritmos de escalonamento, permitindo acompanhar a execução dos processos ao longo do tempo.

## 🎯 Objetivos

- Implementar os algoritmos **Shortest Remaining Time (SRT)** e **Round-Robin (RR)**.
- Permitir o cadastro manual dos processos antes da simulação.
- Simular a execução dos processos a cada unidade de tempo.
- Exibir os processos prontos, seus tempos restantes e o processo em execução.
- Representar o escalonamento por meio de uma timeline no terminal.

## ⚙️ Algoritmos

### 1. Shortest Remaining Time (SRT)

O SRT é um algoritmo de escalonamento preemptivo que seleciona o processo com o menor tempo de execução restante.

Quando um novo processo chega ao sistema, o escalonador verifica se ele possui um tempo restante menor que o processo atualmente em execução, podendo realizar a preempção.

### 2. Round-Robin (RR)

O Round-Robin é um algoritmo de escalonamento preemptivo que distribui o tempo de CPU entre os processos prontos.

Cada processo recebe uma fatia de tempo, denominada **quantum**. Caso não finalize sua execução nesse intervalo, retorna à fila de processos prontos.

## 📥 Entradas do sistema

O simulador deverá permitir a configuração dos seguintes dados:

| Entrada | Descrição |
|---|---|
| Nome do processo | Identificador do processo (P1, P2, etc.) |
| Burst Time | Tempo total de processamento necessário |
| Arrival Time | Instante de chegada do processo |
| Quantum | Fatia de tempo utilizada pelo Round-Robin |

## 📊 Saída esperada

A simulação deverá apresentar, a cada unidade de tempo:

- O instante atual da simulação;
- O processo em execução na CPU;
- Os processos que estão na fila de prontos;
- O tempo de processamento restante de cada processo pronto;
- A evolução temporal da execução dos processos.

## 🛠️ Tecnologias utilizadas

- **Linguagem:** C
- **Compilador:** GCC
- **Interface:** Terminal
- **Versionamento:** Git e GitHub

## 🚧 Status do desenvolvimento

O projeto está em desenvolvimento.

- [x] Criação e documentação inicial do repositório
- [ ] Estruturação dos arquivos do projeto
- [ ] Definição das estruturas de dados dos processos
- [ ] Implementação da entrada manual dos processos
- [ ] Implementação do algoritmo SRT
- [ ] Implementação do algoritmo Round-Robin
- [ ] Implementação da timeline
- [ ] Testes e validação das simulações
- [ ] Documentação final e instruções de execução
- [ ] Gravação do vídeo de apresentação

## 👥 Integrantes

- Integrante 1
- Integrante 2
- Vinicius de Araujo dos Anjos

## 📚 Informações acadêmicas

**Disciplina:** Sistemas Operacionais  
**Trabalho:** Algoritmos de Escalonamento  
**Linguagem:** C  
**Data de entrega:** 16/10/2026

## 📄 Licença

Projeto desenvolvido para fins acadêmicos e educacionais.
