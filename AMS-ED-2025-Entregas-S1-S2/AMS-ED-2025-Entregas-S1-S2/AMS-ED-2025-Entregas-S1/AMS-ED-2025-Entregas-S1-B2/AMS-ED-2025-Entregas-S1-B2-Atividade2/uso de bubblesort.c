/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: Atividade B2-2                          */
/*             Objetivo:    Utilizando Bubblesort em C                              */
/*                                                                                  */
/*                      Autor: Allana Aparecida Rizzo Ribeiro                       */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/
 
#include <stdio.h>
int main()
{
  int array[100], n, c, d, swap;
  printf("Digite o número de números que vc deseja:\n"); //pede pra digitar quantos numeros quer
  scanf("%d", &n);
  printf("Digite %d apenas números inteiros\n", n); //pede pra digitar os numeros inteiros
  for (c = 0; c < n; c++) //O uso de Bubblesort
    scanf("%d", &array[c]);
  for (c = 0 ; c < n - 1; c++)
  {
    for (d = 0 ; d < n - c - 1; d++)
    {
      if (array[d] > array[d+1]) //aqui é pra deixar os numeros em ordem crescente
      {
        swap       = array[d];
        array[d]   = array[d+1];
        array[d+1] = swap;
      }
    }
  }
  printf("Seus números escolhidos em ordem crescente:\n"); //aqui mostra os numeros em ordem crescente
  for (c = 0; c < n; c++)
     printf("%d\n", array[c]);
  return 0;
}