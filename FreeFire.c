// Código da Ilha – Edição Free Fire
// Nível: Mestre
// A missão é criar um sistema de priorização e montagem de componentes da torre de fuga,
// em que o jogador pode escolher diferentes critérios de ordenação (por nome, tipo ou prioridade) e,
// após ordenar, realizar busca binária por um item-chave que destrava a ativação da torre. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// ================================
// Structs
// ================================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ================================
// Protótipos de Funções
// ================================
void adicionarComponente(Componente componentes[], int *qtd);
void descartarComponente(Componente componentes[], int *qtd);
void mostrarComponentes(Componente componentes[], int qtd);
void bubbleSortNome(Componente componentes[], int qtd, int *comparacoes);
void insertionSortTipo(Componente componentes[], int qtd, int *comparacoes);
void selectionSortPrioridade(Componente componentes[], int qtd, int *comparacoes);
int buscaBinariaPorNome(Componente componentes[], int qtd, char nome[], int *comparacoes);

// ================================
// MAIN
// ================================
int main() {
    Componente componentes[MAX_COMPONENTES];
    int qtd = 0;
    int opcao;
    int ordenadoPorNome = 0; // 0 = NÃO ORDENADO, 1 = ORDENADO
    char componenteChave[30]; // para busca binária

    do {
        printf("\n==============================================\n");
        printf(" PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
        printf("==============================================\n");
        printf("Itens na Mochila : %d/%d\n", qtd, MAX_COMPONENTES);
        printf("Status da Ordenacao por Nome: %s\n\n", ordenadoPorNome ? "ORDENADO" : "NAO ORDENADO");
        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("---------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        int comparacoes;
        clock_t inicio, fim;
        double tempo;

        switch(opcao) {
            case 1:
                adicionarComponente(componentes, &qtd);
                ordenadoPorNome = 0;
                break;
            case 2:
                descartarComponente(componentes, &qtd);
                ordenadoPorNome = 0;
                break;
            case 3:
                mostrarComponentes(componentes, qtd);
                break;
            case 4:
                printf("\nEscolha o criterio de ordenacao:\n");
                printf("1. Por Nome em Ordem Alfabética (Bubble Sort)\n");
                printf("2. Por Tipo (Insertion Sort)\n");
                printf("3. Por Prioridade de Montagem(Selection Sort)\n");
                printf("Opcao: ");
                int criterio;
                scanf("%d", &criterio);
                getchar(); // limpar buffer

                comparacoes = 0;
                inicio = clock();
                if (criterio == 1) {
                    bubbleSortNome(componentes, qtd, &comparacoes);
                    ordenadoPorNome = 1;
                    printf("\nMochila organizada por Nome!\n");
                } else if (criterio == 2) {
                    insertionSortTipo(componentes, qtd, &comparacoes);
                    ordenadoPorNome = 0;
                    printf("\nMochila organizada por Tipo!\n");
                } else if (criterio == 3) {
                    selectionSortPrioridade(componentes, qtd, &comparacoes);
                    ordenadoPorNome = 0;
                    printf("\nMochila organizada por Prioridade!\n");
                } else {
                    printf("\nOpcao invalida!\n");
                }
                fim = clock();
                tempo = (double)(fim - inicio)/CLOCKS_PER_SEC;
                printf("Comparacoes realizadas: %d | Tempo de execucao: %.6f segundos\n\n", comparacoes, tempo);
                break;
            case 5:
                if (!ordenadoPorNome) {
                    printf("\nA busca binaria so e possivel apos ordenar por Nome!\n\n");
                    break;
                }
                printf("\nDigite o nome do componente-chave: ");
                fgets(componenteChave, 30, stdin);
                componenteChave[strcspn(componenteChave, "\n")] = '\0';

                comparacoes = 0;
                inicio = clock();
                //idx : posição (índice) do componente encontrado no vetor após a busca binária.
                int idx = buscaBinariaPorNome(componentes, qtd, componenteChave, &comparacoes);
                fim = clock();
                tempo = (double)(fim - inicio)/CLOCKS_PER_SEC;

                if (idx != -1) {
                    printf("\nComponente encontrado:\n");
                    printf("Nome: %s | Tipo: %s | Prioridade: %d\n", 
                           componentes[idx].nome, componentes[idx].tipo, componentes[idx].prioridade);
                } else {
                    printf("\nComponente nao encontrado!\n");
                }
                printf("Comparacoes realizadas: %d | Tempo de execucao: %.6f segundos\n\n", comparacoes, tempo);
                break;
            case 0:
                printf("\nAtivando torre de fuga...\n");
                break;
            default:
                printf("\nOpcao invalida!\n\n");
        }

    } while(opcao != 0);

    return 0;
}

// ================================
// Funcoes auxiliares
// ================================
void adicionarComponente(Componente componentes[], int *qtd) {
    if (*qtd >= MAX_COMPONENTES) {
        printf("\nMochila cheia!\n\n");
        return;
    }
    printf("\nNome: ");
    fgets(componentes[*qtd].nome, 30, stdin);
    componentes[*qtd].nome[strcspn(componentes[*qtd].nome, "\n")] = '\0';

    printf("Tipo (Estrutural, Eletronico, Energia): ");
    fgets(componentes[*qtd].tipo, 20, stdin);
    componentes[*qtd].tipo[strcspn(componentes[*qtd].tipo, "\n")] = '\0';

    printf("Prioridade (1-10): ");
    scanf("%d", &componentes[*qtd].prioridade);
    getchar(); // limpar buffer

    (*qtd)++;
    printf("\nComponente adicionado!\n\n");
    mostrarComponentes(componentes, *qtd);
}

void descartarComponente(Componente componentes[], int *qtd) {
    if (*qtd == 0) {
        printf("\nMochila vazia!\n\n");
        return;
    }
    char nome[30];
    printf("\nDigite o nome do componente a descartar: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int i, encontrado = -1;
    for(i=0; i<*qtd; i++) {
        if(strcmp(componentes[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1) {
        printf("\nComponente nao encontrado!\n\n");
        return;
    }
    for(i=encontrado; i<*qtd-1; i++) {
        componentes[i] = componentes[i+1];
    }
    (*qtd)--;
    printf("\nComponente descartado!\n\n");
    mostrarComponentes(componentes, *qtd);
}

void mostrarComponentes(Componente componentes[], int qtd) {
    if (qtd == 0) {
        printf("\nInventario vazio!\n\n");
        return;
    }
    printf("\nComponentes na Mochila:\n\n");
    for(int i=0; i<qtd; i++) {
        printf("%d) Nome: %s | Tipo: %s | Prioridade: %d\n",
               i+1, componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }
    printf("\n");
}

// ================================
// Algoritmos de Ordenacao
// ================================
void bubbleSortNome(Componente componentes[], int qtd, int *comparacoes) {
    for(int i=0; i<qtd-1; i++) {
        for(int j=0; j<qtd-i-1; j++) {
            (*comparacoes)++;
            if(strcmp(componentes[j].nome, componentes[j+1].nome) > 0) {
                Componente temp = componentes[j];
                componentes[j] = componentes[j+1];
                componentes[j+1] = temp;
            }
        }
    }
}

void insertionSortTipo(Componente componentes[], int qtd, int *comparacoes) {
    for(int i=1; i<qtd; i++) {
        Componente chave = componentes[i];
        int j = i - 1;
        while(j >= 0 && (++(*comparacoes), strcmp(componentes[j].tipo, chave.tipo) > 0)) {
            componentes[j+1] = componentes[j];
            j--;
        }
        componentes[j+1] = chave;
    }
}

void selectionSortPrioridade(Componente componentes[], int qtd, int *comparacoes) {
    for(int i=0; i<qtd-1; i++) {
        int max_idx = i;
        for(int j=i+1; j<qtd; j++) {
            (*comparacoes)++;
            if(componentes[j].prioridade > componentes[max_idx].prioridade)
                max_idx = j;
        }
        if(max_idx != i) {
            Componente temp = componentes[i];
            componentes[i] = componentes[max_idx];
            componentes[max_idx] = temp;
        }
    }
}

// ================================
// Busca Binaria (apenas por nome)
// ================================
int buscaBinariaPorNome(Componente componentes[], int qtd, char nome[], int *comparacoes) {
    int inicio = 0, fim = qtd-1;
    while(inicio <= fim) {
        int meio = (inicio+fim)/2;
        (*comparacoes)++;
        int cmp = strcmp(componentes[meio].nome, nome);
        if(cmp == 0) return meio;
        else if(cmp < 0) inicio = meio+1;
        else fim = meio-1;
    }
    return -1;
}
