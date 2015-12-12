/*Utilizando �rvores bin�rias de busca (ABB), implemente em C um programa que possua as seguintes fun��es:
a) Constr�i uma ABB guardando em cada n� um valor do tipo inteiro. Os dados devem ser lidos (m�nimo de 10 n�s).
b) Determina o n�mero de n�s de uma �rvore (n�o � para contar na inser��o!).
c) Calcula a soma dos conte�dos de todos os n�s de uma �rvore (n�o � para somar na inser��o!).
d) Remove o n� que possuir o menor valor.
e) Imprime a �rvore na tela.
f) Remove a �rvore da mem�ria, ou seja, libera o espa�o ocupado em mem�ria por cada n� da �rvore.
A fun��o main dever� chamar adequadamente cada uma das fun��es. Ap�s cada fun��o, imprimir a �rvore na tela.*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define MIN 3

struct ARVORE
{
	int info;
	struct ARVORE *esq, *dir;
};
typedef struct ARVORE ARVORE;

//funcoes do item a
void inicializa(ARVORE **atual);
void insere(ARVORE **atual, int v);
//nao usa ponteiro de ponteiro pois nao altera o valor da estrutura
void num_nos(ARVORE *atual, int *num);//b
void soma_nos(ARVORE *atual, int *soma);//c
//funcoes do item d
void encontrar_menor(ARVORE *atual, int *menor);
void remover(ARVORE **atual, int elem);
void antecessor(ARVORE **aux, ARVORE **atual);
//exibir e liberar
void exibir(ARVORE *atual, int c);//e
void remove(ARVORE **atual);//f

int main()
{
	ARVORE *raiz;
	raiz = NULL;
	inicializa(&raiz);
	int num = 0;
	num_nos(raiz, &num); 
	printf("\n -> Numero de nos: %d", num);
	int soma = 0;
	soma_nos(raiz, &soma);
	printf("\n -> Soma dos nos: %d", soma);
	int menor = raiz->info;
	encontrar_menor(raiz, &menor);
	remover(&raiz, menor);
	printf("\n -> Menor valor (removido): %d", menor);
	printf("\n\nARVORE (com menor valor removido):\n\n");
	exibir(raiz, 0);
	printf("\nNos removidos! Arvore limpa...");
	getch();
	return 0;
}

void inicializa(ARVORE **atual)
{
	int cont = 0, v;
	printf("Digite no minimo %d cadastros (-1 para sair)\n\n", MIN);
	do
	{
		printf("Info: ");
		scanf("%d", &v);
		fflush(stdin);
		if (v != -1)
		{
			insere(atual, v);
			cont++;
		}
	} while (v != -1 || cont < MIN);
}

void insere(ARVORE **atual, int v)
{
	if(*atual == NULL)
	{
		*atual = (ARVORE *) malloc (sizeof(ARVORE));
		(*atual)->info = v;
		(*atual)->esq = NULL;
		(*atual)->dir = NULL;
	}
	else
	{
		if(v < (*atual)->info)
			insere(&(*atual)->esq, v);
		else
			insere(&(*atual)->dir, v);
	}
}

void num_nos(ARVORE *atual, int *num)
{
	if (atual) //se atual != NULL
	{	
		(*num)++;
		num_nos(atual->esq, num);
		num_nos(atual->dir, num);
	}
}

void soma_nos(ARVORE *atual, int *soma)
{
	if (atual)
	{
		(*soma) = (*soma) + atual->info;
		soma_nos(atual->dir, soma);
		soma_nos(atual->esq, soma);
	}
}

void encontrar_menor(ARVORE *atual, int *menor)
{
	if(atual)
	{
		if(atual->info < *menor)
			*menor = atual->info;
		encontrar_menor(atual->esq, menor);
		encontrar_menor(atual->dir, menor);
	}
}

void remover(ARVORE **atual, int elem)
{
	ARVORE *aux;
	if(*atual == NULL) //isso nao acontecer�
		printf(" Elemento nao esta na arvore!\n");
	else if(elem < (*atual)->info) /* procura � esquerda */
		remover(&(*atual)->esq, elem);
		else if(elem > (*atual)->info) /* procura � direita */
			remover(&(*atual)->dir, elem);
			else 
			{ /* achou */
				aux = *atual;
				
				if((*atual)->dir == NULL) 
					*atual = aux->esq; /* filho � esquerda */
				else if ((*atual)->esq == NULL) 
					*atual = aux->dir; /* filho � direita */
					else 
						antecessor(&aux, &(*atual)->esq); /* dois filhos */
						
				free(aux);
				//printf(" Remocao Feita!");
			}
}

void antecessor(ARVORE **aux, ARVORE **atual)
{
	if((*atual)->dir != NULL) 
		antecessor(aux, &(*atual)->dir);
	else 
	{
		(*aux)->info = (*atual)->info;
		*aux = *atual;
		*atual = (*atual)->esq; /*subarvore esquerda, se existir */
	}
}

void exibir(ARVORE *atual, int c)
{
	if(!atual)
		return;
		
	exibir(atual->dir, c+1);
	for(int i = 0; i < c; i++) 
		printf("  ");
	printf("%d\n", atual->info);
	exibir(atual->esq, c+1);
}

void remove(ARVORE **atual)
{
	if(*atual)
	{
		remove(&(*atual)->esq);
		remove(&(*atual)->dir);
		free(*atual);
	}
}
