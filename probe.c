#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define LLC_SIZE 6144000 // Bytes
#define LLC_WAYS 12 // ways
#define LLC_SETS 8192 // sets
#define LLC_LINESIZE 64 // Bytes

volatile void* chase_global; // used to defeat optimizations (not sure why!)

inline unsigned long long rdtscp() {
  unsigned int lo, hi;
  asm volatile (
     "rdtscp"
   : "=a"(lo), "=d"(hi) /* outputs */
   : "a"(0)             /* inputs */
   : "%ebx", "%ecx");     /* clobbers*/
  return ((unsigned long long)lo) | (((unsigned long long)hi) << 32);
}

unsigned int log_base2(unsigned int x) {
	unsigned int count = 0;
	while(x >>= 1){
		++count;
	}
	return count;
}

unsigned int bit_reverse(unsigned int val, unsigned int bits) {
	unsigned int result = 0;
	while(bits > 0) {
		result = (result << 1) | (val & 1);
		val >>= 1;
		--bits;
	}
	return result;
}

void generate_bit_rev_perm(unsigned int **dst, unsigned int bits, unsigned int count) {
	unsigned int maxval = 1 << bits;
	unsigned int i;
	for(i = 0; i < maxval; i++) {
		*dst[i] = bit_reverse(i, bits);
	}

	unsigned int current = maxval;
	unsigned int index = 0;
	while(current > count) {
		while(*dst[index] < count) ++index;
		--current;
		*dst[index] = *dst[current];	
	}
}

void** alloc_ptr_chasing_buf(size_t size, size_t stride) {
	size_t buf_len = size / sizeof(void*);  
	void** mem = (void**) malloc(size); // allocate a buffer to be the correct size, returned to caller
	int i;
	/*for(i = 0; i < buf_len; i++) {
		mem[i] = (void*) malloc(sizeof(void*));
		}*/
	
	unsigned int runs = stride / sizeof(void*);
	unsigned int bits = log_base2(runs);
	if((1<<bits)!=runs) bits++;
	unsigned int *offset[1<<bits];
	for(i = 0; i < 1<<bits; i++) {
		offset[i] = (unsigned int*) malloc(sizeof(unsigned int));
	}

	generate_bit_rev_perm(offset, bits, runs);

	unsigned int run;
	void** last = NULL;
	for(run = 0; run < runs; run++) {
		printf("run %d\n", run);
		char* next = (char*)mem + *(offset[run]) * sizeof(void*);
		if(last) {
			*last = (void*) next;		
		}
		last = (void**) next;
		for(;;) {
			char* next = (char*)last + stride;
			if(next >= (char*)mem + size) break;
			*last = (void*) next;
			last = (void**) next;
		}
	}

	// free allocated memory for offset
	for(i = 0; i < 1<<bits; i++) {
	  free(offset[i]);
	}

	*last = (void*) mem;
	return (void**) mem;
}

int main() {
	unsigned int size = LLC_SIZE * (LLC_WAYS + 1);
	unsigned int stride = LLC_SETS * LLC_LINESIZE;
	void** chasing_buf = alloc_ptr_chasing_buf(size, stride);
	
	unsigned long long results[10];
	int i, j;
	for(i = 0; i < 10; i++) {
		printf("...probe %d started\n", i);
		unsigned long long start = rdtscp();
		void** current = (void**) chasing_buf;
		for(j = 0; j < 10000; j++) {
			current = (void**) *current; 
		}
		chase_global = *current;
		results[i] = (rdtscp() - start);
		printf("...probe %d stopped\n", i);
	}

	for(i = 0; i < 10; i++) {
		printf("Run %d: %llu\n", i, results[i]);
	}
	
	// free all pointers
	free(chasing_buf);
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

