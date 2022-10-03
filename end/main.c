#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define INDEX 0
#define LENGTH 10
#define NUMBER 5
#define LIMIT 100

typedef struct nodeItem {
    int info;
    struct nodeItem *next;
} node;

typedef struct {
    node *first;
} list;

typedef struct {
    node *top;
} stack;

list *newLinkedList();
node *newNode(int value);

void insertElementInList(list *l, int value, int index);
void insertElementAtStart(list *l, node *n);
void insertElementInMiddleOrEnd(list *l, node *n, int index);
void showList(list *l);

int searchElementByValue(list *l, int value);     //indexOf
node *searchElementByIndex(list *l, int index);  //getNode
void removeElementByValue(list *l, int value);  //delNodeValue
void removeElementByIndex(list *l, int index); //delNodePosition

int lengthOfList(list *l);
int isIndexInvalidInList(list *l, int index);
int isLinkedListEmpty(list *l);

int reduceList(list *l);
int highestValue(list *l);
void insertElementAscendingOrder(list *l, int value);

stack *newStack();
void push(stack *s, int value);
int pop(stack *s);
int isStackEmpty(stack *s);

void invertList(list *l, stack *s);
void sortList(list *l);

int main() {
    setlocale(LC_ALL, "");
    srand(time(NULL));

    list *l = newLinkedList();
    int i, indexOf, sum, high;
    int value = 1;

    for(i=0; i<NUMBER; i++) {
        insertElementInList(l, rand() % LIMIT, i);
    }
    insertElementInList(l, 1, NUMBER);
    printf("Length: %d\n", lengthOfList(l));
    showList(l);

    indexOf = searchElementByValue(l, value);
    if(indexOf) {
        printf("The value %d is at index %d\n", value, indexOf);
    } else {
      printf("Value %d not found in list!\n", value);
    }

    removeElementByValue(l, 1);
    removeElementByIndex(l, 3);
    printf("\nLength: %d\n", lengthOfList(l));
    showList(l);

    sum = reduceList(l);
    high = highestValue(l);
    printf("\nThe sum of nodes in the list is: %d\nThe highest value found in the list was: %d\n\n", sum, high);

    stack *s = newStack();
    invertList(l, s);

    printf("\n");
    list *inOrder = newLinkedList();
    insertElementAscendingOrder(inOrder, 5);
    insertElementAscendingOrder(inOrder, 2);
    insertElementAscendingOrder(inOrder, 4);
    insertElementAscendingOrder(inOrder, 9);
    insertElementAscendingOrder(inOrder, 1);
    insertElementAscendingOrder(inOrder, 20);
    showList(inOrder);

    printf("\n");
    list *aux = newLinkedList();
    for(i=0; i<NUMBER; i++) {
        insertElementInList(aux, rand() % LIMIT, i);
    }
    showList(aux);
    sortList(aux);

    return 0;
}

void insertElementAscendingOrder(list *l, int value) {
    node *n = newNode(value);
    node *previous = l->first;
    node *aux;

    if(isLinkedListEmpty(l) || previous->info >= value) {
        insertElementAtStart(l, n);
    }
    else {
        while(previous != NULL && previous->info <= value) {
            aux = previous->next;
            if(aux == NULL || aux->info > value) break;
            else previous = previous->next;
        }
        n->next = previous->next;
        previous->next = n;
    }
}

void sortList(list *l) {
    node *n = l->first;
    list *listAux = newLinkedList();

    if(isLinkedListEmpty(l)) {
        printf("Unable to sort an empty list!\n");
        return;
    }

    while(n != NULL){
        insertElementAscendingOrder(listAux, n->info);
        n = n->next;
    }

    l->first = listAux->first;
    listAux->first = NULL;
    free(listAux);

    showList(l);
}

//variação: reduceList(node *n);
int reduceList(list *l) {
    node *n = l->first;
    int sum = 0;

    if(isLinkedListEmpty(l)) return sum;

    while(n != NULL) {
        sum += n->info;
        n = n->next;
    }

    return sum;
}

int highestValue(list *l) {
    node *n = l->first;
    int high = n->info;

    if(isLinkedListEmpty(l)) {
        printf("Cannot find the largest value in an empty list!\n");
        exit(1);
    }

    while(n != NULL) {
        if(n->info > high) high = n->info;
        n = n->next;
    }

    return high;
}

