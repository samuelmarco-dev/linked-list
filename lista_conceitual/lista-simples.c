#include <stdlib.h>
#include <stdio.h>

/*
Lista simplesmente encadeada utilizando uma estrutura própria
Codigo apresentado em sala
*/

typedef struct NodeItem {
  int info;
  struct NodeItem *prox;
} node;

typedef struct {
  node *first;
} list;

list *newList();
node *addNode(list *l, int value);
node *findNode(list *l, int value);
void delNode(list *n, int value);
int isEmpty(list *l);
int length(list *l);
void showList(list *l);

int main(){
  list *l1;
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
  delNode(l1, 3);
  showList(l1);
  delNode(l1, 1);
  showList(l1);
}

list *newList() {
  list *l = (list *)malloc(sizeof(list));
  l->first = NULL;
  return l;
}

node *addNode(list *l, int value) {
  node *n = (node *)malloc(sizeof(node));
  n->info = value;
  n->prox = l->first;
  l->first = n;
  return n;
}

node *findNode(list *l, int value) {
  node *n = l->first;
  while(n != NULL && n->info != value) {
    n = n->prox;
  }
  return n;
}

void delNode(list *l, int value) {
  node *n, *ant;
  n = findNode(l, value);
  if (n != NULL) {
    if (n == l->first) {
      l->first = n->prox;
    } else {
      ant  = l->first;
      while(ant->prox != n) {
        ant = ant->prox;
      }
      ant->prox = n->prox;
    }
    free(n);
  }
}

void showList(list *l) {
  node *n;
  if (isEmpty(l)) {
    printf("Lista vazia\n");
  } else {
    printf("Lista possui %d elemento(s): ", length(l));
    n = l->first;
    while(n != NULL) {
      printf("%d, ", n->info);
      n = n->prox;
    }
    printf("\n");
  }
}

int length(list *l) {
  int t=0;
  node *n = l->first;
  while(n != NULL) {
    n = n->prox;
    t++;
  }
  return t;
}

int isEmpty(list *l) {
  return l->first == NULL;
}
