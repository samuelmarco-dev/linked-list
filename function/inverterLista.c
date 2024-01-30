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
}
