#define SRBARRIER // So that the header is not included twice in driver.cpp
#include "SRBarrier.h"

using namespace std;

// You should use the barrier in this part to increase the number of relaxed behaviors

void t0_function(atomic_int* x, atomic_int* y, int* r0, barrier_object* B) {
  // complete me!
  B->barrier(0);
  x->store(1, std::memory_order_relaxed);
  *r0 = y->load(std::memory_order_relaxed);
}

void t1_function(atomic_int* x, atomic_int* y, int* r1,  barrier_object* B) {
  // complete me!
  B->barrier(1);
  y->store(1, std::memory_order_relaxed);
  *r1 = x->load(std::memory_order_relaxed);
}

