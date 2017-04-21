#include <time.h>
#include <stdio.h>

inline unsigned long long rdtscp() {
  unsigned int lo, hi;
  asm volatile (
     "rdtscp"
   : "=a"(lo), "=d"(hi) /* outputs */
   : "a"(0)             /* inputs */
   : "%ebx", "%ecx");     /* clobbers*/
  return ((unsigned long long)lo) | (((unsigned long long)hi) << 32);
}

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
unsigned long long start_t, end_t, total_t, average = 0;
   int i, j;

   printf("Starting of the program, start_t = %llu\n", start_t);

   printf("Going to scan a big loop, start_t = %llu\n", start_t);
   for(j = 0; j < 10; j++){
   	start_t = rdtscp();
   		for(i=0; i< 1000000000; i++)
   		{
   		}
   		end_t = rdtscp();
   		total_t = (1000*(end_t-start_t)/(unsigned long long)CLOCKS_PER_SEC);
   		average += total_t;
   		printf("Run %d: %llu\n", j, total_t);
	}
	printf("Average: %llu\n", average/10);
   
   //RDTSC()
   //printf("End of the big loop, end_t = %llu\n", end_t);

   return(0);
}


/*
Normal output

Starting of the program, start_t = 4195392
Going to scan a big loop, start_t = 4195392
Run 0: 7614777
Run 1: 7809730
Run 2: 7999259
Run 3: 7920497
Run 4: 7713896
Run 5: 7709345
Run 6: 7824286
Run 7: 7841637
Run 8: 7824240
Run 9: 7769998
*/

/*
Messing around with sublime text during run time

Starting of the program, start_t = 4195392
Going to scan a big loop, start_t = 4195392
Run 0: 7736186	0-1 normal runs
Run 1: 7741312	
Run 2: 8089420	2 switch focus from terminal to sublime text
Run 3: 10153410
Run 4: 11078050	sublime text 3 moves from wait to ready bin, slow down is from clicking
Run 5: 10000172	and hightlighting etc.
Run 6: 7720998	6 switch focus back to terminal
Run 7: 7615559
Run 8: 7844114
Run 9: 7807428
*/

