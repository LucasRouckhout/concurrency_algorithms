
#define N 5
#define LEFT     (i - 1)%N
#define RIGHT    (i + 1)%N
#define EATING 1
#define THINKING 0
#define HUNGER -1

typedef int semafore;
semafore flag[N]; 
semafore mutex;
int state[N];

void up(semafore*);
void down(semafore*);

void test(const unsigned int i) {
    if (state[i]       == THINKING &&
        state[LEFT]     != EATING &&
        state[RIGHT]    != EATING) {
        state[i] = EATING;
        up(&flag[i]);
    }
}

void take_fork(const unsigned int i) {
    down(&mutex);
    state[i] = HUNGER;
    test(i);
    up(&mutex);
    down(&flag[i]);
}

void release_fork(const unsigned int i) {
    down(&mutex);
    state[i] = THINKING;
    test(LEFT);
    test(RIGHT);
    up(&mutex);
}

void philisopher(const unsigned int i) {
    while(1) {
        take_fork(i);
        release_fork(i);
    }
}
