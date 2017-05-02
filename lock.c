#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <pthread.h>

#define LENGTH 8192

void * thread_func(void* unalgn_ptr) {
  int i;
  for(i = 0; i < LENGTH; i++) {
    atomic_fetch_add(*((atomic_int**)(unalgn_ptr)) + i, 1);
  }
  return NULL;
}

int main() {
  atomic_char* ptr = (atomic_char*) malloc((LENGTH + 1) * 8);
  atomic_int* unalgn_ptr = (atomic_int*) (ptr + 2);
  
  while(1) {
    pthread_t threads[50];
    int i;
    for(i = 0; i  < 50; ++i) {
      pthread_create(&threads[i], NULL, thread_func, &unalgn_ptr);
    }
    for(i = 0; i < 50; ++i) {
      pthread_join(threads[i], NULL);
    }
  }
  
  return 0;
}


/*
Without Locking:
Run 0: 2982999
Run 1: 2762397
Run 2: 2913717
Run 3: 3302016
Run 4: 2838426
Run 5: 2723781
Run 6: 2948181
Run 7: 2715717
Run 8: 2673261
Run 9: 3105366

With Locking:
Run 0: 2926491
Run 1: 3496701
Run 2: 2683518
Run 3: 3294291
Run 4: 3260763
Run 5: 2686671
Run 6: 2725176
Run 7: 3146580
Run 8: 2599326
Run 9: 2696295
*/
