// Código da Ilha – Edição Free Fire
// Nível: Aventureiro
// A missão é desenvolver duas versões do sistema de mochila: uma usando vetor e outra com lista encadeada.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================================
// Constantes
// ================================
#define MAX_ITENS 10

// ================================
// Structs
// ================================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ================================
// Variáveis globais
// ================================
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ================================
// Protótipos - Vetor
// ================================
void inserirItemVetor(Item inventario[], int *qtd);
void removerItemVetor(Item inventario[], int *qtd);
void listarItensVetor(Item inventario[], int qtd);
int buscarSequencialVetor(Item inventario[], int qtd, char nome[]);
void ordenarVetor(Item inventario[], int qtd);
int buscarBinariaVetor(Item inventario[], int qtd, char nome[]);

// ================================
// Protótipos - Lista encadeada
// ================================
void inserirItemLista(No **lista);
void removerItemLista(No **lista);
void listarItensLista(No *lista);
No* buscarSequencialLista(No *lista, char nome[]);

// ================================
// MAIN - Loop do menu e chamadas de funções
// ================================
int main() {
    Item inventario[MAX_ITENS];
    int qtd = 0;
    No* lista = NULL;
    int estruturaEscolhida;
    int opcao;

    printf("\n================================================\n");
    printf("===== Mochila de sobrevivência - Código da Ilha =\n");
    printf("================================================\n\n");
    printf("Escolha a estrutura de mochila:\n\n");
    printf("1. Vetor (lista sequencial)\n");
    printf("2. Lista encadeada\n\n");
    printf("Opção: ");
    scanf("%d", &estruturaEscolhida);

    do {
        printf("\n===============================================\n");
        printf("===== Mochila de sobrevivência - Código da Ilha =====\n");
        printf("===============================================\n\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item (sequencial)\n");
        if (estruturaEscolhida == 1) {
            printf("5. Ordenar itens (vetor)\n");
            printf("6. Buscar item (binária, vetor)\n");
        }
        printf("0. Sair\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        char nomeBusca[30];

        switch (opcao) {
            case 1:
                if (estruturaEscolhida == 1) {
                    inserirItemVetor(inventario, &qtd);
                    listarItensVetor(inventario, qtd);
                } else {
                    inserirItemLista(&lista);
                    listarItensLista(lista);
                }
                break;

            case 2:
                if (estruturaEscolhida == 1)
                    removerItemVetor(inventario, &qtd);
                else
                    removerItemLista(&lista);
                break;

            case 3:
                if (estruturaEscolhida == 1)
                    listarItensVetor(inventario, qtd);
                else
                    listarItensLista(lista);
                break;

            case 4:
                printf("\nDigite o nome do item para buscar: ");
                scanf(" %[^\n]", nomeBusca);
                if (estruturaEscolhida == 1) {
                    comparacoesSequencial = 0;
                    int idx = buscarSequencialVetor(inventario, qtd, nomeBusca);
                    if (idx != -1) {
                        printf("\nItem encontrado:\n");
                        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                               inventario[idx].nome, inventario[idx].tipo, inventario[idx].quantidade);
                    } else {
                        printf("\nItem nao encontrado.\n");
                    }
                    printf("Comparacoes feitas: %d\n\n", comparacoesSequencial);
                } else {
                    comparacoesSequencial = 0;
                    No* achado = buscarSequencialLista(lista, nomeBusca);
                    if (achado != NULL) {
                        printf("\nItem encontrado:\n");
                        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                               achado->dados.nome, achado->dados.tipo, achado->dados.quantidade);
                    } else {
                        printf("\nItem nao encontrado.\n");
                    }
                    printf("Comparacoes feitas: %d\n\n", comparacoesSequencial);
                }
                break;

            case 5:
                if (estruturaEscolhida == 1) {
                    ordenarVetor(inventario, qtd);
                    printf("\nItens ordenados por nome!\n\n");
                } else {
                    printf("\nOpcao invalida para lista encadeada.\n\n");
                }
                break;

            case 6:
                if (estruturaEscolhida == 1) {
                    printf("\nDigite o nome do item para buscar: ");
                    scanf(" %[^\n]", nomeBusca);
                    comparacoesBinaria = 0;
                    int idx = buscarBinariaVetor(inventario, qtd, nomeBusca);
                    if (idx != -1) {
                        printf("\nItem encontrado:\n");
                        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                               inventario[idx].nome, inventario[idx].tipo, inventario[idx].quantidade);
                    } else {
                        printf("\nItem nao encontrado.\n");
                    }
                    printf("Comparacoes feitas (busca binaria): %d\n\n", comparacoesBinaria);
                } else {
                    printf("\nOpcao invalida para lista encadeada.\n\n");
                }
                break;

            case 0:
                printf("\nSaindo...\n\n");
                break;

            default:
                printf("\nOpcao invalida!\n\n");
        }

    } while (opcao != 0);

    return 0;
}

