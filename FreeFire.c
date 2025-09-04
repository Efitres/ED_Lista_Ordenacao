// Código da Ilha – Edição Free Fire
// Nível: Novato
//A missão inicial é construir um sistema de inventário que simule a mochila de loot inicial do jogador


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// ================================
//        Estrutura do o Item
// ================================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ================================
//         Área das funções
// ================================
void inserirItem(Item inventario[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\n Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", novo.nome); // lê string com espaços
    printf("Digite o tipo do item (arma, munição, cura, etc): ");
    scanf(" %[^\n]", novo.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    inventario[*qtd] = novo;
    (*qtd)++;

    printf("\n Item adicionado com sucesso!\n");
}

void listarItens(Item inventario[], int qtd) {
    printf("\n Itens na mochila (%d/%d):\n\n", qtd, MAX_ITENS);
    if (qtd == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    for (int i = 0; i < qtd; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, inventario[i].nome, inventario[i].tipo, inventario[i].quantidade);
    }
}

void removerItem(Item inventario[], int *qtd) {
    if (*qtd == 0) {
        printf("\n A mochila está vazia!\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item a ser removido: ");
    scanf(" %[^\n]", nomeRemover);

    int encontrado = -1;
    for (int i = 0; i < *qtd; i++) {
        if (strcmp(inventario[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\n Item não encontrado!\n");
        return;
    }

    // "Puxa" os elementos para preencher o espaço
    for (int i = encontrado; i < *qtd - 1; i++) {
        inventario[i] = inventario[i + 1];
    }
    (*qtd)--;

    printf("\n Item removido com sucesso!\n");
}

void buscarItem(Item inventario[], int qtd) {
    if (qtd == 0) {
        printf("\n A mochila está vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item para buscar: ");
    scanf(" %[^\n]", nomeBusca);

    for (int i = 0; i < qtd; i++) {
        if (strcmp(inventario[i].nome, nomeBusca) == 0) {
            printf("\n Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   inventario[i].nome, inventario[i].tipo, inventario[i].quantidade);
            return;
        }
    }

    printf("\n Item não encontrado na mochila.\n");
}

// ================================
// Main orquestrando as chamadas e loop
// ================================
int main() {
    Item inventario[MAX_ITENS];
    int qtd = 0;
    int opcao;

    do {
        printf("\n===============================================\n");
        printf("=====Mochila de sobrevivência - código da ilha\n");
        printf("===============================================\n\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(inventario, &qtd);
                listarItens(inventario, qtd);
                break;
            case 2:
                removerItem(inventario, &qtd);
                listarItens(inventario, qtd);
                break;
            case 3:
                listarItens(inventario, qtd);
                break;
            case 4:
                buscarItem(inventario, qtd);
                break;
            case 0:
                printf("\n Saindo do jogo. Até a próxima!\n");
                break;
            default:
                printf("\n Opcao inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
