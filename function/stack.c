typedef struct {
    node *top;
} stack;

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
