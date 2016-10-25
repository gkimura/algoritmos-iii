
#include "dicionario.h"

int main (){
	FILE *dicionario,*in,*out;
	dicionario = fopen("dicionario.txt","r");
	in = stdin; 
	out = stdout;
	
	if(!dicionario){
		fprintf(stderr,"Falha na abertura do arquivo dicionario.\n");
		exit(1);
	}
	if(!in){
		fprintf(stderr,"Falha na abertura do arquivo in.\n");
		exit(1);
	}
	if(!out){
		fprintf(stderr,"Falha na abertura do arquivo out.\n");
		exit(1);
	}
	ApNo raiz;
	raiz = Cria_Raiz();
	Cria_Dicionario(raiz,dicionario);
	Consulta_Dicionario(raiz,in,out);
	Destroi_Arv(raiz);
	
	return 0;
}
