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
