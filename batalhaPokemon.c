//  Projeto 2 - Algoritmo e Estruturas de Dados.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sPokemon{
	char nome [30];
	int tipo;
}Elemento;

typedef struct sCelula{
	Elemento info;
	struct sCelula * prox;
	struct sCelula * ante;
}Celula;

typedef struct sDeque{
	Celula * inicio;
	Celula * fim;
	int qnt;	
}Deque;

void inicializar(Deque * deque){
	deque->inicio = NULL;
	deque->fim = NULL;
	deque->qnt = 0;
}

int vazia(Deque **deque){
	if((*deque)->inicio == NULL && (*deque)->fim == NULL)
		return 1;
	return 0;
}

Celula * criarCelula(){
	return (Celula*)malloc(sizeof(Celula));
}

Elemento criarElemento(char nome[], int tipo){
	Elemento e;
	strcmp(e.nome,nome);
	e.tipo = tipo;
	return e;
}

void msg(){
	printf("\nTipo:");
	printf("\n1 - ar");
	printf("\n2 - fogo");
	printf("\n3 - agua");
	printf("\n4 - terrestre");
	printf("\n5 - outros");
	printf("\nOpcao: ");
}

int inserirNoInicio(Deque **deque, Elemento novo){
	Celula *novacelula = criarCelula();
	novacelula->info = novo;
	novacelula->ante = NULL;
	novacelula->prox = NULL;
	
	if(vazia(deque)){
		(*deque)->qnt = 1;
		(*deque)->inicio = novacelula;
		(*deque)->fim = novacelula;
		return 1;
	}
	
	(*deque)->qnt = (*deque)->qnt + 1;
	novacelula->prox = (*deque)->inicio;
	(*deque)->inicio->ante = novacelula;
	(*deque)->inicio = novacelula;
	return 1;
}

int inserirNoFim(Deque **deque, Elemento novo){
	Celula *novacelula = criarCelula();
	novacelula->info = novo;
	novacelula->ante = NULL;
	novacelula->prox = NULL;
	
	if(vazia(deque)){
		return inserirNoInicio(deque,novo);
	}
	
	(*deque)->qnt = (*deque)->qnt + 1;
	novacelula->ante = (*deque)->fim;
	(*deque)->fim->prox = novacelula;
	(*deque)->fim = novacelula;
	return 1;
}

Elemento removerNoInicio(Deque **deque){
	Elemento removido = criarElemento("",0);
	Celula *removida;
	
	if(vazia(deque)){
		printf("\nDeque Vazio");
		return removido;
	}
	
	removida = (*deque)->inicio;
	removido = removida->info;
	
	if((*deque)->fim == (*deque)->inicio){
		inicializar(*deque);
		free(removida);
		return removido;
	}
	(*deque)->qnt = (*deque)->qnt - 1;
	(*deque)->inicio = removida->prox;
	(*deque)->inicio->ante = NULL;
	free(removida);
	return removido;
}

char * tipo(int n){
	switch (n){
		case 1:
			return "ar";
		break;
		case 2:
			return "fogo";
		break;
		case 3:
			return "agua";
		break;
		case 4:
			return "terrestre";
		break;
		case 5:
			return "outros";
		break;
	}
}

Elemento duelo(Deque **j1, Deque **j2){
	int ret;
	
	Elemento e1,e2, e;
	e = criarElemento("",0);
	e1 = removerNoInicio(j1);
	e2 = removerNoInicio(j2);
	
	if(e1.tipo == e2.tipo){
		return e;
	}
	
	switch (e1.tipo){
		case 1:
			if((e2.tipo == 3) || (e2.tipo == 4)){
				ret = inserirNoInicio(j1,e1);
				return e1;
			}else{
				ret = inserirNoInicio(j2,e2);
				return e2;
			}
		break;
		case 2:
			if((e2.tipo == 1) || (e2.tipo == 5)){
				ret = inserirNoInicio(j1,e1);
				return e1;
			}else{
				ret = inserirNoInicio(j2,e2);
				return e2;
			}
		break;
		case 3:
			if((e2.tipo == 2) || (e2.tipo == 5)){
				ret = inserirNoInicio(j1,e1);
				return e1;
			}else{
				ret = inserirNoInicio(j2,e2);
				return e2;
			}
		break;
		case 4:
			if((e2.tipo == 2) || (e2.tipo == 3)){
				ret = inserirNoInicio(j1,e1);
				return e1;
			}else{
				ret = inserirNoInicio(j2,e2);
				return e2;
			}
		break;
		case 5:
			if((e2.tipo == 1) || (e2.tipo == 4)){
				ret = inserirNoInicio(j1,e1);
				return e1;
			}else{
				ret = inserirNoInicio(j2,e2);
				return e2;
			}
		break;
	}
	
}

