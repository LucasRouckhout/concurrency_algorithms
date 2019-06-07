#include <stdlib.h>
#include <unistd.h>

#define N 5

int number = 0; // Assumed to be shared variables
int ticket[N]; 

void lock(const unsigned int, int*);
void unlock(const unsigned int);
