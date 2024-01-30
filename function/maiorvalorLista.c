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
