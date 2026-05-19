#include <pthread.h>
#include <stdio.h>

int x, y, a, b;

void *thread1_routine() {
    x = 1;
    a = y;
    return NULL;
}

void *thread2_routine() {
    y = 1;
    b = x;
    return NULL;
}

int main(void) {
    printf("Start of program.\n");
    int count = 0;
    do {
        x = y = 0;
        pthread_t thread1;
        pthread_t thread2;
        pthread_create(&thread1, NULL, thread1_routine, NULL);
        pthread_create(&thread2, NULL, thread2_routine, NULL);
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
        count++;
    } while (!(a == 0 && b == 0));
    printf("Both threads managed to read 0 after %d iterations.\n", count);
    printf("End of program.\n");
    return 0;
}
