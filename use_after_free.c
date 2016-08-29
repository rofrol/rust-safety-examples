#include<stdlib.h>
#include<stdio.h>

void some_dump_function() {
    int *used_after_free = malloc(sizeof(int));
    free(used_after_free);
    printf("%d", *used_after_free);
}

int main() {
    some_dump_function();
    return 0;
}
