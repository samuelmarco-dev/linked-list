#include <stdlib.h>
#include <stdio.h>

/*
 Lista simplesmente encadeada sem cabeça
 Primeiro nó da lista é o primeiro elemento da lista
*/

typedef struct NodeList {
  int info;
  struct NodeList *prox;
} node;

node *newList();
node *addNode(node *list, int value);
node *findNode(node *list, int value);
node *delNode(node *list, int value);
int isEmpty(node *list);
int length(node *list);
void showList(node *list);

int main(){
  node *l1;
  l1 = newList();
  showList(l1);
  l1 = addNode(l1, 1);
  showList(l1);
  l1 = addNode(l1, 2);
  showList(l1);
  l1 = addNode(l1, 3);
  showList(l1);
  l1 = delNode(l1, 2);
  showList(l1);
  l1 = delNode(l1, 12);
  showList(l1);
}

node *newList() {
  return NULL;
}

node *addNode(node *list, int value) {
  node *n = (node *)malloc(sizeof(node));
  n->info = value;
  n->prox = list;
  return n;
}

node *findNode(node *list, int value) {
  while(list != NULL && list->info != value) {
    list = list->prox;
  }
  return list;
}

node *delNode(node *list, int value) {
  node *n, *head;
  head = list;
  n = findNode(list, value);
  if (n != NULL) {
    if (list == n) {
      head = n->prox;
    } else {
      while(list->prox != n) {
        list = list->prox;
      }
      list->prox = n->prox;
    }
    free(n);
  }
  return head;
}

void showList(node *list) {
  if (isEmpty(list)) {
    printf("Lista vazia\n");
  } else {
    printf("Lista possui %d elemento(s): ", length(list));
    while(list != NULL) {
      printf("%d, ", list->info);
      list = list->prox;
    }
    printf("\n");
  }
}

int length(node *list) {
  int t=0;
  while(list != NULL) {
    list = list->prox;
    t++;
  }
  return t;
}

int isEmpty(node *list) {
  return list == NULL;
}
