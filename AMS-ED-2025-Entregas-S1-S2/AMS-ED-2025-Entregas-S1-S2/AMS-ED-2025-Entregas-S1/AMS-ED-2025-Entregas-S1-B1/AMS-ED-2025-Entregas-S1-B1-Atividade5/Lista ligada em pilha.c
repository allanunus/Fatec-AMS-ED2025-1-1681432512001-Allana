/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: Atividade B1-5                          */
/*             Objetivo:    Transforma Lista Ligada em Pilha                        */
/*                                                                                  */
/*                      Autor: Allana Aparecida Rizzo Ribeiro                       */
/*                                                                   Data:01/04/2025*/
/*----------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    PENDENTE,
    EM_PREPARO,
    PRONTO,
    ENTREGUE
} StatusPedido;

typedef struct Pedido {
    int numero_pedido;
    char nome_cliente[100];
    char descricao_prato[100];
    int quantidade;
    StatusPedido status;
    struct Pedido* proximo;
} Pedido;

typedef struct {
    Pedido* topo;
    int total_pedidos;
} Pilha;

const char* status_para_string(StatusPedido status) {
    switch (status) {
        case PENDENTE: return "PENDENTE";
        case EM_PREPARO: return "EM PREPARO";
        case PRONTO: return "PRONTO";
        case ENTREGUE: return "ENTREGUE";
        default: return "DESCONHECIDO";
    }
}

Pilha* criar_pilha() {
    Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));
    if (!pilha) {
        printf("Erro ao criar a pilha!\n");
        return NULL;
    }
    pilha->topo = NULL;
    pilha->total_pedidos = 0;
    return pilha;
}

void empilhar(Pilha* pilha, int numero, const char* nome_cliente, const char* descricao, int quantidade, StatusPedido status) {
    Pedido* novo_pedido = (Pedido*) malloc(sizeof(Pedido));
    if (!novo_pedido) {
        printf("Erro ao alocar memória para novo pedido!\n");
        return;
    }

    novo_pedido->numero_pedido = numero;
    strcpy(novo_pedido->nome_cliente, nome_cliente);
    strcpy(novo_pedido->descricao_prato, descricao);
    novo_pedido->quantidade = quantidade;
    novo_pedido->status = status;
    novo_pedido->proximo = pilha->topo;
    pilha->topo = novo_pedido;
    pilha->total_pedidos++;

    printf("Pedido %d adicionado com sucesso!\n", numero);
}

void remover_pedido(Pilha* pilha) {
    if (pilha->topo == NULL) {
        printf("A pilha está vazia, não há pedidos para remover!\n");
        return;
    }

    Pedido* temp = pilha->topo;
    pilha->topo = pilha->topo->proximo;
    free(temp);
    pilha->total_pedidos--;
    printf("Pedido removido com sucesso!\n");
}

void exibir_menu() {
    printf("\n===== MENU =====\n");
    printf("1. Adicionar novo pedido\n");
    printf("2. Exibir pedido\n");
    printf("3. Alterar pedido\n");
    printf("4. Remover pedido\n");
    printf("5. Sair\n");
    printf("================\n");
    printf("Escolha uma opção: ");
}

int main() {
    Pilha* pilha_pedidos = criar_pilha();
    int numero, quantidade, opcao;
    char nome_cliente[100], descricao_prato[100];
    StatusPedido status;

    while (1) {
        exibir_menu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Número do pedido: ");
                scanf("%d", &numero);
                getchar();
                printf("Nome do cliente: ");
                fgets(nome_cliente, sizeof(nome_cliente), stdin);
                nome_cliente[strcspn(nome_cliente, "\n")] = '\0';
                printf("Descrição do prato: ");
                fgets(descricao_prato, sizeof(descricao_prato), stdin);
                descricao_prato[strcspn(descricao_prato, "\n")] = '\0';
                printf("Quantidade: ");
                scanf("%d", &quantidade);
                int status_int;
                printf("Status (0 - PENDENTE, 1 - EM PREPARO, 2 - PRONTO, 3 - ENTREGUE): ");
                scanf("%d", &status_int);
                status = (StatusPedido)status_int;
                empilhar(pilha_pedidos, numero, nome_cliente, descricao_prato, quantidade, status);
                break;

            case 4:
                remover_pedido(pilha_pedidos);
                break;

            case 5:
                free(pilha_pedidos);
                printf("Saindo...\n");
                return 0;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}
