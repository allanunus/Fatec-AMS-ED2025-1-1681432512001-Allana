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

Pedido* criar_lista() {
    return NULL;
}

Pedido* criar_pedido(int numero, const char* nome_cliente, const char* descricao, int quantidade, StatusPedido status) {
    Pedido* novo_pedido = (Pedido*) malloc(sizeof(Pedido));
    if (!novo_pedido) {
        printf("Erro: Memória insuficiente!\n");
        return NULL;
    }
    novo_pedido->numero_pedido = numero;
    strcpy(novo_pedido->nome_cliente, nome_cliente);
    strcpy(novo_pedido->descricao_prato, descricao);
    novo_pedido->quantidade = quantidade;
    novo_pedido->status = status;
    novo_pedido->proximo = NULL;
    return novo_pedido;
}

void inserir_pedido(Pedido** lista, int numero, const char* nome_cliente, const char* descricao, int quantidade, StatusPedido status) {
    Pedido* novo_pedido = criar_pedido(numero, nome_cliente, descricao, quantidade, status);
    if (!novo_pedido) return;
    if (*lista == NULL) {
        *lista = novo_pedido;
    } else {
        Pedido* temp = *lista;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novo_pedido;
    }
    printf("Pedido #%d foi registrado com sucesso!\n", numero);
}

Pedido* obter_pedido(Pedido* lista, int numero) {
    Pedido* temp = lista;
    while (temp != NULL) {
        if (temp->numero_pedido == numero) {
            return temp;
        }
        temp = temp->proximo;
    }
    return NULL;
}

int atualizar_status(Pedido* lista, int numero, StatusPedido novo_status) {
    Pedido* pedido = obter_pedido(lista, numero);
    if (pedido) {
        pedido->status = novo_status;
        return 1;
    }
    return 0;
}

int deletar_pedido(Pedido** lista, int numero) {
    Pedido* temp = *lista;
    Pedido* anterior = NULL;
    while (temp != NULL && temp->numero_pedido != numero) {
        anterior = temp;
        temp = temp->proximo;
    }
    if (temp == NULL) return 0;
    if (anterior == NULL) {
        *lista = temp->proximo;
    } else {
        anterior->proximo = temp->proximo;
    }
    free(temp);
    return 1;
}

void liberar_lista(Pedido* lista) {
    Pedido* temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->proximo;
        free(temp);
    }
}

const char* status_para_string(StatusPedido status) {
    switch (status) {
        case PENDENTE: return "Pendente";
        case EM_PREPARO: return "Em Preparo";
        case PRONTO: return "Pronto";
        case ENTREGUE: return "Entregue";
        default: return "Desconhecido";
    }
}

StatusPedido ler_status() {
    int status;
    while (1) {
        printf("Digite o status do pedido:\n");
        printf("0 - PENDENTE\n1 - EM PREPARO\n2 - PRONTO\n3 - ENTREGUE\nEscolha: ");
        if (scanf("%d", &status) == 1 && status >= 0 && status <= 3) {
            return (StatusPedido)status;
        }
        printf("Entrada inválida! Digite um número entre 0 e 3.\n");
        while (getchar() != '\n');
    }
}

int main() {
    Pedido* lista_pedidos = criar_lista();
    int numero, quantidade, opcao;
    char nome_cliente[100], descricao_prato[100];
    StatusPedido status;
    while (1) {
        printf("\n========== MENU ==========\n");
        printf("1. Adicionar pedido\n");
        printf("2. Atualizar status do pedido\n");
        printf("3. Remover pedido\n");
        printf("4. Consultar pedido\n");
        printf("5. Sair\n");
        printf("==========================\nEscolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Opção inválida! Tente novamente.\n");
            while (getchar() != '\n');
            continue;
        }
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
                status = ler_status();
                inserir_pedido(&lista_pedidos, numero, nome_cliente, descricao_prato, quantidade, status);
                break;
            case 2:
                printf("Número do pedido a ser atualizado: ");
                scanf("%d", &numero);
                status = ler_status();
                if (atualizar_status(lista_pedidos, numero, status)) {
                    printf("O status do pedido #%d foi atualizado para %s.\n", numero, status_para_string(status));
                } else {
                    printf("Pedido não encontrado!\n");
                }
                break;
            case 3:
                printf("Número do pedido a ser removido: ");
                scanf("%d", &numero);
                if (deletar_pedido(&lista_pedidos, numero)) {
                    printf("Pedido #%d removido com sucesso.\n", numero);
                } else {
                    printf("Pedido não encontrado\n");
                }
                break;
            case 4:
                printf("Número do pedido para consulta: ");
                scanf("%d", &numero);
                Pedido* pedido = obter_pedido(lista_pedidos, numero);
                if (pedido) {
                    printf("\nPedido #%d\nCliente: %s\nPrato: %s\nQuantidade: %d\nStatus: %s\n",
                           pedido->numero_pedido, pedido->nome_cliente, pedido->descricao_prato,
                           pedido->quantidade, status_para_string(pedido->status));
                } else {
                    printf("Pedido não encontrado\n");
                }
                break;
            case 5:
                liberar_lista(lista_pedidos);
                printf("Encerrando sistema...\n");
                return 0;
            default:
                printf("Opção inválida, tente novamente \n");
        }
    }
}