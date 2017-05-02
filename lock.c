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
