#include "ListaLigadaDInterface.h"
#include <stdio.h>
#include <stdlib.h>

void inicializarLista(LISTA* lista) {
  lista->inicio = NULL;
}

void exibirLista(LISTA* lista) {
  PONT end = lista->inicio;
  printf("Lista: \" ");
  while (end != NULL) {
    printf("%d ", end->reg.chave);
    end = end->prox;
  }
  printf("\"\n");
}

int tamanho(LISTA* lista) {
  PONT end = lista->inicio;
  int tam = 0;
  while (end != NULL) {
    tam++;
    end = end->prox;
  }
  return tam;
}

int tamanhoEmBytes(LISTA* lista) {
  return (tamanho(lista) * sizeof(ELEMENTO)) + sizeof(LISTA);
}

PONT buscaSequencial(LISTA* lista, TIPOCHAVE ch) {
  PONT pos = lista->inicio;
  while (pos != NULL) {
    if (pos->reg.chave == ch) return pos;
    pos = pos->prox;
  }
  return NULL;
}

PONT buscaSeqOrd(LISTA* lista, TIPOCHAVE ch) {
  PONT pos = lista->inicio;
  while (pos != NULL && pos->reg.chave < ch) pos = pos->prox;
  if (pos != NULL && pos->reg.chave == ch) return pos;
  return NULL;
}

PONT buscaSeqExc(LISTA* lista, TIPOCHAVE ch, PONT* ant){
  *ant = NULL;
	ELEMENTO* atual = lista->inicio;
	while((atual != NULL) && (atual->reg.chave < ch)){
		*ant = atual;
		atual = atual->prox;
	}
	if ((atual != NULL) && (atual->reg.chave == ch)) return atual;
	return NULL;
}

PONT confereExistencia(LISTA* lista, TIPOCHAVE ch) {
  PONT inserir = lista->inicio;
  while (inserir != NULL && inserir->reg.chave < ch) {
    inserir = inserir->prox;
  }
  if (inserir != NULL && inserir->reg.chave == ch) return inserir;
  return NULL;
}

bool excluirElemLista(LISTA* lista, TIPOCHAVE ch) {
  PONT ant, excluir;
  excluir = buscaSeqExc(lista, ch, &ant);
  if (excluir == NULL) return false; // nao encontrou o elemento a excluir

  // caso o elemento excluido seja o primeiro da lista:
  if (ant == NULL) {
    lista->inicio = excluir->prox; 
    excluir->prox->ant = NULL; // acerta o ponteiro anterior do elemento seguinte
  }

  // caso o elemento excluido seja o último da lista:
  else if (excluir->prox == NULL){
    ant->prox = excluir->prox;
  }

  // caso esteja entre dois elementos:
  else {
    ant->prox = excluir->prox;
    PONT seguinte = excluir->prox;
    seguinte->ant = excluir->ant;
  }
  free(excluir);
  return true;
}

void reinicializarLista(LISTA* lista) {
  PONT end = lista->inicio;
  while (end != NULL) {
    PONT apagar = end;
    end = end->prox;
    free(apagar);
  }
  lista->inicio = NULL;
}

bool inserirElemListaOrd(LISTA* lista, REGISTRO reg) {
  TIPOCHAVE ch = reg.chave;
  PONT inserir, anterior;
  inserir = buscaSeqExc(lista, ch, &anterior);
  if (inserir != NULL) return false;
  inserir = (PONT)malloc(sizeof(ELEMENTO));
  inserir->reg = reg;

  // caso a lista esteja vazia:
  if (lista->inicio == NULL){
    inserir->prox = NULL;
    inserir->ant = NULL;
    lista->inicio = inserir;
  }
  
  // caso formos inserir o elemento na primeira posição:
  else if (anterior == NULL){
    inserir->ant = anterior;
    inserir->prox = lista->inicio;
    lista->inicio = inserir;
  }
  // caso formos inserir o elemento na última posição:
  else if (anterior->prox == NULL){
    inserir->ant = anterior;
    inserir->prox = anterior->prox; // que, no caso, seria null
    anterior->prox = inserir;
  } // não há elemento seguinte para arrumar o ponteiro

  // outros casos:
  else{
    inserir->ant = anterior;
    inserir->prox = anterior->prox;
    PONT seguinte = anterior->prox;
    seguinte->ant = inserir; // arruma o anterior do elemento seguinte ao inserido
    anterior->prox = inserir; // arruma o proximo do anterior
  }
  return true;
}

PONT retornarPrimeiro(LISTA* lista, TIPOCHAVE *ch) {
  if (lista->inicio != NULL) *ch = lista->inicio->reg.chave;
  return lista->inicio;
}

PONT retornarUltimo(LISTA* lista, TIPOCHAVE *ch) {
  PONT ultimo = lista->inicio;
  if (lista->inicio == NULL) return NULL;
  while (ultimo->prox != NULL) ultimo = ultimo->prox;
  *ch = ultimo->reg.chave;
  return ultimo;
}