void invertList(list *l, stack *s) {
    node *n = l->first;
    int i, remove;
    node *element;

    if(isLinkedListEmpty(l)) {
        printf("Cannot invert an empty list!\n");
        return;
    }

    for(i=0; i<lengthOfList(l); i++) {
        element = searchElementByIndex(l, i);
        push(s, element->info);
    }

    if(!isStackEmpty(s)) {
        printf("Linked list invert:\n-> ");
    }
    while(!isStackEmpty(s)) {
        remove = pop(s);
        printf("%d ", remove);
    }
    printf("\n");
}

list *newLinkedList() {
    list *l = (list *)malloc(sizeof(list));
    l->first = NULL;

    return l;
}

node *newNode(int value) {
    node *n = (node *)malloc(sizeof(node));
    n->info = value;
    n->next = NULL;

    return n;
}

void insertElementInList(list *l, int value, int index) {
    node *n = newNode(value);

    if(isIndexInvalidInList(l, index)) {
        printf("Index %d is not valid in linked list!\n", index);
        exit(1);
    }

    if(index == INDEX) insertElementAtStart(l, n);
    else insertElementInMiddleOrEnd(l, n, index);
}

void insertElementAtStart(list *l, node *n) {
    n->next = l->first;
    l->first = n;
}

void insertElementInMiddleOrEnd(list *l, node *n, int index) {
    int i;
    node *previous = l->first;
    //node *previous = searchElementByIndex(l, index-1);

    for(i=INDEX; i<index-1; i++) {
        previous = previous->next;
    }
    n->next = previous->next;
    previous->next = n;
}

void showList(list *l) {
    if(isLinkedListEmpty(l)) {
        printf("Unable to show elements of an empty list!\n");
        return;
    }

    node *n = l->first;
    printf("Linked List:\n-> ");

    while(n != NULL) {
        printf("%d ", n->info);
        n = n->next;
    }
    printf("\n");
}

int searchElementByValue(list *l, int value) {
    node *n = l->first;
    int position = INDEX;
    int error = -1;

    if(isLinkedListEmpty(l)) {
        printf("Value cannot be found in an empty list!\n");
        return error;
    }

    while(n != NULL) {
        if(n->info == value) return position;
        position++;
        n = n->next;
    }

    return error;
}

node *searchElementByIndex(list *l, int index) {
    node *n = l->first;

    if(index < INDEX || index >= lengthOfList(l)) {
        printf("Index %d cannot be found in the list!\n", index);
        return NULL;
    }

    while(index > INDEX) {
        n = n->next;
        index--;
    }

    return n;
}

void removeElementByValue(list *l, int value) {
    int position = searchElementByValue(l, value);

    if(isLinkedListEmpty(l)) exit(1);

    while(position != -1) {
        removeElementByIndex(l, position);
        position = searchElementByValue(l, value);
    }
}

void removeElementByIndex(list *l, int index) {
    node *previous, *n;
    previous = searchElementByIndex(l, index - 1);

    if(isLinkedListEmpty(l)) exit(1);
    if(previous == NULL) exit(1);

    n = previous->next;
    if(n != NULL) {
        previous->next = n->next;
        free(n);
    }
}

int lengthOfList(list *l) {
    int size = 0;
    node *n = l->first;

    while(n != NULL) {
        size++;
        n = n->next;
    }

    return size;
}

int isIndexInvalidInList(list *l, int index) {
    return index < INDEX || index > lengthOfList(l);
}

int isLinkedListEmpty(list *l) {
    return l->first == NULL;
}

stack *newStack() {
    stack *s = (stack *)malloc(sizeof(stack));
    s->top = NULL;

    return s;
}

void push(stack *s, int value) {
    node *n = newNode(value);
    n->next = s->top;
    s->top = n;
}

int pop(stack *s) {
    node *n = s->top;
    int aux;

    if(isStackEmpty(s)) {
        printf("The stack is currently empty. Try again!\n"); //Stack Underflow
        exit(1);
    }

    aux = n->info;
    s->top = n->next;
    free(n);

    return aux;
}

int isStackEmpty(stack *s) {
    return s->top == NULL;
}
