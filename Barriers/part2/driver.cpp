#include <atomic>
#include <vector>
#include <thread>

#if defined(RELAXED)
#include "relaxed_sb.cpp"
#elif defined(SYNC)
#include "sync_sb.cpp"
#elif defined(DISALLOWED)
#include "sc_sb.cpp"
#endif

#ifndef SRBARRIER
#include "SRBarrier.h"
#endif

barrier_object B;

// Fill these out to match your conditions when checking the output
#define OUTPUT_0 "(r0, r1) = (1,1)"
#define OUTPUT_1 "(r0, r1) = (0,1)"
#define OUTPUT_2 "(r0, r1) = (1,0)"
#define OUTPUT_3 "(r0, r1) = (0,0)"

using namespace std;

atomic_int x(0);
atomic_int y(0);

vector<int> test_driver(int iterations) {

  B.init(2);
  int output0 = 0;
  int output1 = 0;
  int output2 = 0;
  int output3 = 0;

  int r0 = 0;
  int r1 = 0;
  for (int i = 0; i < iterations; i++) {

    x.store(0);
    y.store(0);
    std::thread t0(t0_function, &x, &y, &r0, &B);
    std::thread t1(t1_function, &x, &y, &r1, &B);
    // Run a test iteration
    t0.join();
    t1.join();
    // Record a histogram, fill in the conditions
    if (r0 == 1 && r1 == 1) {
      output0++;
    }
    else if (r0 == 0 && r1 == 1) {
      output1++;
    }
    else if (r0 == 1 && r1 == 0) {
      output2++;
    }
    // This should be the relaxed behavior
    else if (r0 == 0 && r1 == 0) {
      output3++;
    }
  }

  vector<int> res {output0, output1, output2, output3};
  return res;
}
