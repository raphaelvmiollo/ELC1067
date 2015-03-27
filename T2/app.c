/*ll
Trabalho 2 de laboratório de programação 2.
Desenvolvido por: Raphael Vieira Miollo
matricula: 201220519
e-mail: rmiollo@inf.ufsm.br
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Estrutura que irá armazenar os dados dos alunos
typedef struct {
	int matricula;
	char nome[50];
} aluno;

//Estrutura que irá armazenar a matricula e as notas dos alunos
typedef struct {
	int matricula;
	float nota1;
	float nota2;
}  nota;

//Protótipo da função calculaMedia
float calculaMedia(nota *vetor_nota, int notas_tam, int matricula);


int main(int argc, char *argv[]){

	FILE *notas, *alunos;
	char linha[100], *retorno, argumento[50] ="";
	int c, i = 0, registro_notas, n_alloc = 10, n_linhas_nota = 0, n_linhas_aluno = 0;
	nota *vetor_nota ;
	aluno item_aluno;

	//Verifica se o número de parametros passados estão corretos
	if (argc < 2){
		fprintf(stderr, "Você deve informar o nome do aluno que deseja calcular a media. Para nomes compostos utilize entre ASPAS\n");
		return 1;
	}

	//Abre o arquivo de notas 
	notas = fopen("notas.txt", "r");
	if(notas == NULL){
		fprintf(stderr, "Arquivo de notas não está acessivel \n");
		return 1;
	}


	vetor_nota = (nota*) malloc (n_alloc * sizeof(nota));

	while(!feof(notas)){
		if(n_alloc == n_linhas_nota){
			n_alloc = n_alloc + (n_alloc * 2);
			vetor_nota = (nota*) realloc (vetor_nota, n_alloc *(sizeof(nota)));	
		}
		fgets(linha, 100,  notas);
		sscanf(linha, "%d %f %f",&vetor_nota[n_linhas_nota].matricula, &vetor_nota[n_linhas_nota].nota1, &vetor_nota[n_linhas_nota].nota2 );
		n_linhas_nota++;		
	}
	if(n_alloc > n_linhas_nota) {
		vetor_nota = (nota*) realloc(vetor_nota, n_linhas_nota *(sizeof(nota)));
	}
	//Fecha o arquivo de notas
	fclose(notas);

	alunos = fopen("alunos.txt", "r");
	if(alunos == NULL){
		fprintf(stderr, "Arquivo de alunos não está acessivel \n");
		free(notas);
		return 1;
	}
	//Abre o arquivo de alunos e verifica se o arquivo foi aberto corretamente
	alunos = fopen("alunos.txt", "r");
	if(alunos == NULL){
		fprintf(stderr, "Arquivo de alunos não está acessivel! \n" );
		free(notas)
		return 1;
	}

	
	//Escaneia linha por linha do arquivo de alunos, copia a matricula e o nome, verifica se o nome contem o argumento passado. Se contem o argumento passado ele calcula a média e exibe na tela.
	fseek(alunos, 0, SEEK_SET);  //Retorna ao inicio do arquivo
	while(fgets(linha, 100, alunos)){
		sscanf(linha ,"%d %[^\n]s", &item_aluno.matricula, &item_aluno.nome);  //Na compilação ele mostra um aviso que espera um ponteiro!
		retorno = strstr(item_aluno.nome, argv[1]);
		if(retorno != NULL){
			printf("%f %s \n", calculaMedia(vetor_nota, n_linhas_nota, item_aluno.matricula), item_aluno.nome);
		}
	}
	free(notas);
	fclose(alunos);

	return 0;


}




//Função recebe uma matricula e retorna a media
float calculaMedia(nota *vetor_nota, int notas_tam, int matricula){
	int i = 0;
	float media = 0;
	//printf("%d\n%d\n",notas_tam, matricula );
	for (i = 0; i < notas_tam; i++)	{
	//	printf("%d\n", vetor_nota[i].matricula );
		if(vetor_nota[i].matricula == matricula){
			media = vetor_nota[i].nota1 + vetor_nota[i].nota2;
			media = media/2;
		}	
	}
	return media;
}


