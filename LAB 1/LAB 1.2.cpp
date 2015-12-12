/*Fa�a uma fun��o em C que receba como par�metros Vi e Vf. L (vari�vel global) 
indica a posi��o do primeiro n� de uma lista encadeada, com o campo info do 
tipo inteiro e n�s ordenados em ordem crescente pelo campo info (sem repeti��o). Vi 
e Vf s�o dois n�meros inteiros, sendo Vi < Vf. A fun��o dever� eliminar da lista os n�s 
cujos valores do campo info estejam compreendidos entre Vi e Vf (inclusive eles). 
Assuma que os valores de Vi e Vf est�o contidos em L, e que Vi n�o � o primeiro n� e 
Vf n�o � o �ltimo n� da lista*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
const int TAM = 10;

struct LISTA
{	int info;
	struct LISTA *prox;
};
typedef struct LISTA LISTA;
LISTA *L;

void inicializar();
void exibir();
int valor_final();
int valor_inicial(int Vf);
void busca(int info, LISTA **aux, LISTA **auxAnt);
void remove(int Vi, int Vf);

int main()
{
	inicializar();
	exibir();
	int Vf = valor_final();
	int Vi = valor_inicial(Vf);
	remove(Vi, Vf);
	exibir();
	
	getch();
	return 0;
}

void inicializar()
{	int idx = TAM;
   	LISTA *novo, *aux;

    aux = NULL;

    do { //preenche todos os 10 elementos da lista dinamica com os valores de 10 a 1
        novo = (LISTA*) malloc(sizeof(LISTA));
        novo->info = idx;
        novo->prox = aux;
        aux = novo;
        idx--;
    } while (idx > 0);

    L = aux; //faz o L apontar para o primeiro elemento da lista existente
}

void exibir()
{	LISTA *i;
	for (i = L; i != NULL; i = i->prox) //i = L; //i aponta para o primeiro elemento da lista
		printf(" %d ", i->info);
}

int valor_final()
{	int Vf;
	printf("\n\nDigite o valor final (Vf): ");
	scanf("%d", &Vf);
	fflush(stdin);
	return Vf;
}

int valor_inicial(int Vf)
{	int Vi;
	printf("Digite o valor inicial (Vi): ");
	scanf("%d", &Vi);
	fflush(stdin);
	while (Vi>=Vf)
	{	printf("\nErro! Digite o valor inicial (Vi) novamente: ");
		scanf("%d", &Vi);
		fflush(stdin);
	}
	printf("\n\n");
	return Vi;
}

void busca(int info, LISTA **aux, LISTA **auxAnt) 
{
    *aux = L;
    *auxAnt = NULL;

    while(*aux != NULL) {
        if ((*aux)->info == info) {
            return;
        }

        *auxAnt = *aux;
        *aux = (*aux)->prox;
    }

    return;
}

void remove(int Vi, int Vf) 
{
    LISTA *VI, *VIAnt, *VF, *VFAnt, *aux;

    busca(Vi, &VI, &VIAnt);
    busca(Vf, &VF, &VFAnt);

    VIAnt->prox = VF->prox;
    VF->prox = NULL;

    aux = VI;

    while (aux != NULL) 
	{
        VI = aux;
        aux = aux->prox;
        free(VI);
    }
}
