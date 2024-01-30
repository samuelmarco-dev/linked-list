void sortList(list *l) {
    stack *s = newStack();
    int high, i, remove;
    int length = lengthOfList(l);

    for(i=0; i<length; i++) {
        high = highestValue(l);
        push(s, high);
        removeElementByValue(l, high);
    }

    if(!isStackEmpty(s)) {
        printf("Linked list sorted:\n-> ");
    }
    while(!isStackEmpty(s)) {
       remove = pop(s);
       printf("%d ", remove);
    }
}
