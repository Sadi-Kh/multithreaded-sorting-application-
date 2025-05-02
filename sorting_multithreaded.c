#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10 

int arr[SIZE] = {38, 27, 43, 3, 9, 82, 10, 14, 7, 1};
int merged[SIZE];

typedef struct {
    int start, end;
} Range;


void *sort_thread(void *arg) {
    Range *r = (Range*)arg;
    for (int i = r->start; i < r->end - 1; i++) {
        for (int j = r->start; j < r->end - 1 - (i - r->start); j++) {
            if (arr[j] > arr[j+1]) {
                int t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }
        }
    }
    return NULL;
}

void *merge_thread(void *arg) {
    int mid = SIZE / 2;
    int i = 0, j = mid, k = 0;
    while (i < mid && j < SIZE) {
        if (arr[i] <= arr[j]) merged[k++] = arr[i++];
        else               merged[k++] = arr[j++];
    }
    while (i < mid)   merged[k++] = arr[i++];
    while (j < SIZE)  merged[k++] = arr[j++];
    return NULL;
}

int main() {
    pthread_t t1, t2, tm;
    Range r1 = {0, SIZE/2}, r2 = {SIZE/2, SIZE};

    pthread_create(&t1, NULL, sort_thread, &r1);
    pthread_create(&t2, NULL, sort_thread, &r2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_create(&tm, NULL, merge_thread, NULL);
    pthread_join(tm, NULL);

    printf("Sorted array:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", merged[i]);
    }
    printf("\n");
    return 0;
}
