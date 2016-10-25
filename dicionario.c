
#include "dicionario.h"

ApNo Cria_Raiz(){
	int i;
	ApNo aux;
	aux = malloc(sizeof(No));
	aux->altura = 0; //nodo raiz, altura 0
	aux->valido = false;
	for (i = 0; i <= 25;i++) 
		aux->p[i] = NULL;
	return aux;
}

//cria um nó, em caso de palavra completa atualiza bit validade, e insere a palavra no nodo
ApNo Cria_No (char palavra[],int altura,int tam_p){
	ApNo aux;
	int i;
	aux = malloc(sizeof(No));
	aux->altura = altura;
	if (tam_p == aux->altura){
		for (i = 0;i < tam_p;i++)
			aux->palavra[i] = palavra[i];

		palavra[i] = '\0';
		aux->valido = true;
	}else 
		aux->valido = false;

	for (i = 0; i <= 25;i++)
		aux->p[i] = NULL;

	return aux;
}
// converte todas as letras maiusculas da palavra em minuscula
void Converte_Minuscula (char palavra[]){
	int i;
	for (i = 0;palavra[i] != '\0';i++)
		if ((palavra[i] >= 'A') && (palavra[i] <= 'Z'))
			palavra[i] = palavra[i]+32;
}
// modifica nodo, insere uma palavra valida em um no existente
void Modifica_No (ApNo no,char palavra[],int tam_p){
	int i;
	if (tam_p == no->altura){
		for (i = 0;i < tam_p;i++)
			no->palavra[i] = palavra[i];
		no->palavra[i] = '\0';
		no->valido = true;
	}
}

int Insere_Palavra(ApNo p,char palavra[],int tam_p){
	ApNo aux = p;
	int Notfound;
	int letra_da_vez; // char da vez para verificacao
	int ponteiro_i;    // indicador do ponteiro
	int i; // comparador ascii da letra da vez;

	if (tam_p > (MAX-1)) return -1; //erro: palavra maior que MAX caracteres
	for (letra_da_vez = 0;letra_da_vez < tam_p;letra_da_vez++){
		i = 'a';
		ponteiro_i = 0;
		Notfound = true;// bolleana, se n achou a letra da vez continua procurando
		while ((Notfound) && (i <= 'z')){
			if (palavra[letra_da_vez] == i){
				Notfound = false;
				//encontrou, se o ponteiro da letra nao existir, cria nodo senao verifica se eh final de palavra
				if (aux->p[ponteiro_i] == NULL){	
					aux->p[ponteiro_i] = Cria_No(palavra,aux->altura+1,tam_p);
				}else{
					Modifica_No(aux->p[ponteiro_i],palavra,tam_p);
				}
			}
			i++;
			ponteiro_i++;
		}
		if (Notfound) return -2; //Erro: letra nao consta no alfabeto
		aux = aux->p[ponteiro_i-1];
	}
	return 0;
}

int Minimo (int primeiro,int segundo,int terceiro){
	if (primeiro < segundo){
		if (primeiro < terceiro)
			return (primeiro);
	}else
		 if (segundo < terceiro)
			return (segundo);
	return (terceiro);
	
	
}


int Compara_Palavras (char palavra1[],int tam_1,char palavra2[],int tam_2){
	int i,j,cont;
	int matriz[tam_1+1][tam_2+1];
	for (i = 0;i <= tam_1;i++)
		for (j = 0;j <= tam_2;j++)
			matriz[i][j] = 0; //zera matriz

	for (i = 1;i <= tam_1;i++)
		matriz[i][0] = i; //insere na primeira coluna, a primeira palavra
	
	for (j = 1;j <= tam_2;j++)
		matriz[0][j] = j; //insere na primeira linha, a segunda palavra comparada
	
	for (i = 1;i <= tam_1;i++){
		for (j = 1;j <= tam_2;j++){
			if (palavra1[i-1] == palavra2[j-1])
				cont = 0;
			else
				cont = 1;

			matriz[i][j] = Minimo (matriz[i-1][j] +1,   // removendo letra
					matriz[i][j-1] + 1,  // adicionando letra
					matriz[i-1][j-1] + cont);// substituindo
		}
	}
	return (matriz[tam_1][tam_2]);
}

void Imprime_Resposta(FILE *out,char palavra[]){
	int i;
	for (i = 0;palavra[i] != '\0';i++)
		fprintf(out,"%c",palavra[i]);
}


//passa pelos nodos, procurando os validos(palavras completas) e entao, compara
void Busca_Palavras(ApNo p,char palavra[],int distancia,int tam_p,FILE *out){
	int i;   // contador para o ponteiro
   	int cont_er; //contador de erros
	if (p == NULL) return;
	for (i = 0;i <= 25;i++) 
		Busca_Palavras(p->p[i],palavra,distancia,tam_p,out);
	if (p->valido == true){
		cont_er = Compara_Palavras(palavra,tam_p,p->palavra,p->altura);
		if (cont_er <= distancia){
			Imprime_Resposta(out,p->palavra);
			fprintf(out," ");
		}
	}
}

//Pega palavras do arquivo de entrada, seu valor de distancia, e procura no dicionario
void Consulta_Dicionario(ApNo raiz,FILE *in,FILE *out){
	int i,distancia;
	char c,palavra[MAX];
	c = fgetc(in);
	while (c != EOF){
		i = 0;
		while(c != ' '){
			palavra[i] = c;
			i++;
			c = fgetc(in);
		}
		palavra[i] = '\0';
		distancia = fgetc(in) - '0'; // pega valor de distancia
		c = fgetc(in); // pega o \n

		Imprime_Resposta(out,palavra);
		fprintf(out,": ");

		Converte_Minuscula(palavra);
		Busca_Palavras(raiz,palavra,distancia,i,out);

		fprintf(out,"\n");
		c = fgetc(in);
	}
}

//desaloca os nodos recursivamente
void Destroi_Arv(ApNo p){
	int i;
	if (p == NULL) return;
	for (i = 0;i <= 25;i++)
		Destroi_Arv(p->p[i]);
	free(p);
	return;
	 
}

//Pega palavras do arquivo dicionario, e insere na árvore
void Cria_Dicionario(ApNo raiz,FILE *dicionario){
	int i,check;
	char c,palavra[MAX];
	c = fgetc(dicionario);
	while (c != EOF){
		i = 0;
		while ((c != '\n') && (c != EOF)){
			palavra[i] = c;
			i++;
			c = fgetc(dicionario);
		}
		palavra[i] = '\0';
		Converte_Minuscula(palavra);
		check = Insere_Palavra(raiz,palavra,i);
		if(check==-1){
			fprintf(stderr,"Erro: palavra ultrapassa numero de letras maxima.\n");
			exit(1);
		}else if(check==-2){
			fprintf(stderr,"Erro: palavra contem caracter invalido.\n");
			exit(1);		
		}
		c = fgetc(dicionario);
	}
}

