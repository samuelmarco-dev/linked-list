#include <stdlib.h>
#include <stdio.h>

/*
 Lista simplesmente encadeada com cabeça
 A lista é um nó vazio
*/

typedef struct NodeList {
  int info;
  struct NodeList *prox;
} node;

node *newList();
node *addNode(node *list, int value);
node *findNode(node *list, int value);
void delNode(node *n, int value);
int isEmpty(node *list);
int length(node *list);
void showList(node *list);

int main(){
  node *l1;
  l1 = newList();
  showList(l1);
  addNode(l1, 1);
  showList(l1);
  addNode(l1, 2);
  showList(l1);
  addNode(l1, 3);
  showList(l1);
  delNode(l1, 2);
  showList(l1);
  delNode(l1, 12);
  showList(l1);
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
