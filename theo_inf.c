#include <stdio.h>
#include <stdlib.h> 

typedef struct State {
    char *name;
} State;

void new_state(char *name)
{
    State* test = (State*) malloc(sizeof(State));

    test->name = name;
    println(test->name);

    // return test;
}

void println(char *string) 
{
    printf("%s\n", string);
}

int main (int argc, char *argv[]) 
{
    new_state("testname");
}