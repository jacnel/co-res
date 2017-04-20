#include <time.h>
#include <stdio.h>

int main(){
	//LLC_size = 32 *1024;
	//stride = LLC_sets? * cacheline_sz?;
	//buffer = alloc_ptr_chasing_buff(size, stride)?;
clock_t start_t, end_t;
double total_t;
   int i;

   start_t = clock();
   printf("Starting of the program, start_t = %ld\n", start_t);
    
   printf("Going to scan a big loop, start_t = %ld\n", start_t);
   for(i=0; i< 1000000000; i++)
   {
   }
   end_t = clock();
   printf("End of the big loop, end_t = %ld\n", end_t);
   
   total_t = (end_t - start_t)/CLOCKS_PER_SEC;
   printf("Time was: %f\n", (1000*(end_t-start_t)/(double)CLOCKS_PER_SEC));

   return(0);
}