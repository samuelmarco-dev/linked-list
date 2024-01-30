void insertElementAscendingOrder(list *l, int value) {
    node *n = newNode(value);
    node *previous = l->first;
    node *limit;

    if(isLinkedListEmpty(l)) {
        insertElementAtStart(l, n);
        return;
    }

    if(previous->info >= value) {
        n->next = previous;
        l->first = n;
    } else {
        limit = limitValue(l, value);
        n->next = limit->next;
        limit->next = n;
    }
}

node *limitValue(list *l, int value) {
    node *n = l->first;

    if(isLinkedListEmpty(l)) {
        printf("Cannot find the value in an empty list!\n");
        exit(1);
    }

    while(n != NULL) {
        if(n->info >= value && value < n->next->info) return n;
        n = n->next;
    }

    return n;
}
