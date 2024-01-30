#include <stdlib.h>
#include <stdio.h>

/*
   Lista simplesmente encadeada com cabeça
   Insere os elementos de modo ordenado na lista
*/

typedef struct NodeList {
  int info;
  struct NodeList *prox;
} node;

node *newList();
node *addNode(node *list, int value);
node *addSortedNode(node *list, int value);
node *findNode(node *list, int value);
void delNode(node *n, int value);
int isEmpty(node *list);
int length(node *list);
void showList(node *list);

int main(){
  int op = 1, aux;
  node *l1;
  l1 = newList();
  while(op != 0) {
    printf("Opcoes:\n 1 - Inserir\n 2 - Remover\n 3 - Listar\n 0 - Sair\n");
    scanf("%d", &op);
    switch (op) {
      case 1:
        printf("Informe o numero a ser inserido: ");
        scanf("%d", &aux);
        addSortedNode(l1, aux);
        printf("\nValor %d inserido com sucesso!\n", aux);
        break;
      case 2:
        printf("Informe o numero a ser removido: ");
        scanf("%d", &aux);
        if (findNode(l1, aux) == NULL) {
          printf("\nValor %d nao foi encontrado\n", aux);
        } else {
          delNode(l1, aux);
          printf("\nValor %d removido com sucesso!\n", aux);
        }
        break;
      case 3:
        showList(l1);
        printf("\nDigite 1 para prosseguir ");
        scanf("%d", &aux);
        break;
    }
  }
}

node *newList() {
  node *n = (node *)malloc(sizeof(node));
  n->prox = NULL;
  return n;
}

node *addNode(node *list, int value) {
  node *n = (node *)malloc(sizeof(node));
  n->info = value;
  n->prox = list->prox;
  list->prox = n;
  return n;
}

node *addSortedNode(node *list, int value) {
  node *ant;

  ant = list;
  list = list->prox;
  while(list != NULL && list->info < value) {
    ant = list;
    list = list->prox;
  }

  return addNode(ant, value);
}

node *findNode(node *list, int value) {
  list = list->prox;
  while(list != NULL && list->info != value) {
    list = list->prox;
  }
  return list;
}

void delNode(node *list, int value) {
  node *n;
  n = findNode(list, value);
  if (n != NULL) {
    while(list->prox != n) {
      list = list->prox;
    }
    list->prox = n->prox;
    free(n);
  }
}

void showList(node *list) {
  if (isEmpty(list)) {
    printf("Lista vazia\n");
  } else {
    printf("Lista possui %d elemento(s): ", length(list));
    list = list->prox;
    while(list != NULL) {
      printf("%d, ", list->info);
      list = list->prox;
    }
    printf("\n");
  }
}

int length(node *list) {
  int t=0;
  while(list->prox != NULL) {
    list = list->prox;
    t++;
  }
  return t;
}

int isEmpty(node *list) {
  return list->prox == NULL;
}