int batalhar(Deque **j1, Deque **j2){
	int i = 0;
	char n;
	Elemento e;
	
	do{
		
		printf("\nJogador 1: %d pokemons restantes", (*j1)->qnt);
		printf("\nJogador 2: %d pokemons restantes", (*j2)->qnt);
		i++;
		printf("\n\n=== Combate %d ===",i);	
		printf("\n%s, tipo: %s",(*j1)->inicio->info.nome,tipo((*j1)->inicio->info.tipo));
		printf("\n--- VS ---");
		printf("\n%s, tipo: %s",(*j2)->inicio->info.nome,tipo((*j2)->inicio->info.tipo));
		printf("\n\nDigite . e depois ENTER para continuar: ");
		scanf("%c", &n);
		fflush(stdin);
		e = duelo(j1,j2);
		if(e.tipo == 0){
			printf("\nEmpate. Os dois pokemons foram eliminados.");
		}else{
			printf("\nVencedor: ");	
			printf("\n%s, tipo: %s",e.nome,tipo(e.tipo));
		}
		
		printf("\n\nDigite . e depois ENTER para continuar: ");
		scanf("%c", &n);
		fflush(stdin);
		
	}while(((*j1)->qnt != 0) && ((*j2)->qnt != 0));
	
	if(((*j1)->qnt == 0) && ((*j2)->qnt == 0)){
		return 0;
	}
	if((*j1)->qnt == 0){
		return 2;
	}
	if((*j2)->qnt == 0){
		return 1;
	}
}

void menu(Deque *jogador1, Deque *jogador2){
	Elemento e;
	int qnt,i = 0, ret;
	
	do{
		printf("\nQuantos pokemons para cada jogador?: ");
		scanf("%d", &qnt);
		fflush(stdin);
	}while(qnt < 1);
	
	printf("\nPokemons do jogador 1: ");
	for(i = 0; i <qnt; i++){
		
		printf("\nNome do pokemon: ");
		scanf("%s",e.nome);
		fflush(stdin);
		do{
			msg();
			scanf("%d", &e.tipo);
			fflush(stdin);	
			
			if(e.tipo < 1 || e.tipo > 5){
				printf("\nOpcao invalida.");
			}
				
		}while(e.tipo < 1 || e.tipo > 5);
		
		ret = inserirNoFim(&jogador1,e);
	}
	printf("\nPokemons do jogador 2: ");
	for(i = 0; i <qnt; i++){
		printf("\nNome do pokemon: ");
		scanf("%s",e.nome);
		fflush(stdin);
		
		do{
			msg();
			scanf("%d", &e.tipo);
			fflush(stdin);	
			
			if(e.tipo < 1 || e.tipo > 5){
				printf("\nOpcao invalida.");
			}
				
		}while(e.tipo < 1 || e.tipo > 5);
		
		ret = inserirNoFim(&jogador2,e);	
	}
	
	ret = batalhar(&jogador1,&jogador2);
	
	printf("\n*** PLACAR FINAL ***");
	if(ret == 0){
		printf("\nEmpate. Os 2 jogaram bem.");
	}
	if(ret == 1){
		printf("\nJogador 1 venceu com %d pokemons. ",jogador1->qnt);
	}
	if(ret == 2){
		printf("\nJogador 2 venceu com %d pokemons. ",jogador2->qnt);
	}
}

int main(){
	Deque jogador1,jogador2;
	char n;
	inicializar(&jogador1);
	inicializar(&jogador2);
	
	menu(&jogador1,&jogador2);
	printf("\nDigite . e depois ENTER para continuar: ");
	scanf("%c", &n);
		
	return 0;
}

