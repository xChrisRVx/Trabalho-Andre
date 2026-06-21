#include <stdio.h>
#include <string.h>
#define MAX 1000

int x=1000;

void ler_vetor(int cod[], char nome[][100], float nota1[], float nota2[], int *n)
{
    *n=0;
    while(scanf("%d,%99[^,],%f,%f", &cod[*n], nome[*n], &nota1[*n], &nota2[*n]) == 4)
    {
        (*n)++;
    }
}

void calc_media(int n, float nota1[], float nota2[], float media[], char result[][20])
{
    int i;
    for (i=0;i<n;i++)
    {
        media[i] = (nota1[i] + nota2[i]) / 2.0;

        if (media[i] >= 6.0 )
        {
            strcpy(result[i], "Aprovado");
        }
        else 
        {
            strcpy(result[i], "Reprovado");
        }
    }
}

void insert(int n, int cod[], char nome[][100], float media[], char result[][20])
{
    int i, j;

    int codAux;
    float mediaAux;
    char nomeAux[100], resultAux[100];

    for (i=1; i<n; i++) 
    {
        codAux = cod[i];
        mediaAux = media[i];

        strcpy(nomeAux, nome[i]);
        strcpy(resultAux, result[i]);

        j = i - 1;

        while (j >= 0 && media[j] < mediaAux)
        {
            cod[j + i] = cod[j];
            media[j + 1] = media[j];

            strcpy(nome[j + 1], nome[j]);
            strcpy(result[j + 1], result[j]);

            j--;
        }

        cod[j + 1] = codAux;
        media[j + 1] = mediaAux;

        strcpy(nome[j + 1], nomeAux);
        strcpy(result[j + 1], resultAux);
    }
}

void printSaida(FILE *saida, int cod[], float media[], char nome[][100], char result[][20], int n)
{
    int i;
    int limite=111;

    fprintf(saida, "Codigo/Nome/Media/Resultado\n");

    for (i=0;i<limite;i++)
    {
        fprintf(saida,"%d,%s,%.2f,%s\n", cod[i],nome[i],media[i],result[i]);
    }
}

int main() {

    FILE *saida;
    int cod[MAX], n;
    float nota1[MAX], nota2[MAX], media[MAX];
    char nome[MAX][100], result[MAX][20];

    ler_vetor(cod,nome,nota1,nota2,&n);

    calc_media(n,nota1,nota2,media,result);

    saida = fopen("saida.csv", "w");

    insert(n,cod,nome,media,result);

    printSaida(saida, cod, media, nome, result,n);

    fclose(saida);
    
    return 0;
}