/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: Atividade B1-4                          */
/*             Objetivo:    Manipulação de Pilha - Implementado HP12c               */
/*                                                                                  */
/*                      Autor: Allana Aparecida Rizzo Ribeiro                       */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 10

typedef struct {
    double itens[MAX];
    int topo;
} Pilha;

typedef struct {
    char expressao[MAX][20];
    int topo;
} PilhaExpressao;

Pilha* criar_pilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->topo = -1;
    return p;
}

PilhaExpressao* criar_pilha_expressao() {
    PilhaExpressao* p = (PilhaExpressao*)malloc(sizeof(PilhaExpressao));
    p->topo = -1;
    return p;
}

int vazia(Pilha* p) {
    return p->topo == -1;
}

int cheia(Pilha* p) {
    return p->topo == MAX - 1;
}

void push(Pilha* p, double valor) {
    if (cheia(p)) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    p->itens[++p->topo] = valor;
}

double pop(Pilha* p) {
    if (vazia(p)) {
        printf("Erro: Pilha vazia!\n");
        return 0;
    }
    return p->itens[p->topo--];
}

void push_expressao(PilhaExpressao* p, char* expr) {
    if (p->topo == MAX - 1) {
        printf("Erro: Pilha de expressões cheia!\n");
        return;
    }
    strcpy(p->expressao[++p->topo], expr);
}

char* pop_expressao(PilhaExpressao* p) {
    if (p->topo == -1) {
        return "";
    }
    return p->expressao[p->topo--];
}

double calcular_RPN(char* expressao, char* expressao_alg) {
    Pilha* p = criar_pilha();
    PilhaExpressao* pExp = criar_pilha_expressao();
    char* token = strtok(expressao, " ");
    
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(p, atof(token));
            push_expressao(pExp, token);
        } else {
            if (p->topo < 1) {
                printf("Erro: Expressão inválida!\n");
                free(p);
                free(pExp);
                return 0;
            }
            double b = pop(p);
            double a = pop(p);
            char op1[20], op2[20], resultado_expr[50];
            strcpy(op2, pop_expressao(pExp));
            strcpy(op1, pop_expressao(pExp));

            double resultado;
            switch (token[0]) {
                case '+': resultado = a + b; break;
                case '-': resultado = a - b; break;
                case '*': resultado = a * b; break;
                case '/': 
                    if (b == 0) {
                        printf("Erro: Divisão por zero\n");
                        free(p);
                        free(pExp);
                        return 0;
                    }
                    resultado = a / b;
                    break;
                default:
                    printf("Operador inválido: %s\n", token);
                    free(p);
                    free(pExp);
                    return 0;
            }
            sprintf(resultado_expr, "(%s %c %s)", op1, token[0], op2);
            push(p, resultado);
            push_expressao(pExp, resultado_expr);
        }
        token = strtok(NULL, " ");
    }
    
    if (p->topo != 0) {
        printf("Erro: Expressão mal formada\n");
        free(p);
        free(pExp);
        return 0;
    }
    
    strcpy(expressao_alg, pop_expressao(pExp));
    double resultado_final = pop(p);
    free(p);
    free(pExp);
    return resultado_final;
}

int main() {
    char expressao[100], expressao_alg[100];
    printf("Digite a expressão RPN: ");
    fgets(expressao, sizeof(expressao), stdin);
    expressao[strcspn(expressao, "\n")] = 0;
    
    double resultado = calcular_RPN(expressao, expressao_alg);
    printf("Fórmula algébrica: %s\n", expressao_alg);
    printf("Resultado: %.2f\n", resultado);
    
    return 0;
}