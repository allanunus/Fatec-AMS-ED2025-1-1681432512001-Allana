#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATOS 50

typedef struct {
    char nome[100];
    float provaescrita[4];
    float analisecurricular[5];
    float provapratica[10];
    float entrevistabanca[3];
    float notafinal;
} Candidato;

float calcularSomaNotasCentrais(float *notas, int quantidade) {
    float maior = notas[0], menor = notas[0], soma = 0;
    for (int i = 0; i < quantidade; i++) {
        if (notas[i] > maior) maior = notas[i];
        if (notas[i] < menor) menor = notas[i];
        soma += notas[i];
    }
    return soma - maior - menor;
}

float calcularNotaFinal(Candidato *candidato) {
    float somaPE = calcularSomaNotasCentrais(candidato->provaescrita, 4);
    float somaAC = calcularSomaNotasCentrais(candidato->analisecurricular, 5);
    float somaPP = calcularSomaNotasCentrais(candidato->provapratica, 10);
    float somaEB = calcularSomaNotasCentrais(candidato->entrevistabanca, 3);
    return (somaPE * 0.3) + (somaAC * 0.1) + (somaPP * 0.4) + (somaEB * 0.2);
}

void ordenarCandidatos(Candidato *candidatos, int totcandidatos) {
    for (int i = 0; i < totcandidatos - 1; i++) {
        for (int j = 0; j < totcandidatos - i - 1; j++) {
            if (candidatos[j].notafinal < candidatos[j + 1].notafinal) {
                Candidato temp = candidatos[j];
                candidatos[j] = candidatos[j + 1];
                candidatos[j + 1] = temp;
            }
        }
    }
}

int main() {
    Candidato candidatos[MAX_CANDIDATOS];
    int totcandidatos = 0;
    char resposta;

    printf("Programa de Seleção para Residência Médica\n");
    
    while (totcandidatos < MAX_CANDIDATOS) {
        printf("\nCandidato %d:\n", totcandidatos + 1);
        printf("Nome: ");
        fgets(candidatos[totcandidatos].nome, sizeof(candidatos[totcandidatos].nome), stdin);
        candidatos[totcandidatos].nome[strcspn(candidatos[totcandidatos].nome, "\n")] = 0;

        printf("Notas da Prova Escrita (4 notas):\n");
        for (int i = 0; i < 4; i++) scanf("%f", &candidatos[totcandidatos].provaescrita[i]);

        printf("Notas da Análise Curricular (5 notas):\n");
        for (int i = 0; i < 5; i++) scanf("%f", &candidatos[totcandidatos].analisecurricular[i]);
        
        printf("Notas da Prova Prática (10 notas):\n");
        for (int i = 0; i < 10; i++) scanf("%f", &candidatos[totcandidatos].provapratica[i]);
        
        printf("Notas da Entrevista em Banca Avaliadora (3 notas):\n");
        for (int i = 0; i < 3; i++) scanf("%f", &candidatos[totcandidatos].entrevistabanca[i]);

        candidatos[totcandidatos].notafinal = calcularNotaFinal(&candidatos[totcandidatos]);
        while (getchar() != '\n');
        
        totcandidatos++;
        printf("Deseja adicionar mais candidatos? (s/n): ");
        scanf(" %c", &resposta);
        while (getchar() != '\n');
        if (resposta != 's' && resposta != 'S') break;
    }

    ordenarCandidatos(candidatos, totcandidatos);
    printf("\n Classificação dos 5 Melhores Candidatos:\n");
    for (int i = 0; i < (totcandidatos < 5 ? totcandidatos : 5); i++) {
        printf("%d. %s - Nota Final: %.2f\n", i + 1, candidatos[i].nome, candidatos[i].notafinal);
    }
    
    printf("\n Estado da Memória do Primeiro Candidato:\n");
    printf("Nome: %s\n", candidatos[0].nome);
    printf("Notas da Entrevista:\n");
    for (int i = 0; i < 3; i++) {
    printf("Nota %d: %.2f (Endereço: %p)\n", i, candidatos[0].entrevistabanca[i], (void*)&candidatos[0].entrevistabanca[i]);
}

    return 0;
}