/* The Lamport algorithm assumes two shared variables: a number and an array of int
 * representing a ticket system. 
 *
 * Each entry of the ticket array, indexed by the
 * procces ID, contains the value of the ticket of that process. A ticket is taken
 * by incrementing the shared number variable and copying that value into the correct
 * ticket[proc_id] entry. A process that calls lock will now sleep until it has the
 * lowest ticket value. If it is sure that it is the first in line, lowest ticket
 * value, than lock will return and the critical section can be called.
 *
 * After the critical section has been executed the procees MUST call unlock so that
 * other proccesses can enter the critical section.
 *
 * To guarantee mutex access to the ticket array a flag array is presented which
 * signals to other procceses that it is manipulating the ticket array. Other 
 * processes will not evaluate the ticket value of an other proccess if this flag
 * is set.
 *
 * PS: This can be regarded as pseudo code since the variables number and ticket are 
 * not trully shared.
 *
 *
 * Author: Lucas Rouckhout
 */
#include "lock.h"

void lock(const unsigned int proc_id, int* flag) {
    
    flag[proc_id] = 1;
    ticket[proc_id] = ++number;
    flag[proc_id] = 0;
    
    int j;
    for (j = 0; j < N; j++) {
        if ( j == proc_id ) continue;
        
        while(flag[j] != 0) sleep(rand());

        while(ticket[j] != 0 && ticket[j] < ticket[proc_id]) {
            sleep(rand());
        }
        
        if (ticket[j] == ticket[proc_id] && j < proc_id) {
            while(ticket[j] == ticket[proc_id]) sleep(rand());
        }
    }
}


void unlock(const unsigned int proc_id) {
    ticket[proc_id] = 0;
}

