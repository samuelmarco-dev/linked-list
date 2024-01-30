#include <stdio.h>
#include <stdlib.h>

typedef struct nodeitem {
    int info;
    struct nodeitem *next;
} node;

typedef struct {
    node *first;
} linkedlist;

linkedlist *newList() {
    linkedlist *l = (linkedlist *)malloc(sizeof(linkedlist));
    l->first = NULL;
    return l;
}

int isListEmpty(linkedlist *l) {
    return l->first == NULL;
}

node *newNode(int value) {
    node *n = (node *)malloc(sizeof(node));
    n->info = value;
    n->next = NULL;
    return n;
}

int info(node *n) {
    return n->info;
}

int length(linkedlist *l) {
  int size = 0;
  node *n = l->first;
  while (n!=NULL) {
    size++;
    n = n->next;
  }
  return size;
}

int indexOf(linkedlist *l, int value) {
    int pos = 1;
    node *n = l->first;
    while(n != NULL) {
        if (n->info == value) {
            return pos;
        }
        pos++;
        n = n->next;
    }
    return -1;
}

node *getNode(linkedlist *l, int pos) {
    int i;
    node *n;

    if (pos < 1 || pos > length(l)) {
        return NULL;
    }

    n = l->first;
    for (i = 1; i<pos; i++) {
        n = n->next;
    }
    return n;
}

node *addFirstNode(linkedlist *l, int value) {
    node *n = newNode(value);
    n->next = l->first;
    l->first = n;
    return n;
}

node *addNextNode(node *prev, int value) {
    node *n = newNode(value);
    n->next = prev->next;
    prev->next = n;
    return n;
}

node *addNodePos(linkedlist *l, int value, int pos) {
    if (pos == 1) {
        return addFirstNode(l, value);
    } else {
        node *n = getNode(l, pos-1);
        if (n != NULL) {
            n = addNextNode(n, value);
        }
        return n;
    }
}

int delFirstNode(linkedlist *l) {
    int aux;
    node *n = l->first;
    if (n == NULL) {
        printf("A lista esta vazia!");
        exit(0);
    }
    l->first = n->next;
    aux = info(n);
    free(n);
    return aux;
}

int delNextNode(node *prev) {
    int aux;
    node *n = prev->next;
    if (n == NULL) {
        printf("O no a ser excluido nao existe!");
        exit(0);
    }
    prev->next = n->next;
    aux = info(n);
    free(n);
    return aux;
}

int delNodePos(linkedlist *l, int pos) {
    if (pos == 1) {
        return delFirstNode(l);
    } else {
        if (pos < 1 || pos > length(l)) {
            printf("Posicao invalida!");
            exit(0);
        }

        node *n = getNode(l, pos-1);
        return delNextNode(n);
    }
}

int delNodeValue(linkedlist *l, int value) {
    int pos = indexOf(l, value);
    if (pos == 1) {
        delFirstNode(l);
    } else if(pos > 0) {
        delNodePos(l, pos - 1);
    }
    return pos;
}

void showList(linkedlist *l) {
    node *n;
    n = l->first;

    if (isListEmpty(l)) {
        printf("Lista vazia!");
    } else {
        printf("Lista (%d): \n", length(l));
    }
    while (n!=NULL) {
        printf("%d, ", n->info);
        n = n->next;
    }
    printf("\n");
}


int main() {
    linkedlist *l = newList();
    addFirstNode(l, 10);
    addFirstNode(l, 5);
    addNextNode(addFirstNode(l, 7), 2);
    addNodePos(l, 9, 5);
    showList(l);
    printf("Busca: %d\n", info(getNode(l, 3)));
    printf("Posicao: %d\n", indexOf(l, 5));
    printf("Removendo o 3o elemento: %d\n", delNodePos(l, 3));
    printf("Removendo primeiro elemento: %d\n", delFirstNode(l));
    printf("Removendo o ultimo elemento: %d\n", delNextNode(getNode(l, length(l)-1)));
    printf("Removendo o valor 10: %d\n", delNodeValue(l, 10));

    showList(l);

}
