#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <cmath>
using namespace std;

inline unsigned long long rdtscp() {
  unsigned int lo, hi;
  asm volatile (
		"rdtscp"
		:"=a"(lo), "=d"(hi) // outputs
		:"a"(0) // inputs
		:"%ebx", "%ecx"); // clobbers
  return ((unsigned long long)lo) | (((unsigned long long)hi) << 32);
}

int main() {
  printf("%llu\n", rdtscp());
}
