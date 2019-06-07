#define AMOUNT_OF_CHAIRS 8

typedef int semafore;

semafore mutex;
semafore barber_sem;
semafore customers_sem;

int amount_of_customers = 0;

void down(semafore*);
void up(semafore*);

void barber() {
    while(1) {
        down(&customers_sem);   // Check for customers block on it
        down(&mutex);           // mutex on the amount of customers
        amount_of_customers--;
        up(&barber_sem);        // unblock a customer thread
        up(&mutex);             // release the mutex
    }
}

void customer() {
    down(&mutex);
    if (amount_of_customers < AMOUNT_OF_CHAIRS) {
        amount_of_customers++;  // Increase amount of customers                
        up(&customers_sem);     // Unblock the barber who is blocking
        up(&mutex);             // release lock on amount of customers
        down(&barber_sem);      // block on the barber who will unblock this thread
    } else {
        up(&mutex);             // Make sure to release the mutex
    }
}