// ================================
// Implementacoes - Vetor
// ================================
void inserirItemVetor(Item inventario[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\nMochila cheia!\n\n");
        return;
    }
    Item novo;
    printf("\nNome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    inventario[*qtd] = novo;
    (*qtd)++;
}

void removerItemVetor(Item inventario[], int *qtd) {
    if (*qtd == 0) {
        printf("\nMochila vazia!\n\n");
        return;
    }
    char nome[30];
    printf("\nNome do item a remover: ");
    scanf(" %[^\n]", nome);
    int i, encontrado = -1;
    for (i = 0; i < *qtd; i++) {
        if (strcmp(inventario[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1) {
        printf("\nItem nao encontrado.\n\n");
        return;
    }
    for (i = encontrado; i < *qtd - 1; i++) {
        inventario[i] = inventario[i + 1];
    }
    (*qtd)--;
    printf("\nItem removido!\n\n");
}

void listarItensVetor(Item inventario[], int qtd) {
    if (qtd == 0) {
        printf("\nMochila vazia!\n\n");
        return;
    }
    printf("\nItens na mochila:\n\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, inventario[i].nome, inventario[i].tipo, inventario[i].quantidade);
    }
    printf("\n");
}

int buscarSequencialVetor(Item inventario[], int qtd, char nome[]) {
    for (int i = 0; i < qtd; i++) {
        comparacoesSequencial++;
        if (strcmp(inventario[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

void ordenarVetor(Item inventario[], int qtd) {
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = i + 1; j < qtd; j++) {
            if (strcmp(inventario[i].nome, inventario[j].nome) > 0) {
                Item temp = inventario[i];
                inventario[i] = inventario[j];
                inventario[j] = temp;
            }
        }
    }
}

int buscarBinariaVetor(Item inventario[], int qtd, char nome[]) {
    int inicio = 0, fim = qtd - 1, meio;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(inventario[meio].nome, nome);
        if (cmp == 0) {
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}

// ================================
// Implementacoes - Lista encadeada
// ================================
void inserirItemLista(No **lista) {
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) {
        printf("\nErro de memoria!\n\n");
        return;
    }
    printf("\nNome: ");
    scanf(" %[^\n]", novo->dados.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    novo->proximo = *lista;
    *lista = novo;
}

void removerItemLista(No **lista) {
    if (*lista == NULL) {
        printf("\nMochila vazia!\n\n");
        return;
    }
    char nome[30];
    printf("\nNome do item a remover: ");
    scanf(" %[^\n]", nome);
    No* atual = *lista;
    No* anterior = NULL;
    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("\nItem nao encontrado.\n\n");
        return;
    }
    if (anterior == NULL) {
        *lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    printf("\nItem removido!\n\n");
}

void listarItensLista(No *lista) {
    if (lista == NULL) {
        printf("\nMochila vazia!\n\n");
        return;
    }
    printf("\nItens na mochila:\n\n");
    int i = 1;
    while (lista != NULL) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
               i++, lista->dados.nome, lista->dados.tipo, lista->dados.quantidade);
        lista = lista->proximo;
    }
    printf("\n");
}

No* buscarSequencialLista(No *lista, char nome[]) {
    while (lista != NULL) {
        comparacoesSequencial++;
        if (strcmp(lista->dados.nome, nome) == 0) {
            return lista;
        }
        lista = lista->proximo;
    }
    return NULL;
}
