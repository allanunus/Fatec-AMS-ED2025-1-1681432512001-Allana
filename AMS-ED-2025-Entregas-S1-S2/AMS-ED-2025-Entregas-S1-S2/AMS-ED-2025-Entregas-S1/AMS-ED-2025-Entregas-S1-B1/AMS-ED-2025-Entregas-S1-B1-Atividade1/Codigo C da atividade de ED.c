#include <stdio.h>

int calcular_valor_final(int valor, int desconto) {
    return valor - desconto;
}

int main() {
    int val, desc, tot; 
    int* Xv = &val;  
    int* Xd = &desc;  
    int* Xt = &tot;

    printf("Digite o valor do produto: \n");
    scanf("%d", Xv);

    printf("Digite o valor do desconto: \n");
    scanf("%d", Xd);

    if (*Xv < *Xd) {
        printf("Erro: o desconto não pode ser maior que o valor do produto.\n"); 
    } else {
        *Xt = calcular_valor_final(*Xv, *Xd); 

        printf("Valor Original do Produto: %d\n", *Xv);
        printf("Valor do Desconto: %d\n", *Xd); 
        printf("Valor Final do Produto: %d\n", *Xt); 
    }

    return 0;
}
