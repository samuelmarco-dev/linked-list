#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

/*
    0. Criar a lista e inicializar suas referências de ponteiros
    1. inserir no início/meio/fim, inserir por índice
    2. remover no início/meio/fim, remover por índice
    3. buscar no início/meio/fim, buscar por índice, buscar por valor
    3. retornar o tamanho de uma lista e a quantidade de elementos
*/

typedef struct nodeItem { //um nó onde cada nó é "filho" do nó criado anteriormente
    int info;
    struct nodeItem *prox;
} node;

typedef struct {
    node *first; //podemos guardar outros campos, como: meio, final, entre outros
} list;

list *newList();
node *newNode(int valor);

void showList(list *l);
int length(list *l);
int isLinkedListEmpty(list *l);
int posicaoInvalida(int pos, list *l);

node *inserirInicio(list *l, int valor);
void inserirPosicao(list *l, int valor, int pos);

int buscar(list *l, int valor);
node *buscaPosicao(list *l, int pos);

int excluirInicio(list *l);
void excluiPosicao(list *l, int pos);
void excluiValor(list *l, int valor);

int main() {
    setlocale(LC_ALL, "");

    list *l = newList();
    showList(l);
    inserirInicio(l, 5);
    inserirInicio(l, 10);
    inserirInicio(l, 15);
    inserirInicio(l, 20);
    showList(l);
    printf("Tamanho da lista: %d\n", length(l));

    int index = buscar(l, 5);
    if(index) {
        printf("Valor encontrado na posição: %d\n", index);
    } else {
        printf("Valor não encontrado!\n");
    }
    printf("\n");

    return 0;
}

list *newList() {
    list *l = (list *)malloc(sizeof(list));
    l->first = NULL;

    return l;
}

node *newNode(int valor) {
    node *n = (node *)malloc(sizeof(node));
    n->info = valor;
    n->prox = NULL;

    return n;
}

node *inserirInicio(list *l, int valor) {
    node *n = newNode(valor);
    n->prox = l->first;
    l->first = n;

    return n;
}

//Para uma posição inexistente, onde anterior recebe NULL, o elemento não será inserido na lista
void inserirPosicao(list *l, int valor, int pos) {
    int i;
    node *n, *ant;

    //utilizando posições exatas e não via "indexização"
    if(posicaoInvalida(pos, l)) return;
    if(pos == 1) inserirInicio(l, valor);
    else {
        n = newNode(valor);
        ant = l->first;

        //ant = buscaPosicao(l, pos-1)
        for(i=1; i<pos-1; i++) {
            ant = ant->prox;
        }
        n->prox = ant->prox;
        ant->prox = n;
    }
}

void showList(list *l) {
    node *n = l->first;

    if(isLinkedListEmpty(l)) {
       printf("List underflow!\n");
    } else {
        printf("List: \n-> ");
        while(n != NULL) {
            printf("%d ", n->info);
            n = n->prox;
        }
        printf("\n");
    }
}

int length(list *l) {
    int count = 0;
    node *n;
    n = l->first;

    while(n != NULL) {
        count++;
        n = n->prox;
    }

    return count;
}

int posicaoInvalida(int pos, list *l) {
    return pos < 1 || pos > (length(l) + 1);
}

int buscar(list *l, int valor) {
    node *n = l->first;
    int pos = 0;

    while(n != NULL) {
        pos++;
        if(n->info == valor) return pos;
        n = n->prox;
    }

    return -1;
}

node *buscaPosicao(list *l, int pos) {
    node *n = l->first;

    if(posicaoInvalida(pos, l)) {
        return NULL;
    }

    while(pos > 1) {
        n = n->prox;
        pos--;
    }
    return n;
}

int excluirInicio(list *l) {
    node *n;
    int aux;

    if(isLinkedListEmpty(l)) {
        exit(1);
    }
    n = l->first;
    aux = n->info;
    l->first = n->prox;

    free(n);
    return aux;
}

void excluiPosicao(list *l, int pos) {
    if(pos == 1) excluirInicio(l);

    node *ant, *n;
    ant = buscaPosicao(l, pos);

    if(ant == NULL) return;

    n = ant->prox;
    if(n != NULL) {
        ant->prox = n->prox;
        free(n);
    }
}

void excluiValor(list *l, int valor) {
    int pos = buscar(l, valor);

    while(pos > 0) {
        excluiPosicao(l, pos);
        pos = buscar(l, valor);
    }
}

int isLinkedListEmpty(list *l) {
    return l->first == NULL;
}
