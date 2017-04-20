#include <time.h>
#include <stdio.h>

int main(){

  /*
    For cache size we need to determine the number of bits in the set.
    Depending on the type of cace we're using we need to determine the number
    of sets in the cache. For two-way associative we have 2 cache blocks and a
    block contains 16 bytes. There fore a set for 2-way has 32 bytes
  */

	//LLC_size = 32 *1024 (32K);
	//stride = LLC_sets? * cacheline_sz (64 bytes);
  //cacheline_sz = 64 bytes because of x86 processor;
	//buffer = alloc_ptr_chasing_buff(size, stride)?;
clock_t start_t, end_t;
double total_t;
   int i;

   start_t = clock();
   //RDTSC() instead
   printf("Starting of the program, start_t = %ld\n", start_t);

   printf("Going to scan a big loop, start_t = %ld\n", start_t);
   for(i=0; i< 1000000000; i++)
   {
   }
   end_t = clock();
   //RDTSC()
   printf("End of the big loop, end_t = %ld\n", end_t);

   total_t = (end_t - start_t)/CLOCKS_PER_SEC;
   printf("Time was: %f\n", (1000*(end_t-start_t)/(double)CLOCKS_PER_SEC));

   return(0);
}
