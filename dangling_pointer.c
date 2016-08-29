#include<stdlib.h>
#include<stdio.h>

int *another_dump_function() {
    int a_local_variable;
    return &a_local_variable;
}

void implicitly_dump_function() {
    int *raw_pointer = another_dump_function();
    *raw_pointer = 1234;
}

int main() {
    implicitly_dump_function();
    return 0;
}
