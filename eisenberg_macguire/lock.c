#include <stdlib.h>
#include <unistd.h>
#include "lock.h"

#define INTERESTED -1
#define ACCESS 1
#define NOT_INTERESTED 0


int j = 0;
/*
 * Lock the thread until it gets access to the critical section using the Eisenberg Macguire 
 * algorithm.
 */
void lock(const unsigned int proc_id, unsigned int* turn, const unsigned int N, int* flag) {
  j = 0;
  while(j != N) {
    flag[proc_id] = INTERESTED;

    for (j = proc_id; j < *turn; j = (j+1)%N) {
      while(flag[j] == INTERESTED) sleep(rand());
    }

    flag[proc_id] = ACCESS;

    for (j = 0; j < N; j++) {
      if (j != proc_id && flag[j] == ACCESS) {
        break; 
      }
    }

    if (j == N) {
      *turn = proc_id;
    }
  }
}

/*
 * release the lock on the critical section
 */
void unlock(const unsigned int proc_id, unsigned int* turn, const unsigned int N, int* flag) {
  j = (j + 1) % N;
  while(flag[j] != ACCESS) {
    j = (j + 1) % N;
  }
  *turn = j;
  flag[j] = NOT_INTERESTED;
}
