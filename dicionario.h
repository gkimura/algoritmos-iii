#ifndef _dicionario_h
#define _dicionario_h

#include <stdio.h>
#include <stdlib.h>

#define false (1 == 0)
#define true !false
#define MAX 30 // numero maximo de caracteres das palavras

typedef struct no *ApNo;
typedef struct no{
	int altura;
	int valido;
	ApNo p[26];
	char palavra[MAX];
}No;

ApNo Cria_Raiz();
ApNo Cria_No (char palavra[],int altura,int tam_p);
void Converte_Minuscula (char palavra[]);
void Modifica_No (ApNo no,char palavra[],int tam_p);
int Insere_Palavra(ApNo p,char palavra[],int tam_p);
int Minimo (int primeiro,int segundo,int terceiro);
int Compara_Palavras (char palavra1[],int tam_1,char palavra2[],int tam_2);
void Imprime_Resposta(FILE *out,char palavra[]);
void Busca_Palavras(ApNo p,char palavra[],int distancia,int tam_p,FILE *out);
void Consulta_Dicionario(ApNo raiz,FILE *in,FILE *out);
void Destroi_Arv(ApNo p);
void Cria_Dicionario(ApNo raiz,FILE *dicionario);

#endif
